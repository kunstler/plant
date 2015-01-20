// Generated by RcppR6 (0.1): do not edit by hand
#ifndef _TREE2_RCPPR6_POST_HPP_
#define _TREE2_RCPPR6_POST_HPP_

#include <Rcpp.h>
#include <tree2/RcppR6_support.hpp>

namespace tree2 {
namespace RcppR6 {
namespace traits {
template <> inline std::string   class_name_r<ode::test::Lorenz >() {return "Lorenz";}
template <> inline std::string   package_name<ode::test::Lorenz >() {return "tree2";}
template <> inline std::string generator_name<ode::test::Lorenz >() {return ".R6_Lorenz";}

template <> inline std::string   class_name_r<ode::Runner<ode::test::Lorenz> >() {return "OdeRunner<Lorenz>";}
template <> inline std::string   package_name<ode::Runner<ode::test::Lorenz> >() {return "tree2";}
template <> inline std::string generator_name<ode::Runner<ode::test::Lorenz> >() {return ".R6_OdeRunner___Lorenz";}

template <> inline std::string   class_name_r<tree2::CohortScheduleEvent >() {return "CohortScheduleEvent";}
template <> inline std::string   package_name<tree2::CohortScheduleEvent >() {return "tree2";}
template <> inline std::string generator_name<tree2::CohortScheduleEvent >() {return ".R6_CohortScheduleEvent";}

template <> inline std::string   class_name_r<tree2::CohortSchedule >() {return "CohortSchedule";}
template <> inline std::string   package_name<tree2::CohortSchedule >() {return "tree2";}
template <> inline std::string generator_name<tree2::CohortSchedule >() {return ".R6_CohortSchedule";}

template <> inline std::string   class_name_r<tree2::Disturbance >() {return "Disturbance";}
template <> inline std::string   package_name<tree2::Disturbance >() {return "tree2";}
template <> inline std::string generator_name<tree2::Disturbance >() {return ".R6_Disturbance";}

template <> inline std::string   class_name_r<tree2::Control >() {return "Control";}
template <> inline std::string   package_name<tree2::Control >() {return "tree2";}
template <> inline std::string generator_name<tree2::Control >() {return "";}

template <> inline std::string   class_name_r<ode::OdeControl >() {return "OdeControl";}
template <> inline std::string   package_name<ode::OdeControl >() {return "tree2";}
template <> inline std::string generator_name<ode::OdeControl >() {return "";}

template <> inline std::string   class_name_r<tree2::Strategy >() {return "Strategy";}
template <> inline std::string   package_name<tree2::Strategy >() {return "tree2";}
template <> inline std::string generator_name<tree2::Strategy >() {return "";}

template <> inline std::string   class_name_r<tree2::Parameters >() {return "Parameters";}
template <> inline std::string   package_name<tree2::Parameters >() {return "tree2";}
template <> inline std::string generator_name<tree2::Parameters >() {return "";}

template <> inline std::string   class_name_r<quadrature::QK >() {return "QK";}
template <> inline std::string   package_name<quadrature::QK >() {return "tree2";}
template <> inline std::string generator_name<quadrature::QK >() {return ".R6_QK";}

template <> inline std::string   class_name_r<quadrature::QAG >() {return "QAG";}
template <> inline std::string   package_name<quadrature::QAG >() {return "tree2";}
template <> inline std::string generator_name<quadrature::QAG >() {return ".R6_QAG";}

template <> inline std::string   class_name_r<interpolator::Interpolator >() {return "Interpolator";}
template <> inline std::string   package_name<interpolator::Interpolator >() {return "tree2";}
template <> inline std::string generator_name<interpolator::Interpolator >() {return ".R6_Interpolator";}

template <> inline std::string   class_name_r<tree2::Environment >() {return "Environment";}
template <> inline std::string   package_name<tree2::Environment >() {return "tree2";}
template <> inline std::string generator_name<tree2::Environment >() {return ".R6_Environment";}

template <> inline std::string   class_name_r<tree2::Plant >() {return "Plant";}
template <> inline std::string   package_name<tree2::Plant >() {return "tree2";}
template <> inline std::string generator_name<tree2::Plant >() {return ".R6_Plant";}

template <> inline std::string   class_name_r<tree2::Cohort<tree2::Plant> >() {return "Cohort";}
template <> inline std::string   package_name<tree2::Cohort<tree2::Plant> >() {return "tree2";}
template <> inline std::string generator_name<tree2::Cohort<tree2::Plant> >() {return ".R6_Cohort";}

template <> inline std::string   class_name_r<tree2::Species<tree2::Cohort<tree2::Plant> > >() {return "Species";}
template <> inline std::string   package_name<tree2::Species<tree2::Cohort<tree2::Plant> > >() {return "tree2";}
template <> inline std::string generator_name<tree2::Species<tree2::Cohort<tree2::Plant> > >() {return ".R6_Species";}

template <> inline std::string   class_name_r<tree2::Patch<tree2::Cohort<tree2::Plant> > >() {return "Patch";}
template <> inline std::string   package_name<tree2::Patch<tree2::Cohort<tree2::Plant> > >() {return "tree2";}
template <> inline std::string generator_name<tree2::Patch<tree2::Cohort<tree2::Plant> > >() {return ".R6_Patch";}

template <> inline std::string   class_name_r<tree2::EBT<tree2::Plant> >() {return "EBT";}
template <> inline std::string   package_name<tree2::EBT<tree2::Plant> >() {return "tree2";}
template <> inline std::string generator_name<tree2::EBT<tree2::Plant> >() {return ".R6_EBT";}
}
}
}

