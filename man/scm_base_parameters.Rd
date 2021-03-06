% Generated by roxygen2: do not edit by hand
% Please edit documentation in r/scm_support.R
\name{scm_base_parameters}
\alias{scm_base_parameters}
\title{Sensible, fast (ish) SCM parameters}
\usage{
scm_base_parameters(type = "FF16", env = environment_type(type))
}
\arguments{
<<<<<<< HEAD
\item{type}{Either \code{"FF16"}, \code{"FF16r"}, or  \code{"FF16FvCB"}.}
=======
\item{type}{Name of model (defaults to FF16 but any strategy name is valid).}
>>>>>>> upstream/master
}
\description{
Hopefully sensible set of parameters for use with the SCM.  Turns
accuracy down a bunch, makes it noisy, sets up the
hyperparameterisation that we most often use.
}
\author{
Rich FitzJohn
}
