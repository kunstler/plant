## We can probably actually do better than this with an S3 method on
## the actual strategy?  That would need to be organised by the
## templating though and that's stretched to the limit.

##' Create a FF16FvCB Plant or Cohort
##' @title Create a FF16FvCB Plant or Cohort
##' @param s A \code{\link{FF16FvCB_Strategy}} object
##' @export
##' @rdname FF16FvCB
##' @examples
##' pl <- FF16FvCB_Plant()
##' pl$height
FF16FvCB_Plant <- function(s=FF16FvCB_Strategy()) {
  Plant("FF16FvCB")(s)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_Cohort <- function(s=FF16FvCB_Strategy()) {
  Cohort("FF16FvCB")(s)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_Species <- function(s=FF16FvCB_Strategy()) {
  Species("FF16FvCB")(s)
}

##' @export
##' @rdname FF16FvCB
##' @param ... Arguments!
FF16FvCB_Parameters <- function(...) {
  Parameters("FF16FvCB")(...)
}

##' @export
##' @rdname FF16FvCB
##' @param p A \code{Parameters<FF16FvCB>} object
FF16FvCB_Patch <- function(p) {
  Patch("FF16FvCB")(p)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_SCM <- function(p) {
  SCM("FF16FvCB")(p)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_StochasticSpecies <- function(s=FF16FvCB_Strategy()) {
  StochasticSpecies("FF16FvCB")(s)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_StochasticPatch <- function(p) {
  StochasticPatch("FF16FvCB")(p)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_StochasticPatchRunner <- function(p) {
  StochasticPatchRunner("FF16FvCB")(p)
}

##' @export
##' @rdname FF16FvCB
FF16FvCB_PlantPlus <- function(s=FF16FvCB_Strategy()) {
  PlantPlus("FF16FvCB")(s)
}

## Helper:
##' @export
##' @rdname Environment
##' @param p A Parameters object
make_environment <- function(p) {
  Environment(p$disturbance_mean_interval,
              p$seed_rain,
              p$control)
}

##' Hyperparameters for FF16FvCB physiological model
##' @title Hyperparameters for FF16FvCB physiological model
##' @param lma_0 Central (mean) value for leaf mass per area [kg /m2]
##' @param B_kl1 Rate of leaf turnover at lma_0 [/yr]
##' @param B_kl2 Scaling slope for phi in leaf turnover [dimensionless]
##' @param rho_0 Central (mean) value for wood density [kg /m3]
##' @param B_dI1 Rate of instantaneous mortality at rho_0 [/yr]
##' @param B_dI2 Scaling slope for wood density in intrinsic mortality [dimensionless]
##' @param B_ks1 Rate of sapwood turnover at rho_0 [/yr]
##' @param B_ks2 Scaling slope for rho in sapwood turnover [dimensionless]
##' @param B_rs1 CO_2 respiration per unit sapwood volume [mol / yr / m3 ]
##' @param B_rb1 CO_2 respiration per unit sapwood volume [mol / yr / m3 ]
##' @param B_f1 Cost of seed accessories per unit seed mass [dimensionless]
##' @param narea nitrogen per leaf area [kg / m2]
##' @param narea_0 central (mean) value for nitrogen per leaf area [kg / m2]
##' @param B_lf1 Maximum carboxylation rate at 25 degrees C vs leaf nitrogen parameter 1 [mu mol m-2 s-1]
##' @param B_lf2 Curvature of leaf photosynthetic light response curve [dimensionless]
##' @param B_lf3 Quantum yield of electron transport [mol mol-1]
##' @param B_lf4 CO_2 respiration per unit leaf nitrogen [mol / yr / kg]
##' @param B_lf5 Vcmax scaling exponent for leaf nitrogen [dimensionless]
##' @param B_lf6 Jmax vs Vcmax comversion factor [dimensionless]
##' @param B_lf7 Scaling slope for Jmax vs Vcmax [dimensionless]
##' @param k_I light extinction coefficient [dimensionless]
##' @param latitude degrees from equator (0-90), used in solar model [deg]
##' @param vpd Vapour pressure deficit [kPa]
##' @param Tleaf Leaf temperature [degrees C]
##' @export
##' @rdname FF16FvCB_hyperpar
##' @import plantecophys
##' @import nlmrt
make_FF16FvCB_hyperpar <- function(lma_0=0.1978791,
                                      B_kl1=0.4565855,
                                      B_kl2=1.71,
                                      rho_0=608.0,
                                      B_dI1=0.01,
                                      B_dI2=0.0,
                                      B_ks1=0.2,
                                      B_ks2=0.0,
                                      B_rs1=4012.0,
                                      B_rb1=2.0*4012.0,
                                      B_f1 =3.0,
                                      narea=1.87e-3,
                                      narea_0=1.87e-3,
                                      B_lf1= 31.62 *1000^0.801, # http://doi.wiley.com/10.1111/gcb.12870 conversion of Narea in g m-2
                                      B_lf2=0.7,
                                      B_lf3=0.3,
                                      B_lf4=21000,
                                      B_lf5=0.801, # http://doi.wiley.com/10.1111/gcb.12870
                                      B_lf6=1.67, # Medlyn et al. 2002 / for Walker 1.01
                                      B_lf7 = 1, # Medlyn et al. 2002 / for Walker 0.89
                                      k_I=0.5, latitude=0, vpd = 0, Tleaf= 25) {
  assert_scalar <- function(x, name=deparse(substitute(x))) {
    if (length(x) != 1L) {
      stop(sprintf("%s must be a scalar", name), call. = FALSE)
    }
  }
  assert_scalar(lma_0)
  assert_scalar(B_kl1)
  assert_scalar(B_kl2)
  assert_scalar(rho_0)
  assert_scalar(B_dI1)
  assert_scalar(B_dI2)
  assert_scalar(B_ks1)
  assert_scalar(B_ks2)
  assert_scalar(B_rs1)
  assert_scalar(B_rb1)
  assert_scalar(B_f1)
  assert_scalar(narea)
  assert_scalar(narea_0)
  assert_scalar(B_lf1)
  assert_scalar(B_lf2)
  assert_scalar(B_lf3)
  assert_scalar(B_lf4)
  assert_scalar(B_lf5)
  assert_scalar(B_lf6)
  assert_scalar(B_lf7)
  assert_scalar(k_I)
  assert_scalar(latitude)
  assert_scalar(vpd)
  assert_scalar(Tleaf)

  ## TODO: k_I should actually be in default parameter set, so perhaps don't pass into function?

  function(m, s, filter=TRUE) {
    with_default <- function(name, default_value=s[[name]]) {
      rep_len(if (name %in% colnames(m)) m[, name] else default_value,
              nrow(m))
    }
    lma       <- with_default("lma")
    rho       <- with_default("rho")
    omega     <- with_default("omega")
    narea     <- with_default("narea", narea)

    ## lma / leaf turnover relationship:
    k_l   <- B_kl1 * (lma / lma_0) ^ (-B_kl2)

    ## rho / mortality relationship:
    d_I  <- B_dI1 * (rho / rho_0) ^ (-B_dI2)

    ## rho / wood turnover relationship:
    k_s  <- B_ks1 *  (rho / rho_0) ^ (-B_ks2)

    ## rho / sapwood respiration relationship:

    ## Respiration rates are per unit mass, so this next line has the
    ## effect of holding constant the respiration rate per unit volume.
    ## So respiration rates per unit mass vary with rho, respiration
    ## rates per unit volume don't.
    r_s <- B_rs1 / rho
    # bark respiration follows from sapwood
    r_b <- B_rb1 / rho

    ## omega / accessory cost relationship
    a_f3 <- B_f1 * omega

    ## Narea, photosynthesis, respiration

    assimilation_FvCB <- function(I, V, vpd, Tleaf, alpha, theta, lf6, lf7) {
    df_pred <- Photosyn(PPFD=I *1e+06/(24*3600), # conversion of light in mu mol /m2 /s is it ok ?
                        VPD = vpd,
                        Tleaf = Tleaf,
                        Vcmax  = V,
                        Jmax  = lf6*V^lf7, # Jmax ~1.67 Vcmax in Medlyn et al. 20
                        alpha = alpha,
                        theta = theta,
                        gsmodel = "BBLeuning")
    return((df_pred$ALEAF + df_pred$Rd)*24 * 3600 / 1e+06)
    }


    ## Photosynthesis  [mol CO2 / m2 / yr]
    approximate_annual_assimilation <- function(narea, latitude, vpd, Tleaf) {
      E <- seq(0, 1, by=0.02)
      ## Only integrate over half year, as solar path is symmetrical
      D <- seq(0, 365/2, length.out = 10000)
      I <- PAR_given_solar_angle(solar_angle(D, latitude = abs(latitude)))

      Vcmax <- B_lf1 * (narea) ^  B_lf5
      theta <- B_lf2
      alpha <- B_lf3
      lf6   <- B_lf6
      lf7   <- B_lf7
      AA <- NA * E

      for (i in seq_len(length(E))) {
        AA[i] <- 2 * trapezium(D, assimilation_FvCB(
                                    k_I * I * E[i], Vcmax, vpd, Tleaf, alpha, theta, lf6, lf7))
      }
      if(all(diff(AA) < 1E-8)) {
        # line fitting will fail if all have are zero, or potentially same value
        ret <- c(last(AA), 0)
        names(ret) <- c("p1","p2", "p3")
      } else {
        fitxb2 <- nlxb(AA ~ (p1 +p2*E - sqrt((p1+p2*E)^2-4*p3*p2*E*p1))/(2*p3),
                           data = data.frame(E = E, AA = AA),
                           start = list(p1 = 500,
                                        p2 = 600,
                                        p3 = 0.8),
                           lower = 0.01,
                           upper = c(7000, 1200, 1))
        ret <- fitxb2$coefficients
        names(ret) <- c("p1","p2", "p3")
      }
      ret
    }

    # This needed in case narea has length zero, in which case trapezium fails
    a_p1 <- a_p2 <- a_p3 <- 0 * narea
    ## TODO: Remove the 0.5 hardcoded default for k_I here, and deal
    ## with this more nicely.
    if (length(narea) > 0 || k_I != 0.5) {
      i <- match(narea, unique(narea))
      y <- vapply(unique(narea), approximate_annual_assimilation,
                  numeric(3), latitude, vpd, Tleaf)
      a_p1  <- y["p1", i]
      a_p2  <- y["p2", i]
      a_p3  <- y["p3", i]
    }

    ## Respiration rates are per unit mass, so convert to mass-based
    ## rate by dividing with lma
    ## So respiration rates per unit mass vary with lma, while
    ## respiration rates per unit area don't.
    r_l  <- B_lf4 * narea / lma

    extra <- cbind(k_l,                # lma
                   d_I, k_s, r_s, r_b, # rho
                   a_f3,               # omega
                   a_p1, a_p2, a_p2,   # narea
                   r_l)                # lma, narea

    overlap <- intersect(colnames(m), colnames(extra))
    if (length(overlap) > 0L) {
      stop("Attempt to overwrite generated parameters: ",
           paste(overlap, collapse=", "))
    }

    ## Filter extra so that any column where all numbers are with eps
    ## of the default strategy are not replaced:
    if (filter) {
      if (nrow(extra) == 0L) {
        extra <- NULL
      } else {
        pos <- diff(apply(extra, 2, range)) == 0
        if (any(pos)) {
          eps <- sqrt(.Machine$double.eps)
          x1 <- extra[1, pos]
          x2 <- unlist(s[names(x1)])
          drop <- abs(x1 - x2) < eps & abs(1 - x1/x2) < eps
          if (any(drop)) {
            keep <- setdiff(colnames(extra), names(drop)[drop])
            extra <- extra[, keep, drop=FALSE]
          }
        }
      }
    }

    if (!is.null(extra)) {
      m <- cbind(m, extra)
    }
    m
  }
}

##' @rdname FF16FvCB_hyperpar
##' @export
##' @param m A trait matrix
##' @param s A default strategy
##' @param filter Logical, indicating if generated parameters that are
##' the same as the default should be removed.
FF16FvCB_hyperpar <- make_FF16FvCB_hyperpar()