namespace Rcpp {
template <typename T>
SEXP wrap(const tree2::RcppR6::RcppR6<T>& x) {
  return x.to_R6();
}

namespace traits {
template <typename T>
class Exporter<tree2::RcppR6::RcppR6<T> > {
public:
  Exporter(SEXP x) : obj(tree2::RcppR6::RcppR6<T>(x)) {}
  inline tree2::RcppR6::RcppR6<T> get() { return obj; }
private:
  tree2::RcppR6::RcppR6<T> obj;
};
}

template <> inline SEXP wrap(const ode::test::Lorenz& x) {
  return wrap(tree2::RcppR6::RcppR6<ode::test::Lorenz>(x));
}
template <> inline ode::test::Lorenz as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<ode::test::Lorenz>(x));
}

template <> inline SEXP wrap(const ode::Runner<ode::test::Lorenz>& x) {
  return wrap(tree2::RcppR6::RcppR6<ode::Runner<ode::test::Lorenz> >(x));
}
template <> inline ode::Runner<ode::test::Lorenz> as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<ode::Runner<ode::test::Lorenz> >(x));
}

template <> inline SEXP wrap(const tree2::CohortScheduleEvent& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::CohortScheduleEvent>(x));
}
template <> inline tree2::CohortScheduleEvent as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::CohortScheduleEvent>(x));
}

template <> inline SEXP wrap(const tree2::CohortSchedule& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::CohortSchedule>(x));
}
template <> inline tree2::CohortSchedule as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::CohortSchedule>(x));
}

template <> inline SEXP wrap(const tree2::Disturbance& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::Disturbance>(x));
}
template <> inline tree2::Disturbance as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::Disturbance>(x));
}

