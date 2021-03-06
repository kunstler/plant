% Generated by roxygen2: do not edit by hand
% Please edit documentation in r/util_model.R
\name{strategy_list}
\alias{strategy_list}
\alias{strategy_default}
\alias{strategy}
\alias{individual_list}
\title{Create a list of Strategies}
\usage{
strategy_list(x, parameters, hyperpar = param_hyperpar(parameters))

strategy_default(parameters, hyperpar = param_hyperpar(parameters))

strategy(x, parameters, hyperpar = param_hyperpar(parameters))

individual_list(x, parameters, hyperpar = parram_hyperpar(parameters))
}
\arguments{
\item{x}{Values for the trait.  This must be a \emph{matrix}, with
column names corresponding to entries in \code{Strategy} and
rows representing different values.}

\item{parameters}{\code{Parameters} object containing a
default strategy to modify.  Any hyperparameterisation included
will be applied.}
}
\description{
Create a list of Strategies or Plants by varying a single trait.
}
