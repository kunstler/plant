#include <tree2/plant.h>
#include <tree2/qag.h>
#include <tree2/uniroot.h>
#include <Rcpp.h>
#include <functional>

namespace tree2 {

Plant::Plant(Strategy_ptr s)
  : strategy(s) {
  set_height(strategy->height_0);
}

// Individual size
// [eqn 1-8] Update size variables given an input leaf mass

// Height is really important -- everything else follows from it.
double Plant::height() const {
  return vars.height;
}
double Plant::height_rate() const {
  return vars.height_growth_rate;
}
// NOTE: Only recomputes size variables if the height is actually
// different.  This is totally safe if nothing else sets either height
// or any size variable except this method.  This could help save
// quite a bit of calculation time and book-keeping down the track.
// If we're off because of a floating point difference, the worst that
// happens is that we recompute the variables again.
void Plant::set_height(double height_) {
  if (height_ < 0.0) {
    Rcpp::stop("height must be positive (given " +
               util::to_string(height_) + ")");
  }
  if (!util::identical(height_, height())) {
    compute_vars_size(height_);
  }
}

double Plant::mortality() const {
  return vars.mortality;
}
double Plant::mortality_rate() const {
  return vars.mortality_rate;
}
void Plant::set_mortality(double x) {
  vars.mortality = x;
  // this is where the trim_rates code should probably go.
}

double Plant::fecundity() const {
  return vars.fecundity;
}
double Plant::fecundity_rate() const {
  return vars.fecundity_rate;
}
void Plant::set_fecundity(double x) {
  vars.fecundity = x;
}

// Note that there is inconsistencies here with naming because they
// *are* consistent with naming for other variables.  There's some
// tidying up to do here at some point.
double Plant::heartwood_area() const {
  return vars.area_heartwood;
}
double Plant::heartwood_area_rate() const {
  return strategy->k_s0 * sapwood_area();
}
void Plant::set_heartwood_area(double x) {
  vars.area_heartwood = x;
}

double Plant::heartwood_mass() const {
  return vars.mass_heartwood;
}
double Plant::heartwood_mass_rate() const {
  return sapwood_turnover();
}
void Plant::set_heartwood_mass(double x) {
  vars.mass_heartwood = x;
}

// Mortality functions
double Plant::mortality_growth_independent(double d0, double d1,
                                           double rho, double rho_0,
                                           double height, double B6) {
  return(d0 * pow(rho/rho_0, -d1)* pow(height, B6) );
}

double Plant::mortality_growth_dependent(double d2, double d3,
                                         double productivity) {
  return(d2 * exp(-d3 * productivity));
}

// This one is a bit different, as it converts from the mean of the
// poisson process (on [0,Inf)) to a probability (on [0,1]).
double Plant::mortality_probability() const {
  return 1 - survival_probability();
}
double Plant::survival_probability() const {
  return exp(-mortality());
}

// * Competitive environment
double Plant::leaf_area() const {
  return vars.leaf_area;
}

// [      ] Leaf area (not fraction) above height `z`
double Plant::leaf_area_above(double z) const {
  if (z < 0.0) {
    Rcpp::stop("Negative heights do not make sense");
  }
  return vars.leaf_area * Q(z);
}

// * Mass production
// [eqn 12-19,21] Update physiological variables given the current
// light environment (and given the current set of size variables).
void Plant::compute_vars_phys(const Environment& environment) {
  // [eqn 12] Gross annual CO2 assimilation
  vars.assimilation = assimilation(environment);

  // [eqn 13] Total maintenance respiration
  vars.respiration = compute_respiration();

  // [eqn 14] Total turnover
  vars.turnover = compute_turnover();

  // [eqn 15] Net production
  //
  // NOTE: Translation of variable names from the EBT.  our
  // `net_primary_production` is EBT's N, our `net_production` is
  // EBT's P.
  const double net_primary_production =
    strategy->c_bio * strategy->Y * (vars.assimilation - vars.respiration);
  vars.net_production = net_primary_production - vars.turnover;

  if (vars.net_production > 0) {
    // [eqn 16] - Fraction of whole plant growth that is leaf
    vars.reproduction_fraction = compute_reproduction_fraction();

    // [eqn 17] - Rate of offspring production
    //
    // NOTE: In EBT, was multiplied by Pi_0 (survival during
    // dispersal), but we do not here.
    // NOTE: This is also a hyperparametrisation and should move into
    // the initialisation function.
    vars.fecundity_rate = vars.net_production *
      vars.reproduction_fraction / (strategy->s + strategy->c_acc * pow(strategy->
        s/strategy->s_0, strategy->B7));

    // [eqn 18] - Fraction of mass growth in leaves
    vars.leaf_fraction = compute_leaf_fraction();

    // [eqn 19] - Growth rate in leaf mass
    vars.mass_leaf_growth_rate = vars.net_production *
      (1 - vars.reproduction_fraction) * vars.leaf_fraction;

    // [      ] - see doc/details.md
    vars.height_growth_rate = dheight_dleaf_area() * vars.mass_leaf_growth_rate /
      strategy->lma;
  } else {
    vars.reproduction_fraction = 0.0;
    vars.fecundity_rate        = 0.0;
    vars.leaf_fraction         = 0.0;
    vars.mass_leaf_growth_rate = 0.0;
    vars.height_growth_rate    = 0.0;
  }

  // [eqn 21] - Instantaneous mortality rate
  //
  // Composed of a wood density effect (term involving c_d0) and a
  // growth effect (term involving c_d2)
  //
  // NOTE: When plants are extremely inviable, the rate of change in
  // mortality can be Inf, because net production is negative, leaf
  // area is small and so we get exp(big number).  However, most of
  // the time that happens we should get infinite mortality variable
  // levels and the rate of change won't matter.  It is possible that
  // we will need to trim this to some large finite value, but for
  // now, just checking that the actual mortality rate is finite.
  vars.mortality_rate =
    mortality_growth_independent(strategy->c_d0, strategy->c_d1,
                                 strategy->rho, strategy->rho_0,
                                 vars.height, strategy->B6) +
    mortality_growth_dependent(strategy->c_d2, strategy->c_d3,
                               vars.net_production / vars.leaf_area);
  trim_rates();
}

// [eqn 20] Survival of seedlings during germination
//
// NOTE: This does not check/enforce that height is set to the seed
// height (so this is actually the germination probability of a plant
// that happens to be the current size).  This might be something to
// change.
double Plant::germination_probability(const Environment& environment) {
  compute_vars_phys(environment);
  return germination_probability();
}

double Plant::germination_probability() const {
  if (vars.net_production > 0) {
    const double tmp = vars.leaf_area * strategy->c_s0 / vars.net_production;
    return 1 / (tmp * tmp + 1.0);
  } else {
    return 0.0;
  }
}

// NOTE: static method.
void Plant::prepare_strategy(Strategy_ptr s) {
  // Set up the integrator.
  s->control.initialize();
  // NOTE: this precomputes something to save a very small amount of time
  s->eta_c = 1 - 2/(1 + s->eta) + 1/(1 + 2*s->eta);
  // NOTE: These are straight up hyper parametrisation.  k_l0, lma_0
  // and B4 can all come out and be replaced by k_l, with this logic
  // kept back in the generating class.
  s->k_l = s->k_l0 * pow(s->lma/s->lma_0, -s->B4);
  s->k_s = s->k_s0 * pow(s->rho/s->rho_0, -s->B5);
  // NOTE: Also precomputing, though less trivial
  s->height_0 = height_seed(s);
}

// * R interface
Strategy Plant::r_get_strategy() const {
  return *strategy.get();
}

SEXP Plant::r_get_vars_size() const {
  using namespace Rcpp;
  return wrap(NumericVector::create(
                               _["mass_leaf"]=vars.mass_leaf,
                               _["mass_sapwood"]=vars.mass_sapwood,
                               _["mass_bark"]=vars.mass_bark,
                               _["mass_heartwood"]=vars.mass_heartwood,
                               _["mass_root"]=vars.mass_root,
                               _["mass_live"]=vars.mass_live,
                               _["mass_total"]=vars.mass_live+vars.mass_heartwood,
                               _["mass_above_ground"]=vars.mass_live+vars.mass_heartwood - vars.mass_root,
                               _["height"]=vars.height,
                               _["leaf_area"]=vars.leaf_area,
                               _["area_sapwood"]= sapwood_area(),
                               _["area_bark"]= bark_area(),
                               _["area_heartwood"]= vars.area_heartwood,
                               _["area_basal"]= basal_area(),
                               _["diameter"]= pow(4*basal_area()/M_PI,0.5)
                                    ));
}

SEXP Plant::r_get_vars_phys() const {
  using namespace Rcpp;
  return wrap(NumericVector::create(_["assimilation"]=vars.assimilation,
                               _["respiration"]=vars.respiration,
                               _["turnover"]=vars.turnover,
                               _["net_production"]=vars.net_production,
                               _["reproduction_fraction"]=
                               vars.reproduction_fraction,
                               _["fecundity_rate"]=vars.fecundity_rate,
                               _["leaf_fraction"]=vars.leaf_fraction,
                               _["height_growth_rate"]=
                               vars.height_growth_rate,
                               _["mortality_rate"]=vars.mortality_rate
                                    ));
}

// TODO: Revisit names here
// TODO: Could use functions for some of the last three messes.
SEXP Plant::r_get_vars_growth() const {
  using namespace Rcpp;
  return wrap(NumericVector::create(
             _["dheight_dleaf_area"]=dheight_dleaf_area(),
             _["dleaf_area_dleaf_mass"]=1/strategy->lma,
             _["growth_fraction"]=1-vars.reproduction_fraction,
             _["dmass_sapwood_dmass_leaf"]=dmass_sapwood_dmass_leaf(),
             _["dmass_bark_dmass_leaf"]=dmass_bark_dmass_leaf(),
             _["dmass_root_dmass_leaf"]=dmass_root_dmass_leaf(),
             _["dleaf_area_dt"]=dleaf_area_dt(),
             _["dsapwood_area_dt"]=dsapwood_area_dt(),
             _["dbark_area_dt"]=dbark_area_dt(),
             _["dheartwood_area_dt"]=heartwood_area_rate(),
             _["dheartwood_mass_dt"]=heartwood_mass_rate(),
             _["dbasal_area_dt"]=dbasal_area_dt(),
             _["dbasal_diam_dbasal_area"]=dbasal_diam_dbasal_area(),
             _["dbasal_diam_dt"]=dbasal_diam_dt(),
             _["dmass_leaf_dt"]=vars.mass_leaf_growth_rate,
             _["dmass_root_dt"]=vars.mass_leaf_growth_rate*dmass_root_dmass_leaf(),
             _["dmass_live_dt"]=(1-vars.reproduction_fraction)*vars.net_production,
             _["dmass_total_dt"]=(1-vars.reproduction_fraction)*vars.net_production + sapwood_turnover(),
             _["dmass_above_ground_dt"]=(1-vars.reproduction_fraction)*vars.net_production
                            + sapwood_turnover() - vars.mass_leaf_growth_rate*dmass_root_dmass_leaf()
                                    ));
}

Plant Plant::r_copy() const {
  return *this;
}

// This exists only so that I know that nothing will change the
// control parameters by only being able to access a const reference
// (it's shared with everything else that shares the strategy).  It
// also saves a little ugly looking referencing.
const Control& Plant::control() const {
  return strategy->control;
}

// This is required so that the cohort calculations can use the exact
// same intervals for integration.  I might shift this into the
// Strategy or something though.  Not sure.
// TODO: Given these are unchecked get/set pairs, replace with direct
// access to the member I think.
quadrature::intervals_type Plant::get_last_integration_intervals() const {
  return strategy->control.integrator.get_last_intervals();
}
void Plant::set_integration_intervals(quadrature::intervals_type x) {
  integration_intervals = x;
}

// This is used to stop rates getting out of control.
//
// TODO: This is currently implemented as a method only so that
// CohortTop can override it after inheritence.  That's likely to stop
// soon, at which point this can happily move into the function that
// calls it.
void Plant::trim_rates() {
  if (!R_FINITE(vars.mortality)) {
    vars.mortality_rate = 0.0;
  }
}

// * Private methods

// * Individual size
// [eqn 1-8] Update size variables to a new leaf mass.
void Plant::compute_vars_size(double height_) {
  // First 3 differ from paper; working height->mass, not mass->height.
  // [eqn 3] height
  vars.height = height_;
  // [eqn 2] leaf_area (inverse of [eqn 3])
  vars.leaf_area = pow(vars.height / strategy->a1, 1 / strategy->B1);
  // [eqn 1] mass_leaf (inverse of [eqn 2])
  vars.mass_leaf = vars.leaf_area * strategy->lma;

  // These are identical to paper.
  // [eqn 4] Mass of sapwood
  vars.mass_sapwood =   strategy->rho / strategy->theta *
    strategy->a1 * strategy->eta_c * pow(vars.leaf_area, 1 + strategy->B1);
  // [eqn 5] Mass of bark
  vars.mass_bark = strategy->b * vars.mass_sapwood;
  // [eqn 7] Mass of (fine) roots
  vars.mass_root = strategy->a3 * vars.leaf_area;
  // [eqn 8] Total mass
  vars.mass_live =
    vars.mass_leaf + vars.mass_sapwood + vars.mass_bark + vars.mass_root;
}

// [eqn  9] Probability density of leaf area at height `z`
double Plant::q(double z) const {
  const double eta = strategy->eta;
  const double tmp = pow(z / vars.height, eta);
  return 2 * eta * (1 - tmp) * tmp / z;
}

// [eqn 10] ... Fraction of leaf area above height 'z' for an
//              individual of height 'height'
double Plant::Q(double z) const {
  if (z > vars.height) {
    return 0.0;
  }
  const double tmp = 1.0-pow(z / vars.height, strategy->eta);
  return tmp * tmp;
}

// (inverse of [eqn 10]; return the height above which fraction 'x' of
// the leaf mass would be found).
double Plant::Qp(double x) const { // x in [0,1], unchecked.
  return pow(1 - sqrt(x), (1/strategy->eta)) * vars.height;
}

// [eqn 12] Gross annual CO2 assimilation
//
// NOTE: In contrast with Daniel's implementation (but following
// Falster 2012), we do not normalise by Y*c_bio here.
double Plant::assimilation(const Environment& environment) {
  return compute_assimilation(environment);
}

double Plant::compute_assimilation(const Environment& environment) {
  // const bool over_distribution = control().plant_assimilation_over_distribution;
  // const double x_min = 0, x_max = over_distribution ? 1 : vars.height;
  double A = 0.0;
  quadrature::QAG integrator(control().integrator);

  // I should probably use std::function here to store the return
  // value, then we can use the same integrate command easily enough.
  if (control().plant_assimilation_over_distribution) {
    auto f = [&] (double x) -> double {
      return compute_assimilation_h(x, environment);
    };
    A = integrator.integrate(f, 0.0, vars.height);
  } else {
    auto f = [&] (double x) -> double {
      return compute_assimilation_p(x, environment);
    };
    A = integrator.integrate(f, 0.0, 1.0);
  }

  // This whole section exists only because of working around
  // CohortTop, where we want to recompute the photosynthetic integral
  // using the same grid that we refined onto before.  This would
  // probably be heaps more efficient if we worked with references or
  // iterators and avoided the copying that is going on here.
  // Conceptually, this probably belongs in its own function.
  // if (control().plant_assimilation_adaptive &&
  //     control().plant_assimilation_reuse_intervals &&
  //     integration_intervals.size() == 2) {
  //   if (over_distribution) {
  //     A = strategy->integrator.integrate_with_intervals(&fun,
  //                                                       integration_intervals);
  //   } else {
  //     // In theory we might not have to to scale if we're doing
  //     // backward differencing.
  //     A = strategy->integrator.integrate_with_intervals(&fun,
  //                                                       quadrature::internal::rescale_intervals(integration_intervals, x_min, x_max));
  //   }
  // } else {
  //   A = strategy->integrator.integrate(&fun, x_min, x_max);
  // }
  return vars.leaf_area * A;
}

// This is used in the calculation of assimilation by
// `compute_assimilation` above; it is the term within the integral in
// [eqn 12]; i.e., A_lf(A_0v, E(z,a)) * q(z,h(m_l))
// where `z` is height.
double Plant::compute_assimilation_x(double x,
                                     const Environment& environment) const {
  if (control().plant_assimilation_over_distribution) {
    return compute_assimilation_p(x, environment);
  } else {
    return compute_assimilation_h(x, environment);
  }
}

double Plant::compute_assimilation_h(double h,
                                     const Environment& environment) const {
  return assimilation_leaf(environment.canopy_openness(h)) * q(h);
}

double Plant::compute_assimilation_p(double p,
                                     const Environment& environment) const {
  return assimilation_leaf(environment.canopy_openness(Qp(p)));
}

// [Appendix S6] Per-leaf photosynthetic rate.
// Here, `x` is openness, ranging from 0 to 1.
double Plant::assimilation_leaf(double x) const {
  return strategy->c_p1 * x / (x + strategy->c_p2);
}

// [eqn 13] Total maintenance respiration
//
// (NOTE that there is a reparametrisation here relative to the paper
// -- c_Rb is defined (new) as 2*c_Rs, wheras the paper assumes a
// fixed multiplication by 2)
//
// NOTE: In contrast with EBT, we do not normalise by Y*c_bio.
double Plant::compute_respiration() const {
  return
    strategy->c_Rl * vars.leaf_area * strategy->n_area +
    strategy->c_Rs * vars.mass_sapwood / strategy->rho +
    strategy->c_Rb * vars.mass_bark    / strategy->rho +
    strategy->c_Rr * vars.mass_root;
}

// [eqn 14] Total turnover
//
// (NOTE: `k_l` is (a_4*\phi)^{b_4} in [eqn 14], and is computed by
// `prepare_strategy`).
double Plant::compute_turnover() const {
  return
    vars.mass_leaf * strategy->k_l  +
    vars.mass_bark * strategy->k_b  +
    sapwood_turnover() +
    vars.mass_root * strategy->k_r;
}

double Plant::sapwood_turnover() const {
  return vars.mass_sapwood * strategy->k_s;
}

// [eqn 16] Fraction of production allocated to reproduction
double Plant::compute_reproduction_fraction() const {
  return strategy->c_r1 / (1.0 + exp(strategy->c_r2 *
                                     (1.0 - vars.height/strategy->hmat)));
}

// [eqn 18] Fraction of mass growth that is leaves (see doc/details.md
// for derivation).
double Plant::compute_leaf_fraction() const {
  return 1.0/(
              1.0
        + dmass_sapwood_dmass_leaf()
        + dmass_bark_dmass_leaf()
        + dmass_root_dmass_leaf());
}

// Sapwood area
double Plant::sapwood_area() const {
  return vars.leaf_area / strategy->theta;
}

// Bark area
double Plant::bark_area() const {
  return strategy->b * sapwood_area();
}

// basal area
double Plant::basal_area() const {
  return heartwood_area() + bark_area() + sapwood_area();
}

// Mass of stem needed for new unit mass leaf, d m_s / d m_l
double Plant::dmass_sapwood_dmass_leaf() const {
  const Strategy *s = strategy.get(); // for brevity.
  return s->rho * s->eta_c * s->a1 / (s->theta * s->lma) *
        (s->B1 + 1.0) * pow(vars.leaf_area, s->B1);
}

// Mass of bark needed for new unit mass leaf, d m_b / d m_l
double Plant::dmass_bark_dmass_leaf() const {
  return strategy->b * dmass_sapwood_dmass_leaf();
}

// Mass of root needed for new unit mass leaf, d m_r / d m_l
double Plant::dmass_root_dmass_leaf() const {
  return strategy->a3 / strategy->lma;
}

double Plant::dheight_dleaf_area() const {
  return strategy->a1 * strategy->B1 *
  pow(vars.leaf_area, strategy->B1 - 1);
}

// Growth rate of leaf area per unit time
double Plant::dleaf_area_dt() const {
  return vars.mass_leaf_growth_rate / strategy->lma;;
}

// Growth rate of spawood area at base per unit time
double Plant::dsapwood_area_dt() const {
  return dleaf_area_dt() / strategy->theta;
}

// Growth rate of bark area at base per unit time
double Plant::dbark_area_dt() const {
  return strategy->b * dsapwood_area_dt();
}

// Growth rate of stem basal area per unit time
double Plant::dbasal_area_dt() const {
  return dsapwood_area_dt() + dbark_area_dt() + heartwood_area_rate();
}

// Growth rate of basal diameter per unit time
double Plant::dbasal_diam_dbasal_area() const {
  return pow(M_PI/basal_area(),0.5);
}

// Growth rate of basal diameter per unit time
double Plant::dbasal_diam_dt() const {
  return dbasal_diam_dbasal_area() * dbasal_area_dt();
}


// NOTE: static method
// The aim is to find a plant height that gives the correct seed mass.
double Plant::height_seed(Strategy_ptr s) {
  Plant p(s);
  const double seed_mass = p.strategy->s;

  // TODO: I don't think these are actually correct bounds; we would
  // actually want height given *total* mass.  This is probably why
  // this breaks with obscure parameter values.
  const double
    h0 = p.height_given_mass_leaf(std::numeric_limits<double>::min()),
    h1 = p.height_given_mass_leaf(seed_mass);
  const double tol = p.control().plant_seed_tol;
  const size_t max_iterations = p.control().plant_seed_iterations;

  auto target = [&] (double x) mutable -> double {
    return p.mass_live_given_height(x) - seed_mass;
  };

  return util::uniroot(target, h0, h1, tol, max_iterations);
}

// NOTE: This is used only by height_seed.
double Plant::mass_live_given_height(double h) {
  set_height(h);
  return vars.mass_live;
}

// This is useful for finding the seed height.
double Plant::height_given_mass_leaf(double mass_leaf_) const {
  return strategy->a1 * pow(mass_leaf_ / strategy->lma, strategy->B1);
}

Plant::internals::internals()
  : mass_leaf(NA_REAL),
    leaf_area(NA_REAL),
    height(NA_REAL),
    mass_sapwood(NA_REAL),
    mass_bark(NA_REAL),
    mass_heartwood(0),
    area_heartwood(0),
    mass_root(NA_REAL),
    mass_live(NA_REAL),
    assimilation(NA_REAL),
    respiration(NA_REAL),
    turnover(NA_REAL),
    net_production(NA_REAL),
    reproduction_fraction(NA_REAL),
    fecundity_rate(NA_REAL),
    leaf_fraction(NA_REAL),
    mass_leaf_growth_rate(NA_REAL),
    height_growth_rate(NA_REAL),
    mortality_rate(NA_REAL),
    // But these should be zero
    mortality(0.0),
    fecundity(0.0) {
}

Strategy_ptr make_strategy_ptr(Strategy s) {
  Strategy_ptr sp = std::make_shared<Strategy>(s);
  Plant::prepare_strategy(sp);
  return sp;
}

Plant make_plant(Strategy s) {
  return Plant(make_strategy_ptr(s));
}

}

// Some exports

// [[Rcpp::export]]
double mortality_growth_independent(double d0, double d1,
                                    double rho, double rho_0,
                                    double height, double B6) {
  return tree2::Plant::mortality_growth_independent(d0, d1, rho, rho_0,
                                                    height, B6);
}

// [[Rcpp::export]]
double mortality_growth_dependent(double d2, double d3,
                                  double productivity) {
  return tree2::Plant::mortality_growth_dependent(d2, d3, productivity);
}