template <> inline SEXP wrap(const tree2::Control& x) {
  Rcpp::List ret;
  ret["plant_assimilation_adaptive"] = Rcpp::wrap(x.plant_assimilation_adaptive);
  ret["plant_assimilation_over_distribution"] = Rcpp::wrap(x.plant_assimilation_over_distribution);
  ret["plant_assimilation_tol"] = Rcpp::wrap(x.plant_assimilation_tol);
  ret["plant_assimilation_iterations"] = Rcpp::wrap(x.plant_assimilation_iterations);
  ret["plant_assimilation_rule"] = Rcpp::wrap(x.plant_assimilation_rule);
  ret["plant_assimilation_reuse_intervals"] = Rcpp::wrap(x.plant_assimilation_reuse_intervals);
  ret["plant_assimilation_approximate_use"] = Rcpp::wrap(x.plant_assimilation_approximate_use);
  ret["plant_assimilation_approximate_tol"] = Rcpp::wrap(x.plant_assimilation_approximate_tol);
  ret["plant_assimilation_approximate_nbase"] = Rcpp::wrap(x.plant_assimilation_approximate_nbase);
  ret["plant_assimilation_approximate_max_depth"] = Rcpp::wrap(x.plant_assimilation_approximate_max_depth);
  ret["plant_assimilation_approximate_akima"] = Rcpp::wrap(x.plant_assimilation_approximate_akima);
  ret["plant_assimilation_approximate_linear"] = Rcpp::wrap(x.plant_assimilation_approximate_linear);
  ret["plant_assimilation_approximate_rescale_usually"] = Rcpp::wrap(x.plant_assimilation_approximate_rescale_usually);
  ret["plant_seed_tol"] = Rcpp::wrap(x.plant_seed_tol);
  ret["plant_seed_iterations"] = Rcpp::wrap(x.plant_seed_iterations);
  ret["cohort_gradient_eps"] = Rcpp::wrap(x.cohort_gradient_eps);
  ret["cohort_gradient_direction"] = Rcpp::wrap(x.cohort_gradient_direction);
  ret["cohort_gradient_richardson"] = Rcpp::wrap(x.cohort_gradient_richardson);
  ret["cohort_gradient_richardson_depth"] = Rcpp::wrap(x.cohort_gradient_richardson_depth);
  ret["environment_light_tol"] = Rcpp::wrap(x.environment_light_tol);
  ret["environment_light_nbase"] = Rcpp::wrap(x.environment_light_nbase);
  ret["environment_light_max_depth"] = Rcpp::wrap(x.environment_light_max_depth);
  ret["environment_light_akima"] = Rcpp::wrap(x.environment_light_akima);
  ret["environment_light_linear"] = Rcpp::wrap(x.environment_light_linear);
  ret["environment_light_rescale_usually"] = Rcpp::wrap(x.environment_light_rescale_usually);
  ret["environment_light_skip"] = Rcpp::wrap(x.environment_light_skip);
  ret["ode_step_size_min"] = Rcpp::wrap(x.ode_step_size_min);
  ret["ode_step_size_max"] = Rcpp::wrap(x.ode_step_size_max);
  ret["ode_tol_rel"] = Rcpp::wrap(x.ode_tol_rel);
  ret["ode_tol_abs"] = Rcpp::wrap(x.ode_tol_abs);
  ret["ode_a_y"] = Rcpp::wrap(x.ode_a_y);
  ret["ode_a_dydt"] = Rcpp::wrap(x.ode_a_dydt);
  ret["schedule_nsteps"] = Rcpp::wrap(x.schedule_nsteps);
  ret["schedule_eps"] = Rcpp::wrap(x.schedule_eps);
  ret["schedule_progress"] = Rcpp::wrap(x.schedule_progress);
  ret["schedule_verbose"] = Rcpp::wrap(x.schedule_verbose);
  ret["schedule_default_patch_survival"] = Rcpp::wrap(x.schedule_default_patch_survival);
  ret["schedule_default_multipler"] = Rcpp::wrap(x.schedule_default_multipler);
  ret["schedule_default_min_step_size"] = Rcpp::wrap(x.schedule_default_min_step_size);
  ret["schedule_default_max_step_size"] = Rcpp::wrap(x.schedule_default_max_step_size);
  ret["equilibrium_nsteps"] = Rcpp::wrap(x.equilibrium_nsteps);
  ret["equilibrium_eps"] = Rcpp::wrap(x.equilibrium_eps);
  ret["equilibrium_large_seed_rain_change"] = Rcpp::wrap(x.equilibrium_large_seed_rain_change);
  ret["equilibrium_progress"] = Rcpp::wrap(x.equilibrium_progress);
  ret["equilibrium_verbose"] = Rcpp::wrap(x.equilibrium_verbose);
  ret["equilibrium_solver"] = Rcpp::wrap(x.equilibrium_solver);
  ret["equilibrium_extinct_seed_rain"] = Rcpp::wrap(x.equilibrium_extinct_seed_rain);
  ret["equilibrium_runsteady_tol"] = Rcpp::wrap(x.equilibrium_runsteady_tol);
  ret["equilibrium_inviable_test_eps"] = Rcpp::wrap(x.equilibrium_inviable_test_eps);
  ret["equilibrium_nattempts"] = Rcpp::wrap(x.equilibrium_nattempts);
  ret["equilibrium_solver_logN"] = Rcpp::wrap(x.equilibrium_solver_logN);
  ret["equilibrium_solver_try_keep"] = Rcpp::wrap(x.equilibrium_solver_try_keep);
  ret.attr("class") = "Control";
  return ret;
}
template <> inline tree2::Control as(SEXP x) {
  if (!tree2::RcppR6::is<tree2::Control >(x)) {
    Rcpp::stop("Expected an object of type Control");
    // NOTE: Won't drop through or return anything.
  }
  // NOTE: assumes default constructable, and will assign *every*
  // field twice.  No current support for a hook.
  tree2::Control ret;
  Rcpp::List xl(x);
  // ret.plant_assimilation_adaptive = Rcpp::as<decltype(retplant_assimilation_adaptive) >(xl["plant_assimilation_adaptive"]);
  ret.plant_assimilation_adaptive = Rcpp::as<bool >(xl["plant_assimilation_adaptive"]);
  // ret.plant_assimilation_over_distribution = Rcpp::as<decltype(retplant_assimilation_over_distribution) >(xl["plant_assimilation_over_distribution"]);
  ret.plant_assimilation_over_distribution = Rcpp::as<bool >(xl["plant_assimilation_over_distribution"]);
  // ret.plant_assimilation_tol = Rcpp::as<decltype(retplant_assimilation_tol) >(xl["plant_assimilation_tol"]);
  ret.plant_assimilation_tol = Rcpp::as<double >(xl["plant_assimilation_tol"]);
  // ret.plant_assimilation_iterations = Rcpp::as<decltype(retplant_assimilation_iterations) >(xl["plant_assimilation_iterations"]);
  ret.plant_assimilation_iterations = Rcpp::as<size_t >(xl["plant_assimilation_iterations"]);
  // ret.plant_assimilation_rule = Rcpp::as<decltype(retplant_assimilation_rule) >(xl["plant_assimilation_rule"]);
  ret.plant_assimilation_rule = Rcpp::as<size_t >(xl["plant_assimilation_rule"]);
  // ret.plant_assimilation_reuse_intervals = Rcpp::as<decltype(retplant_assimilation_reuse_intervals) >(xl["plant_assimilation_reuse_intervals"]);
  ret.plant_assimilation_reuse_intervals = Rcpp::as<bool >(xl["plant_assimilation_reuse_intervals"]);
  // ret.plant_assimilation_approximate_use = Rcpp::as<decltype(retplant_assimilation_approximate_use) >(xl["plant_assimilation_approximate_use"]);
  ret.plant_assimilation_approximate_use = Rcpp::as<bool >(xl["plant_assimilation_approximate_use"]);
  // ret.plant_assimilation_approximate_tol = Rcpp::as<decltype(retplant_assimilation_approximate_tol) >(xl["plant_assimilation_approximate_tol"]);
  ret.plant_assimilation_approximate_tol = Rcpp::as<double >(xl["plant_assimilation_approximate_tol"]);
  // ret.plant_assimilation_approximate_nbase = Rcpp::as<decltype(retplant_assimilation_approximate_nbase) >(xl["plant_assimilation_approximate_nbase"]);
  ret.plant_assimilation_approximate_nbase = Rcpp::as<int >(xl["plant_assimilation_approximate_nbase"]);
  // ret.plant_assimilation_approximate_max_depth = Rcpp::as<decltype(retplant_assimilation_approximate_max_depth) >(xl["plant_assimilation_approximate_max_depth"]);
  ret.plant_assimilation_approximate_max_depth = Rcpp::as<int >(xl["plant_assimilation_approximate_max_depth"]);
  // ret.plant_assimilation_approximate_akima = Rcpp::as<decltype(retplant_assimilation_approximate_akima) >(xl["plant_assimilation_approximate_akima"]);
  ret.plant_assimilation_approximate_akima = Rcpp::as<bool >(xl["plant_assimilation_approximate_akima"]);
  // ret.plant_assimilation_approximate_linear = Rcpp::as<decltype(retplant_assimilation_approximate_linear) >(xl["plant_assimilation_approximate_linear"]);
  ret.plant_assimilation_approximate_linear = Rcpp::as<bool >(xl["plant_assimilation_approximate_linear"]);
  // ret.plant_assimilation_approximate_rescale_usually = Rcpp::as<decltype(retplant_assimilation_approximate_rescale_usually) >(xl["plant_assimilation_approximate_rescale_usually"]);
  ret.plant_assimilation_approximate_rescale_usually = Rcpp::as<bool >(xl["plant_assimilation_approximate_rescale_usually"]);
  // ret.plant_seed_tol = Rcpp::as<decltype(retplant_seed_tol) >(xl["plant_seed_tol"]);
  ret.plant_seed_tol = Rcpp::as<double >(xl["plant_seed_tol"]);
  // ret.plant_seed_iterations = Rcpp::as<decltype(retplant_seed_iterations) >(xl["plant_seed_iterations"]);
  ret.plant_seed_iterations = Rcpp::as<int >(xl["plant_seed_iterations"]);
  // ret.cohort_gradient_eps = Rcpp::as<decltype(retcohort_gradient_eps) >(xl["cohort_gradient_eps"]);
  ret.cohort_gradient_eps = Rcpp::as<double >(xl["cohort_gradient_eps"]);
  // ret.cohort_gradient_direction = Rcpp::as<decltype(retcohort_gradient_direction) >(xl["cohort_gradient_direction"]);
  ret.cohort_gradient_direction = Rcpp::as<int >(xl["cohort_gradient_direction"]);
  // ret.cohort_gradient_richardson = Rcpp::as<decltype(retcohort_gradient_richardson) >(xl["cohort_gradient_richardson"]);
  ret.cohort_gradient_richardson = Rcpp::as<bool >(xl["cohort_gradient_richardson"]);
  // ret.cohort_gradient_richardson_depth = Rcpp::as<decltype(retcohort_gradient_richardson_depth) >(xl["cohort_gradient_richardson_depth"]);
  ret.cohort_gradient_richardson_depth = Rcpp::as<size_t >(xl["cohort_gradient_richardson_depth"]);
  // ret.environment_light_tol = Rcpp::as<decltype(retenvironment_light_tol) >(xl["environment_light_tol"]);
  ret.environment_light_tol = Rcpp::as<double >(xl["environment_light_tol"]);
  // ret.environment_light_nbase = Rcpp::as<decltype(retenvironment_light_nbase) >(xl["environment_light_nbase"]);
  ret.environment_light_nbase = Rcpp::as<int >(xl["environment_light_nbase"]);
  // ret.environment_light_max_depth = Rcpp::as<decltype(retenvironment_light_max_depth) >(xl["environment_light_max_depth"]);
  ret.environment_light_max_depth = Rcpp::as<int >(xl["environment_light_max_depth"]);
  // ret.environment_light_akima = Rcpp::as<decltype(retenvironment_light_akima) >(xl["environment_light_akima"]);
  ret.environment_light_akima = Rcpp::as<bool >(xl["environment_light_akima"]);
  // ret.environment_light_linear = Rcpp::as<decltype(retenvironment_light_linear) >(xl["environment_light_linear"]);
  ret.environment_light_linear = Rcpp::as<bool >(xl["environment_light_linear"]);
  // ret.environment_light_rescale_usually = Rcpp::as<decltype(retenvironment_light_rescale_usually) >(xl["environment_light_rescale_usually"]);
  ret.environment_light_rescale_usually = Rcpp::as<bool >(xl["environment_light_rescale_usually"]);
  // ret.environment_light_skip = Rcpp::as<decltype(retenvironment_light_skip) >(xl["environment_light_skip"]);
  ret.environment_light_skip = Rcpp::as<bool >(xl["environment_light_skip"]);
  // ret.ode_step_size_min = Rcpp::as<decltype(retode_step_size_min) >(xl["ode_step_size_min"]);
  ret.ode_step_size_min = Rcpp::as<double >(xl["ode_step_size_min"]);
  // ret.ode_step_size_max = Rcpp::as<decltype(retode_step_size_max) >(xl["ode_step_size_max"]);
  ret.ode_step_size_max = Rcpp::as<double >(xl["ode_step_size_max"]);
  // ret.ode_tol_rel = Rcpp::as<decltype(retode_tol_rel) >(xl["ode_tol_rel"]);
  ret.ode_tol_rel = Rcpp::as<double >(xl["ode_tol_rel"]);
  // ret.ode_tol_abs = Rcpp::as<decltype(retode_tol_abs) >(xl["ode_tol_abs"]);
  ret.ode_tol_abs = Rcpp::as<double >(xl["ode_tol_abs"]);
  // ret.ode_a_y = Rcpp::as<decltype(retode_a_y) >(xl["ode_a_y"]);
  ret.ode_a_y = Rcpp::as<double >(xl["ode_a_y"]);
  // ret.ode_a_dydt = Rcpp::as<decltype(retode_a_dydt) >(xl["ode_a_dydt"]);
  ret.ode_a_dydt = Rcpp::as<double >(xl["ode_a_dydt"]);
  // ret.schedule_nsteps = Rcpp::as<decltype(retschedule_nsteps) >(xl["schedule_nsteps"]);
  ret.schedule_nsteps = Rcpp::as<int >(xl["schedule_nsteps"]);
  // ret.schedule_eps = Rcpp::as<decltype(retschedule_eps) >(xl["schedule_eps"]);
  ret.schedule_eps = Rcpp::as<double >(xl["schedule_eps"]);
  // ret.schedule_progress = Rcpp::as<decltype(retschedule_progress) >(xl["schedule_progress"]);
  ret.schedule_progress = Rcpp::as<bool >(xl["schedule_progress"]);
  // ret.schedule_verbose = Rcpp::as<decltype(retschedule_verbose) >(xl["schedule_verbose"]);
  ret.schedule_verbose = Rcpp::as<bool >(xl["schedule_verbose"]);
  // ret.schedule_default_patch_survival = Rcpp::as<decltype(retschedule_default_patch_survival) >(xl["schedule_default_patch_survival"]);
  ret.schedule_default_patch_survival = Rcpp::as<double >(xl["schedule_default_patch_survival"]);
  // ret.schedule_default_multipler = Rcpp::as<decltype(retschedule_default_multipler) >(xl["schedule_default_multipler"]);
  ret.schedule_default_multipler = Rcpp::as<double >(xl["schedule_default_multipler"]);
  // ret.schedule_default_min_step_size = Rcpp::as<decltype(retschedule_default_min_step_size) >(xl["schedule_default_min_step_size"]);
  ret.schedule_default_min_step_size = Rcpp::as<double >(xl["schedule_default_min_step_size"]);
  // ret.schedule_default_max_step_size = Rcpp::as<decltype(retschedule_default_max_step_size) >(xl["schedule_default_max_step_size"]);
  ret.schedule_default_max_step_size = Rcpp::as<double >(xl["schedule_default_max_step_size"]);
  // ret.equilibrium_nsteps = Rcpp::as<decltype(retequilibrium_nsteps) >(xl["equilibrium_nsteps"]);
  ret.equilibrium_nsteps = Rcpp::as<int >(xl["equilibrium_nsteps"]);
  // ret.equilibrium_eps = Rcpp::as<decltype(retequilibrium_eps) >(xl["equilibrium_eps"]);
  ret.equilibrium_eps = Rcpp::as<double >(xl["equilibrium_eps"]);
  // ret.equilibrium_large_seed_rain_change = Rcpp::as<decltype(retequilibrium_large_seed_rain_change) >(xl["equilibrium_large_seed_rain_change"]);
  ret.equilibrium_large_seed_rain_change = Rcpp::as<double >(xl["equilibrium_large_seed_rain_change"]);
  // ret.equilibrium_progress = Rcpp::as<decltype(retequilibrium_progress) >(xl["equilibrium_progress"]);
  ret.equilibrium_progress = Rcpp::as<bool >(xl["equilibrium_progress"]);
  // ret.equilibrium_verbose = Rcpp::as<decltype(retequilibrium_verbose) >(xl["equilibrium_verbose"]);
  ret.equilibrium_verbose = Rcpp::as<bool >(xl["equilibrium_verbose"]);
  // ret.equilibrium_solver = Rcpp::as<decltype(retequilibrium_solver) >(xl["equilibrium_solver"]);
  ret.equilibrium_solver = Rcpp::as<int >(xl["equilibrium_solver"]);
  // ret.equilibrium_extinct_seed_rain = Rcpp::as<decltype(retequilibrium_extinct_seed_rain) >(xl["equilibrium_extinct_seed_rain"]);
  ret.equilibrium_extinct_seed_rain = Rcpp::as<double >(xl["equilibrium_extinct_seed_rain"]);
  // ret.equilibrium_runsteady_tol = Rcpp::as<decltype(retequilibrium_runsteady_tol) >(xl["equilibrium_runsteady_tol"]);
  ret.equilibrium_runsteady_tol = Rcpp::as<double >(xl["equilibrium_runsteady_tol"]);
  // ret.equilibrium_inviable_test_eps = Rcpp::as<decltype(retequilibrium_inviable_test_eps) >(xl["equilibrium_inviable_test_eps"]);
  ret.equilibrium_inviable_test_eps = Rcpp::as<double >(xl["equilibrium_inviable_test_eps"]);
  // ret.equilibrium_nattempts = Rcpp::as<decltype(retequilibrium_nattempts) >(xl["equilibrium_nattempts"]);
  ret.equilibrium_nattempts = Rcpp::as<int >(xl["equilibrium_nattempts"]);
  // ret.equilibrium_solver_logN = Rcpp::as<decltype(retequilibrium_solver_logN) >(xl["equilibrium_solver_logN"]);
  ret.equilibrium_solver_logN = Rcpp::as<bool >(xl["equilibrium_solver_logN"]);
  // ret.equilibrium_solver_try_keep = Rcpp::as<decltype(retequilibrium_solver_try_keep) >(xl["equilibrium_solver_try_keep"]);
  ret.equilibrium_solver_try_keep = Rcpp::as<bool >(xl["equilibrium_solver_try_keep"]);
  return ret;
}

