// -*-c++-*-
#ifndef TREE_COHORT_H_
#define TREE_COHORT_H_

#include <tree2/environment.h>
#include <tree2/gradient.h>

namespace tree2 {

template <typename T>
class Cohort {
public:
  typedef typename T::strategy_type strategy_type;
  Cohort(strategy_type s);

  void compute_vars_phys(const Environment& environment);
  void compute_initial_conditions(const Environment& environment);

  // * R interface (testing only, really)
  double r_growth_rate_gradient(const Environment& environment);

  double height() const {return plant.height();}
  double leaf_area_above(double z) const;
  double leaf_area() const;

  T plant;

private:
  // This is the gradient of growth rate with respect to height:
  double growth_rate_gradient(const Environment& environment) const;
  double growth_rate_given_height(double height_,
                                  const Environment& environment);

  double log_density;
  double log_density_rate;
  double density; // hmm...
  double seeds_survival_weighted;
  double seeds_survival_weighted_rate;
  double pr_patch_survival_at_birth;
};

template <typename T>
Cohort<T>::Cohort(strategy_type s)
  : plant(s),
    log_density(R_NegInf),
    log_density_rate(0),
    density(0),
    seeds_survival_weighted(0),
    seeds_survival_weighted_rate(0),
    pr_patch_survival_at_birth(1) {
}

template <typename T>
void Cohort<T>::compute_vars_phys(const Environment& environment) {
  plant.compute_vars_phys(environment);

  // [eqn 22] Density per unit area of individuals with size 'h'.
  // EBT.md{eq:boundN}, see Numerical technique.
  // details.md, for details on translation from mass_leaf to height.
  log_density_rate =
    - growth_rate_gradient(environment)
    - plant.mortality_rate();

  // EBT.md{eq:boundSurv}, see Numerical technique
  const double survival_patch = environment.patch_survival();
  seeds_survival_weighted_rate =
    plant.fecundity_rate() * plant.survival_probability() *
    survival_patch / pr_patch_survival_at_birth;
}

// NOTE: germination_probability() will cause all physiological
// variables to be updated, so height_rate() becomes valid so long as
// it is used *after* germination_probability().  This is something
// that can be improved, as that feels a bit fragile.
//
// NOTE: There will be a discussion of why the mortality rate initial
// condition is -log(germination_probability) in the documentation
// that Daniel is working out.
//
// NOTE: The initial condition for log_density is also a bit tricky, and
// defined on p 7 at the moment.
template <typename T>
void Cohort<T>::compute_initial_conditions(const Environment& environment) {
  pr_patch_survival_at_birth = environment.patch_survival();
  const double pr_germ = plant.germination_probability(environment);
  // EBT.md{eq:boundSurv}
  plant.set_mortality(-log(pr_germ));
  // EBT.md{eq:boundN}
  const double g = plant.height_rate();
  const double seed_rain = environment.seed_rain_rate();
  // NOTE: log(0.0) -> -Inf, which should behave fine.
  log_density = g > 0 ? log(seed_rain * pr_germ / g) : log(0.0);
  density     = exp(log_density);

  // Need to check that the rates are valid after setting the
  // mortality value here (can go to -Inf and that requires squashing
  // the rate to zero).
  // trim_rates();
  plant.trim_rates();
  if (!R_FINITE(log_density)) {
    log_density_rate = 0.0;
  }
}

template <typename T>
double Cohort<T>::growth_rate_gradient(const Environment& environment) const {
  // TODO: What needs to happen here is that we set tmp.plant to use
  // previously stored integration intervals.  They will be found in
  // the control object that the plant has anyway, so that will all
  // work pretty nicely.  The code in Plant::compute_assimilation to
  // make use of this has not yet been written though.
  //
  // TODO: There's no need to play around with cohorts here; could
  // work natively with a Plant object.  We'll lose the ability,
  // later, to easily get access to growth_rate_given_height, but
  // that's used in only one script.  It's a change that can be easily
  // made later though.
  Cohort<T> tmp = *this;
  auto fun = [=] (double h) mutable -> double {
    return tmp.growth_rate_given_height(h, environment);
  };

  const Control& control = plant.control();
  const double eps = control.cohort_gradient_eps;
  if (control.cohort_gradient_richardson) {
    const size_t r = control.cohort_gradient_richardson_depth;
    return util::gradient_richardson(fun, plant.height(), eps, r);
  } else {
    return util::gradient_fd(fun, plant.height(), eps, plant.height_rate(),
                             control.cohort_gradient_direction);
  }
}

// This exists only because it is needed by growth_rate_gradient.
template <typename T>
double Cohort<T>::growth_rate_given_height(double height_,
                                           const Environment& environment) {
  plant.set_height(height_);
  plant.compute_vars_phys(environment);
  return plant.height_rate();
}

template <typename T>
double Cohort<T>::r_growth_rate_gradient(const Environment& environment) {
  plant.compute_vars_phys(environment);
  return growth_rate_gradient(environment);
}

template <typename T>
double Cohort<T>::leaf_area_above(double height_) const {
  return density * plant.leaf_area_above(height_);
}

template <typename T>
double Cohort<T>::leaf_area() const {
  return density * plant.leaf_area();
}

template <typename T>
Cohort<T> make_cohort(typename Cohort<T>::strategy_type::element_type s) {
  return Cohort<T>(make_strategy_ptr(s));
}

}

#endif
