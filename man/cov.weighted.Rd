\name{cov.weighted}
\alias{cov.weighted}
\title{Weighted covariance matrices}
\description{
  Returns a list containing estimates of the weighted mean and covariance matrix
  of the data.
}
\usage{
cov.weighted(x, weights = rep(1, nrow(x)))
}
\arguments{
  \item{x}{a matrix or data frame. As usual, rows are observations and columns are
    variables.}
  \item{weights}{a non-negative and non-zero vector of weights for each
    observation. Its length must equal the number of rows of \code{x}.}
}
\value{
  A list containing the following named components:
  \item{mean}{an estimate for the center (mean) of the data.}
  \item{cov}{the estimated (weighted) covariance matrix.}
}
\details{
  The covariance matrix is divided by the number of observations, which arise for
  instance, when we use the class of elliptical contoured distributions. Thus,
  \deqn{W_n = \sum\limits_{i=1}^n w_i, \qquad \overline{\bold{x}}_n = \frac{1}{W_n} 
    \sum\limits_{i=1}^n w_i\bold{x}_i \qquad \bold{S}_n = \frac{1}{n} \sum\limits_{i=1}^n 
    w_i (\bold{x}_i - \overline{\bold{x}}_n)(\bold{x}_i - \overline{\bold{x}}_n)^T.}
  This differs from the behaviour of function \code{\link{cov.wt}}. 
}
\seealso{
  \code{\link{cov.wt}}, \code{\link{cov}} and \code{\link{var}}.
}
\references{
  Clarke, M.R.B. (1971).
  Algorithm AS 41: Updating the sample mean and dispersion matrix.
  \emph{Applied Statistics} \bold{20}, 206-209.
}
\examples{
x <- cbind(1:10, c(1:3, 8:5, 8:10))
z0 <- cov.weighted(x) # all weights are 1
D2 <- Mahalanobis(x, center = z0$mean, cov = z0$cov)
p <- ncol(x)
wts <- (p + 1) / (1 + D2) # nice weights!
z1 <- cov.weighted(x, weights = wts)
z1
}
\keyword{multivariate}