template <> inline SEXP wrap(const ode::OdeControl& x) {
  Rcpp::List ret;
  ret["tol_abs"] = Rcpp::wrap(x.tol_abs);
  ret["tol_rel"] = Rcpp::wrap(x.tol_rel);
  ret["a_y"] = Rcpp::wrap(x.a_y);
  ret["a_dydt"] = Rcpp::wrap(x.a_dydt);
  ret["step_size_min"] = Rcpp::wrap(x.step_size_min);
  ret["step_size_max"] = Rcpp::wrap(x.step_size_max);
  ret["step_size_initial"] = Rcpp::wrap(x.step_size_initial);
  ret.attr("class") = "OdeControl";
  return ret;
}
template <> inline ode::OdeControl as(SEXP x) {
  if (!tree2::RcppR6::is<ode::OdeControl >(x)) {
    Rcpp::stop("Expected an object of type OdeControl");
    // NOTE: Won't drop through or return anything.
  }
  // NOTE: assumes default constructable, and will assign *every*
  // field twice.  No current support for a hook.
  ode::OdeControl ret;
  Rcpp::List xl(x);
  // ret.tol_abs = Rcpp::as<decltype(rettol_abs) >(xl["tol_abs"]);
  ret.tol_abs = Rcpp::as<double >(xl["tol_abs"]);
  // ret.tol_rel = Rcpp::as<decltype(rettol_rel) >(xl["tol_rel"]);
  ret.tol_rel = Rcpp::as<double >(xl["tol_rel"]);
  // ret.a_y = Rcpp::as<decltype(reta_y) >(xl["a_y"]);
  ret.a_y = Rcpp::as<double >(xl["a_y"]);
  // ret.a_dydt = Rcpp::as<decltype(reta_dydt) >(xl["a_dydt"]);
  ret.a_dydt = Rcpp::as<double >(xl["a_dydt"]);
  // ret.step_size_min = Rcpp::as<decltype(retstep_size_min) >(xl["step_size_min"]);
  ret.step_size_min = Rcpp::as<double >(xl["step_size_min"]);
  // ret.step_size_max = Rcpp::as<decltype(retstep_size_max) >(xl["step_size_max"]);
  ret.step_size_max = Rcpp::as<double >(xl["step_size_max"]);
  // ret.step_size_initial = Rcpp::as<decltype(retstep_size_initial) >(xl["step_size_initial"]);
  ret.step_size_initial = Rcpp::as<double >(xl["step_size_initial"]);
  return ret;
}

