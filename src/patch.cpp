#include "patch.h"

namespace model {

PatchBase::~PatchBase() {
}

SEXP patch(Rcpp::CppClass individual, Parameters p) {
  std::string individual_type =
    util::rcpp_class_demangle(Rcpp::as<std::string>(individual));
  SEXP ret = R_NilValue;
  if (individual_type == "Plant") {
    Patch<Plant> obj(p);
    ret = Rcpp::wrap(obj);
  } else if (individual_type == "CohortDiscrete") {
    Patch<CohortDiscrete> obj(p);
    ret = Rcpp::wrap(obj);
  } else if (individual_type == "CohortTop") {
    Patch<CohortTop> obj(p);
    ret = Rcpp::wrap(obj);
  } else {
    Rcpp::stop("Cannot make Patch of " + individual_type);
  }
  return ret;
}

}
