#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;
using namespace arma;

// [[Rcpp::export]]


arma::mat arma_distmat(arma::mat X) { 
  
  // Number of points
  int np = X.n_rows;
  
  // Initialize with zeros the matrix to store results
  arma::mat distmat; distmat.zeros(np, np);
  
  // Loop on all points 
  for (int i = 0; i < np; i++) {
    arma::vec p0 = X.row(i).t(); // fix a point 
    
    // Loop to calculate the distances between this point and the next ones  
    for (int j = i + 1; j < np; j++) {
      arma::vec p1 = X.row(j).t();
      arma::vec diff = p0 - p1; // (x0-x1,y0-y1)
      double squared_diff = as_scalar(diff.t() * diff); // (x0-x1)² + (y0-y1)²
      // Fill the distance matrix with the square root of precedent value
      distmat(j, i) = distmat(i, j) = sqrt(squared_diff);
    }
  }
  return distmat;
}


#include <Rcpp.h>
// arma_distmat
arma::mat arma_distmat(arma::mat X);
RcppExport SEXP sourceCpp_1_arma_distmat(SEXP XSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< arma::mat >::type X(XSEXP);
    rcpp_result_gen = Rcpp::wrap(arma_distmat(X));
    return rcpp_result_gen;
END_RCPP
}