template <> inline SEXP wrap(const tree2::Strategy& x) {
  Rcpp::List ret;
  ret["lma"] = Rcpp::wrap(x.lma);
  ret["rho"] = Rcpp::wrap(x.rho);
  ret["hmat"] = Rcpp::wrap(x.hmat);
  ret["s"] = Rcpp::wrap(x.s);
  ret["n_area"] = Rcpp::wrap(x.n_area);
  ret["lma_0"] = Rcpp::wrap(x.lma_0);
  ret["rho_0"] = Rcpp::wrap(x.rho_0);
  ret["hmat_0"] = Rcpp::wrap(x.hmat_0);
  ret["s_0"] = Rcpp::wrap(x.s_0);
  ret["n_area_0"] = Rcpp::wrap(x.n_area_0);
  ret["eta"] = Rcpp::wrap(x.eta);
  ret["theta"] = Rcpp::wrap(x.theta);
  ret["a1"] = Rcpp::wrap(x.a1);
  ret["B1"] = Rcpp::wrap(x.B1);
  ret["a3"] = Rcpp::wrap(x.a3);
  ret["k_l0"] = Rcpp::wrap(x.k_l0);
  ret["B4"] = Rcpp::wrap(x.B4);
  ret["k_s0"] = Rcpp::wrap(x.k_s0);
  ret["B5"] = Rcpp::wrap(x.B5);
  ret["b"] = Rcpp::wrap(x.b);
  ret["c_Rs"] = Rcpp::wrap(x.c_Rs);
  ret["c_Rb"] = Rcpp::wrap(x.c_Rb);
  ret["c_Rr"] = Rcpp::wrap(x.c_Rr);
  ret["c_Rl"] = Rcpp::wrap(x.c_Rl);
  ret["Y"] = Rcpp::wrap(x.Y);
  ret["c_bio"] = Rcpp::wrap(x.c_bio);
  ret["k_b"] = Rcpp::wrap(x.k_b);
  ret["k_r"] = Rcpp::wrap(x.k_r);
  ret["c_p1"] = Rcpp::wrap(x.c_p1);
  ret["c_p2"] = Rcpp::wrap(x.c_p2);
  ret["c_acc"] = Rcpp::wrap(x.c_acc);
  ret["B7"] = Rcpp::wrap(x.B7);
  ret["c_r1"] = Rcpp::wrap(x.c_r1);
  ret["c_r2"] = Rcpp::wrap(x.c_r2);
  ret["c_s0"] = Rcpp::wrap(x.c_s0);
  ret["c_d0"] = Rcpp::wrap(x.c_d0);
  ret["c_d1"] = Rcpp::wrap(x.c_d1);
  ret["B6"] = Rcpp::wrap(x.B6);
  ret["c_d2"] = Rcpp::wrap(x.c_d2);
  ret["c_d3"] = Rcpp::wrap(x.c_d3);
  ret["control"] = Rcpp::wrap(x.control);
  ret.attr("class") = "Strategy";
  return ret;
}
template <> inline tree2::Strategy as(SEXP x) {
  if (!tree2::RcppR6::is<tree2::Strategy >(x)) {
    Rcpp::stop("Expected an object of type Strategy");
    // NOTE: Won't drop through or return anything.
  }
  // NOTE: assumes default constructable, and will assign *every*
  // field twice.  No current support for a hook.
  tree2::Strategy ret;
  Rcpp::List xl(x);
  // ret.lma = Rcpp::as<decltype(retlma) >(xl["lma"]);
  ret.lma = Rcpp::as<double >(xl["lma"]);
  // ret.rho = Rcpp::as<decltype(retrho) >(xl["rho"]);
  ret.rho = Rcpp::as<double >(xl["rho"]);
  // ret.hmat = Rcpp::as<decltype(rethmat) >(xl["hmat"]);
  ret.hmat = Rcpp::as<double >(xl["hmat"]);
  // ret.s = Rcpp::as<decltype(rets) >(xl["s"]);
  ret.s = Rcpp::as<double >(xl["s"]);
  // ret.n_area = Rcpp::as<decltype(retn_area) >(xl["n_area"]);
  ret.n_area = Rcpp::as<double >(xl["n_area"]);
  // ret.lma_0 = Rcpp::as<decltype(retlma_0) >(xl["lma_0"]);
  ret.lma_0 = Rcpp::as<double >(xl["lma_0"]);
  // ret.rho_0 = Rcpp::as<decltype(retrho_0) >(xl["rho_0"]);
  ret.rho_0 = Rcpp::as<double >(xl["rho_0"]);
  // ret.hmat_0 = Rcpp::as<decltype(rethmat_0) >(xl["hmat_0"]);
  ret.hmat_0 = Rcpp::as<double >(xl["hmat_0"]);
  // ret.s_0 = Rcpp::as<decltype(rets_0) >(xl["s_0"]);
  ret.s_0 = Rcpp::as<double >(xl["s_0"]);
  // ret.n_area_0 = Rcpp::as<decltype(retn_area_0) >(xl["n_area_0"]);
  ret.n_area_0 = Rcpp::as<double >(xl["n_area_0"]);
  // ret.eta = Rcpp::as<decltype(reteta) >(xl["eta"]);
  ret.eta = Rcpp::as<double >(xl["eta"]);
  // ret.theta = Rcpp::as<decltype(rettheta) >(xl["theta"]);
  ret.theta = Rcpp::as<double >(xl["theta"]);
  // ret.a1 = Rcpp::as<decltype(reta1) >(xl["a1"]);
  ret.a1 = Rcpp::as<double >(xl["a1"]);
  // ret.B1 = Rcpp::as<decltype(retB1) >(xl["B1"]);
  ret.B1 = Rcpp::as<double >(xl["B1"]);
  // ret.a3 = Rcpp::as<decltype(reta3) >(xl["a3"]);
  ret.a3 = Rcpp::as<double >(xl["a3"]);
  // ret.k_l0 = Rcpp::as<decltype(retk_l0) >(xl["k_l0"]);
  ret.k_l0 = Rcpp::as<double >(xl["k_l0"]);
  // ret.B4 = Rcpp::as<decltype(retB4) >(xl["B4"]);
  ret.B4 = Rcpp::as<double >(xl["B4"]);
  // ret.k_s0 = Rcpp::as<decltype(retk_s0) >(xl["k_s0"]);
  ret.k_s0 = Rcpp::as<double >(xl["k_s0"]);
  // ret.B5 = Rcpp::as<decltype(retB5) >(xl["B5"]);
  ret.B5 = Rcpp::as<double >(xl["B5"]);
  // ret.b = Rcpp::as<decltype(retb) >(xl["b"]);
  ret.b = Rcpp::as<double >(xl["b"]);
  // ret.c_Rs = Rcpp::as<decltype(retc_Rs) >(xl["c_Rs"]);
  ret.c_Rs = Rcpp::as<double >(xl["c_Rs"]);
  // ret.c_Rb = Rcpp::as<decltype(retc_Rb) >(xl["c_Rb"]);
  ret.c_Rb = Rcpp::as<double >(xl["c_Rb"]);
  // ret.c_Rr = Rcpp::as<decltype(retc_Rr) >(xl["c_Rr"]);
  ret.c_Rr = Rcpp::as<double >(xl["c_Rr"]);
  // ret.c_Rl = Rcpp::as<decltype(retc_Rl) >(xl["c_Rl"]);
  ret.c_Rl = Rcpp::as<double >(xl["c_Rl"]);
  // ret.Y = Rcpp::as<decltype(retY) >(xl["Y"]);
  ret.Y = Rcpp::as<double >(xl["Y"]);
  // ret.c_bio = Rcpp::as<decltype(retc_bio) >(xl["c_bio"]);
  ret.c_bio = Rcpp::as<double >(xl["c_bio"]);
  // ret.k_b = Rcpp::as<decltype(retk_b) >(xl["k_b"]);
  ret.k_b = Rcpp::as<double >(xl["k_b"]);
  // ret.k_r = Rcpp::as<decltype(retk_r) >(xl["k_r"]);
  ret.k_r = Rcpp::as<double >(xl["k_r"]);
  // ret.c_p1 = Rcpp::as<decltype(retc_p1) >(xl["c_p1"]);
  ret.c_p1 = Rcpp::as<double >(xl["c_p1"]);
  // ret.c_p2 = Rcpp::as<decltype(retc_p2) >(xl["c_p2"]);
  ret.c_p2 = Rcpp::as<double >(xl["c_p2"]);
  // ret.c_acc = Rcpp::as<decltype(retc_acc) >(xl["c_acc"]);
  ret.c_acc = Rcpp::as<double >(xl["c_acc"]);
  // ret.B7 = Rcpp::as<decltype(retB7) >(xl["B7"]);
  ret.B7 = Rcpp::as<double >(xl["B7"]);
  // ret.c_r1 = Rcpp::as<decltype(retc_r1) >(xl["c_r1"]);
  ret.c_r1 = Rcpp::as<double >(xl["c_r1"]);
  // ret.c_r2 = Rcpp::as<decltype(retc_r2) >(xl["c_r2"]);
  ret.c_r2 = Rcpp::as<double >(xl["c_r2"]);
  // ret.c_s0 = Rcpp::as<decltype(retc_s0) >(xl["c_s0"]);
  ret.c_s0 = Rcpp::as<double >(xl["c_s0"]);
  // ret.c_d0 = Rcpp::as<decltype(retc_d0) >(xl["c_d0"]);
  ret.c_d0 = Rcpp::as<double >(xl["c_d0"]);
  // ret.c_d1 = Rcpp::as<decltype(retc_d1) >(xl["c_d1"]);
  ret.c_d1 = Rcpp::as<double >(xl["c_d1"]);
  // ret.B6 = Rcpp::as<decltype(retB6) >(xl["B6"]);
  ret.B6 = Rcpp::as<double >(xl["B6"]);
  // ret.c_d2 = Rcpp::as<decltype(retc_d2) >(xl["c_d2"]);
  ret.c_d2 = Rcpp::as<double >(xl["c_d2"]);
  // ret.c_d3 = Rcpp::as<decltype(retc_d3) >(xl["c_d3"]);
  ret.c_d3 = Rcpp::as<double >(xl["c_d3"]);
  // ret.control = Rcpp::as<decltype(retcontrol) >(xl["control"]);
  ret.control = Rcpp::as<tree2::Control >(xl["control"]);
  return ret;
}

