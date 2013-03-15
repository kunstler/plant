#include "plant.h"
#include "strategy.h"

namespace model {

Plant::Plant(Strategy s)
  : standalone(true), 
    strategy(new Strategy(s)) { }

Plant::Plant(Strategy *s) 
  : standalone(false),
    strategy(s) { }

Plant::Plant(const Plant &other)
  : standalone(other.standalone) {
  Rprintf("Copy constructor\n");
  if ( standalone )
    strategy = new Strategy(*other.strategy);
  else
    strategy = other.strategy;
}

Plant& Plant::operator=(const Plant &rhs) {
  Rprintf("Assigmnent operator\n");
  // TODO: Violates DRY - must be some way of doing both.  This will
  // get more important once the state attributes have been added.
  standalone = rhs.standalone;
  if ( standalone )
    strategy = new Strategy(*rhs.strategy);
  else
    strategy = rhs.strategy;

  return *this;
}

Plant::~Plant() {
  if ( standalone )
    delete strategy;
}

double Plant::get_mass_leaf() const {
  return mass_leaf;
}

void Plant::set_mass_leaf(double x) {
  compute_vars_size(x);
}

// [eqn 1-8] Update size variables given an input leaf mass
void Plant::compute_vars_size(double mass_leaf_) {
  if ( mass_leaf_ <= 0.0 ) 
    Rf_error("mass_leaf must be positive");
  // [eqn 1] Leaf mass
  mass_leaf = mass_leaf_;
  // [eqn 2] Leaf area
  leaf_area = mass_leaf / strategy->lma;
  // [eqn 3] Height
  height = strategy->a1*pow(leaf_area, strategy->B1);
  // [eqn 4] Mass of sapwood
  mass_sapwood =   strategy->rho / strategy->theta * 
    strategy->a1 * strategy->eta_c * pow(leaf_area, 1 + strategy->B1);
  // [eqn 5] Mass of bark
  mass_bark = strategy->b * mass_sapwood;
  // [eqn 6] Mass of heartwood
  mass_heartwood = strategy->rho * strategy->eta_c * strategy->a2 * 
    pow(leaf_area, strategy->B2);
  // [eqn 7] Mass of (fine) roots
  mass_root = strategy->a3 * leaf_area;
  // [eqn 8] Total mass
  mass_total = 
    mass_leaf + mass_sapwood + mass_bark + mass_heartwood + mass_root;
}

// [eqn  9] Probability density of leaf area at height `z`
double Plant::q(double z) const {
  const double eta = strategy->eta;
  const double tmp = pow(z / height, eta);
  return 2 * eta * (1 - tmp) * tmp / z;
}

// [eqn 10] ... Fraction of leaf area above height 'z' for an
//              individual of height 'height'
double Plant::Q(double z) const {
  if ( z > height )
    return 0.0;
  const double tmp = 1.0-pow(z/height, strategy->eta);
  return tmp * tmp;
}

// (inverse of [eqn 10]; return the height above which fraction 'x' of
// the leaf mass would be found).
double Plant::Qp(double x) const { // x in [0,1], unchecked.
  return pow(1 - sqrt(x), (1/strategy->eta)) * height;
}

// [      ] Leaf area (not fraction) above height `z`
double Plant::leaf_area_above(double z) const {
  return leaf_area * Q(height);
}


// [Appendix S6] Per-leaf photosynthetic rate.
double Plant::assimilation_leaf(double x) const {
  return strategy->c_p1 * x / (x + strategy->c_p2);
}

// [eqn 12] Gross annual CO2 assimilation
double Plant::compute_assimilation(spline::Spline *env) const {
  //Functor<test::Plant, &test::Plant::assimilation_leaf> fun(&obj);

  Rf_error("Need to write integration support");
  return 0.0;
}

double Plant::compute_assimilation_x(double x, spline::Spline *env) const {
  return assimilation_leaf(env->eval(x)) * q(x);
}

// [eqn 13] Total maintenance respiration
// 
// (note that there is a reparametrisation here relative to the paper
// -- c_Rb is defined (new) as 2*c_Rs, wheras the paper assumes a
// fixed multiplication by 2)
double Plant::compute_respiration() const {
  return 
    strategy->c_Rl * leaf_area * strategy->n_area +
    strategy->c_Rs * mass_sapwood / strategy->rho +
    strategy->c_Rb * mass_bark    / strategy->rho +
    strategy->c_Rr * mass_root;
}

// [eqn 14] Total turnover
// 
// (note that k_l is (a_4*\phi)^{b_4} in [eqn 14], and is computed in
// Plant::compute_constants())
double Plant::compute_turnover() const {
  return
    mass_leaf * strategy->k_l  +
    mass_bark * strategy->k_b  +
    mass_root * strategy->k_r;
}

// [eqn 16] Fraction of whole plan growth that is leaf
double Plant::compute_reproduction_fraction() const {
  return strategy->c_r1 / (1.0 + exp(strategy->c_r2 * 
				     (1.0 - height/strategy->hmat)));
}

// [eqn 18] Fraction of mass growth that is leaves
// 
// TODO: This could do with documenting properly and tidying.
double Plant::compute_leaf_fraction() const {
  const Strategy *s = strategy; // for brevity.
  return 1.0 + s->a3/s->lma +
    (s->rho / s->theta * s->a1 * s->eta_c * (1.0 +s->b) *
     (1.0+s->B1) * pow(leaf_area, s->B1) / s->lma +
     s->rho * s->a2 * s->eta_c * s->B2 * pow(leaf_area, s->B2-1) / s->lma);
  
}

// [eqn 12-19,21] Update physiological variables given the current
// light environment (and given the current set of size variables).
void Plant::compute_vars_phys(spline::Spline *env) {
  // [eqn 12] Gross annual CO2 assimilation
  assimilation = compute_assimilation(env);

  // [eqn 13] Total maintenance respiration
  respiration = compute_respiration();

  // [eqn 14] Total turnover 
  turnover = compute_turnover();

  // [eqn 15] Net production
  const double net_primary_production = 
    strategy->c_bio * strategy->Y * (assimilation - respiration);
  net_production = net_primary_production - turnover;

  if ( net_production > 0 ) {
    // [eqn 16] - Fraction of whole plant growth that is leaf
    reproduction_fraction = compute_reproduction_fraction();

    // [eqn 17] - Rate of offspring production
    fecundity_rate = net_production * reproduction_fraction /
      (strategy->c_acc * strategy->s);

    // [eqn 18] - Fraction of mass growth in leaves
    leaf_fraction = compute_leaf_fraction();

    // [eqn 19] - Growth rate in leaf mass
    growth_rate = net_production * (1 - reproduction_fraction) /
      leaf_fraction;
  } else {
    reproduction_fraction = 0.0;
    fecundity_rate        = 0.0;
    leaf_fraction         = 0.0; // or NA?
    growth_rate           = 0.0;
  }

  // [eqn 21] - Instantaneous mortality rate
  //
  // Composed of a wood density effect (term involving c_d0) and a
  // growth effect (term involving c_d2)
  mortality_rate = 
    strategy->c_d0 * exp(-strategy->c_d1 * strategy->rho) +
    strategy->c_d2 * exp(-strategy->c_d3 * net_production / leaf_area);
}

Rcpp::NumericVector Plant::r_get_vars_size() const {
  using namespace Rcpp;
  return NumericVector::create(_["mass_leaf"]=mass_leaf,
			       _["mass_sapwood"]=mass_sapwood,
			       _["mass_bark"]=mass_bark,
			       _["mass_heartwood"]=mass_heartwood,
			       _["mass_root"]=mass_root,
			       _["mass_total"]=mass_total,
			       _["height"]=height,
			       _["leaf_area"]=leaf_area);
}

Rcpp::NumericVector Plant::r_get_vars_phys() const {
  using namespace Rcpp;
  return NumericVector::create(_["assimilation"]=assimilation,
			       _["respiration"]=respiration,
			       _["turnover"]=turnover,
			       _["net_production"]=net_production,
			       _["reproduction_fraction"]=reproduction_fraction,
			       _["fecundity_rate"]=fecundity_rate,
			       _["leaf_fraction"]=leaf_fraction,
			       _["growth_rate"]=growth_rate);
}

double Plant::r_compute_assimilation(spline::Spline env) const {
  return compute_assimilation(&env);
}

double Plant::r_compute_assimilation_x(double x, spline::Spline env) const {
  return compute_assimilation_x(x, &env);
}

Rcpp::List Plant::r_get_parameters() const {
  return strategy->get_parameters();
}

}
