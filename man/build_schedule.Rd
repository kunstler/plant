% Generated by roxygen2: do not edit by hand
% Please edit documentation in r/build_schedule.R
\name{build_schedule}
\alias{build_schedule}
\title{Build Cohort Schedule}
\usage{
build_schedule(p)
}
\arguments{
\item{p}{Parameters object}
}
\value{
A Parameters object, with schedule components set.  The
output seed rain is also available as an attribute
\code{seed_rain}.
}
\description{
Build an appropriately refined schedule.
}
\details{
There are control options (within the \code{Parameters} object)
that affect how this function runs, in particular
\code{schedule_nsteps} and \code{schedule_eps} control how refined
the schedule will end up, and \code{schedule_verbose} controls if
details are printed to the screen during construction.
}
\author{
Rich FitzJohn
}