template <> inline SEXP wrap(const tree2::Parameters& x) {
  Rcpp::List ret;
  ret["c_ext"] = Rcpp::wrap(x.c_ext);
  ret["patch_area"] = Rcpp::wrap(x.patch_area);
  ret["Pi_0"] = Rcpp::wrap(x.Pi_0);
  ret["n_patches"] = Rcpp::wrap(x.n_patches);
  ret["strategies"] = Rcpp::wrap(x.strategies);
  ret["seed_rain"] = Rcpp::wrap(x.seed_rain);
  ret["is_resident"] = Rcpp::wrap(x.is_resident);
  ret["disturbance"] = Rcpp::wrap(x.disturbance);
  ret["control"] = Rcpp::wrap(x.control);
  ret["strategy_default"] = Rcpp::wrap(x.strategy_default);
  ret.attr("class") = "Parameters";
  return ret;
}
template <> inline tree2::Parameters as(SEXP x) {
  if (!tree2::RcppR6::is<tree2::Parameters >(x)) {
    Rcpp::stop("Expected an object of type Parameters");
    // NOTE: Won't drop through or return anything.
  }
  // NOTE: assumes default constructable, and will assign *every*
  // field twice.  No current support for a hook.
  tree2::Parameters ret;
  Rcpp::List xl(x);
  // ret.c_ext = Rcpp::as<decltype(retc_ext) >(xl["c_ext"]);
  ret.c_ext = Rcpp::as<double >(xl["c_ext"]);
  // ret.patch_area = Rcpp::as<decltype(retpatch_area) >(xl["patch_area"]);
  ret.patch_area = Rcpp::as<double >(xl["patch_area"]);
  // ret.Pi_0 = Rcpp::as<decltype(retPi_0) >(xl["Pi_0"]);
  ret.Pi_0 = Rcpp::as<double >(xl["Pi_0"]);
  // ret.n_patches = Rcpp::as<decltype(retn_patches) >(xl["n_patches"]);
  ret.n_patches = Rcpp::as<size_t >(xl["n_patches"]);
  // ret.strategies = Rcpp::as<decltype(retstrategies) >(xl["strategies"]);
  ret.strategies = Rcpp::as<std::vector<tree2::Strategy> >(xl["strategies"]);
  // ret.seed_rain = Rcpp::as<decltype(retseed_rain) >(xl["seed_rain"]);
  ret.seed_rain = Rcpp::as<std::vector<double> >(xl["seed_rain"]);
  // ret.is_resident = Rcpp::as<decltype(retis_resident) >(xl["is_resident"]);
  ret.is_resident = Rcpp::as<std::vector<bool> >(xl["is_resident"]);
  // ret.disturbance = Rcpp::as<decltype(retdisturbance) >(xl["disturbance"]);
  ret.disturbance = Rcpp::as<tree2::Disturbance >(xl["disturbance"]);
  // ret.control = Rcpp::as<decltype(retcontrol) >(xl["control"]);
  ret.control = Rcpp::as<tree2::Control >(xl["control"]);
  // ret.strategy_default = Rcpp::as<decltype(retstrategy_default) >(xl["strategy_default"]);
  ret.strategy_default = Rcpp::as<tree2::Strategy >(xl["strategy_default"]);
  return ret;
}

template <> inline SEXP wrap(const quadrature::QK& x) {
  return wrap(tree2::RcppR6::RcppR6<quadrature::QK>(x));
}
template <> inline quadrature::QK as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<quadrature::QK>(x));
}

template <> inline SEXP wrap(const quadrature::QAG& x) {
  return wrap(tree2::RcppR6::RcppR6<quadrature::QAG>(x));
}
template <> inline quadrature::QAG as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<quadrature::QAG>(x));
}

template <> inline SEXP wrap(const interpolator::Interpolator& x) {
  return wrap(tree2::RcppR6::RcppR6<interpolator::Interpolator>(x));
}
template <> inline interpolator::Interpolator as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<interpolator::Interpolator>(x));
}

template <> inline SEXP wrap(const tree2::Environment& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::Environment>(x));
}
template <> inline tree2::Environment as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::Environment>(x));
}

template <> inline SEXP wrap(const tree2::Plant& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::Plant>(x));
}
template <> inline tree2::Plant as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::Plant>(x));
}

template <> inline SEXP wrap(const tree2::Cohort<tree2::Plant>& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::Cohort<tree2::Plant> >(x));
}
template <> inline tree2::Cohort<tree2::Plant> as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::Cohort<tree2::Plant> >(x));
}

template <> inline SEXP wrap(const tree2::Species<tree2::Cohort<tree2::Plant> >& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::Species<tree2::Cohort<tree2::Plant> > >(x));
}
template <> inline tree2::Species<tree2::Cohort<tree2::Plant> > as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::Species<tree2::Cohort<tree2::Plant> > >(x));
}

template <> inline SEXP wrap(const tree2::Patch<tree2::Cohort<tree2::Plant> >& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::Patch<tree2::Cohort<tree2::Plant> > >(x));
}
template <> inline tree2::Patch<tree2::Cohort<tree2::Plant> > as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::Patch<tree2::Cohort<tree2::Plant> > >(x));
}

template <> inline SEXP wrap(const tree2::EBT<tree2::Plant>& x) {
  return wrap(tree2::RcppR6::RcppR6<tree2::EBT<tree2::Plant> >(x));
}
template <> inline tree2::EBT<tree2::Plant> as(SEXP x) {
  return *(tree2::RcppR6::RcppR6<tree2::EBT<tree2::Plant> >(x));
}
}

#endif
