/* $ID: init.c, last updated 2021-03-03, F.Osorio */

#include "fastmatrix.h"
#include <R_ext/Rdynload.h>

#define CALLDEF(name, nargs)  {#name, (DL_FUNC) &name, nargs}
#define F77DEF(name, nargs)   {#name, (DL_FUNC) &F77_NAME(name), nargs}

static const R_CMethodDef CEntries[]  = {
  CALLDEF(central_moments,        6),
  CALLDEF(cg_solver,              9),
  CALLDEF(chol_dcmp,              5),
  CALLDEF(cov_MSSD,               5),
  CALLDEF(cov_weighted,           6),
  CALLDEF(dupl_cols,              2),
  CALLDEF(dupl_left_mult,         8),
  CALLDEF(dupl_left_trans,        9),
  CALLDEF(dupl_right_mult,        9),
  CALLDEF(dupl_right_trans,       8),
  CALLDEF(duplication_mat,        4),
  CALLDEF(geometric_mean,         3),
  CALLDEF(hadamard_prod,          4),
  CALLDEF(jacobi_solver,          9),
  CALLDEF(kronecker_prod,         7),
  CALLDEF(lu_dcmp,                5),
  CALLDEF(lu_inverse,             4),
  CALLDEF(lu_solve,               7),
  CALLDEF(mahal_distances,        7),
  CALLDEF(mat2vech,               4),
  CALLDEF(matrix_norm,            6),
  CALLDEF(norm_one,               4),
  CALLDEF(norm_two,               4),
  CALLDEF(norm_inf,               4),
  CALLDEF(norm_minkowski,         5),
  CALLDEF(OLS_cg,                 9),
  CALLDEF(OLS_qr,                10),
  CALLDEF(OLS_ridge,             20),
  CALLDEF(power_method,           9),
  CALLDEF(seidel_solver,          9),
  CALLDEF(sherman_morrison,       6),
  CALLDEF(skewness_and_kurtosis,  7),
  CALLDEF(svd_dcmp,              11),
  CALLDEF(sweep_operator,         6),
  CALLDEF(symmetrizer_prod,       6),
  CALLDEF(wilson_hilferty_chisq,  4),
  CALLDEF(whitening_chol,         4),
  {NULL, NULL, 0}
};

static const R_FortranMethodDef F77Entries[] = {
  F77DEF(arraymult,              14),
  F77DEF(bracketprod,            11),
  F77DEF(comm_rows,               3),
  F77DEF(comm_left_mult,         10),
  F77DEF(comm_right_mult,        10),
  F77DEF(commutation_mat,         6),
  F77DEF(equilibrate_cols,        8),
  F77DEF(inner_frobenius,         7),
  F77DEF(ldl_dcmp,                5),
  F77DEF(pivot_mat,               4),
  F77DEF(symmetrizer_mat,         8),
  {NULL, NULL, 0}
};

void R_init_fastmatrix(DllInfo *dll)
{
  /* Register the internal routines. We have no .Call or .External calls */
  R_registerRoutines(dll, CEntries, NULL, F77Entries, NULL);
  R_useDynamicSymbols(dll, FALSE);

  /* BLAS-1 wrappers callable from other packages */
  R_RegisterCCallable("fastmatrix", "BLAS1_axpy",               (DL_FUNC) &BLAS1_axpy);
  R_RegisterCCallable("fastmatrix", "BLAS1_copy",               (DL_FUNC) &BLAS1_copy);
  R_RegisterCCallable("fastmatrix", "BLAS1_dot_product",        (DL_FUNC) &BLAS1_dot_product);
  R_RegisterCCallable("fastmatrix", "BLAS1_index_max",          (DL_FUNC) &BLAS1_index_max);
  R_RegisterCCallable("fastmatrix", "BLAS1_norm_two",           (DL_FUNC) &BLAS1_norm_two);
  R_RegisterCCallable("fastmatrix", "BLAS1_scale",              (DL_FUNC) &BLAS1_scale);
  R_RegisterCCallable("fastmatrix", "BLAS1_sum_abs",            (DL_FUNC) &BLAS1_sum_abs);
  R_RegisterCCallable("fastmatrix", "BLAS1_swap",               (DL_FUNC) &BLAS1_swap);

  /* BLAS-2 wrappers callable from other packages */
  R_RegisterCCallable("fastmatrix", "BLAS2_gemv",               (DL_FUNC) &BLAS2_gemv);
  R_RegisterCCallable("fastmatrix", "BLAS2_symv",               (DL_FUNC) &BLAS2_symv);
  R_RegisterCCallable("fastmatrix", "BLAS2_trmv",               (DL_FUNC) &BLAS2_trmv);
  R_RegisterCCallable("fastmatrix", "BLAS2_trsv",               (DL_FUNC) &BLAS2_trsv);
  R_RegisterCCallable("fastmatrix", "BLAS2_ger",                (DL_FUNC) &BLAS2_ger);
  R_RegisterCCallable("fastmatrix", "BLAS2_syr",                (DL_FUNC) &BLAS2_syr);
  R_RegisterCCallable("fastmatrix", "BLAS2_syr2",               (DL_FUNC) &BLAS2_syr2);

  /* BLAS-3 wrappers callable from other packages */
  R_RegisterCCallable("fastmatrix", "BLAS3_gemm",               (DL_FUNC) &BLAS3_gemm);
  R_RegisterCCallable("fastmatrix", "BLAS3_symm",               (DL_FUNC) &BLAS3_symm);
  R_RegisterCCallable("fastmatrix", "BLAS3_syrk",               (DL_FUNC) &BLAS3_syrk);
  R_RegisterCCallable("fastmatrix", "BLAS3_trmm",               (DL_FUNC) &BLAS3_trmm);
  R_RegisterCCallable("fastmatrix", "BLAS3_trsm",               (DL_FUNC) &BLAS3_trsm);

  /*  operations on vectors */
  R_RegisterCCallable("fastmatrix", "FM_norm_sqr",              (DL_FUNC) &FM_norm_sqr);
  R_RegisterCCallable("fastmatrix", "FM_normalize",             (DL_FUNC) &FM_normalize);
  R_RegisterCCallable("fastmatrix", "FM_vecsum",                (DL_FUNC) &FM_vecsum);

  /* basic matrix manipulations */
  R_RegisterCCallable("fastmatrix", "FM_add_mat",               (DL_FUNC) &FM_add_mat);
  R_RegisterCCallable("fastmatrix", "FM_copy_mat",              (DL_FUNC) &FM_copy_mat);
  R_RegisterCCallable("fastmatrix", "FM_copy_trans",            (DL_FUNC) &FM_copy_trans);
  R_RegisterCCallable("fastmatrix", "FM_crossprod",             (DL_FUNC) &FM_crossprod);
  R_RegisterCCallable("fastmatrix", "FM_GAXPY",                 (DL_FUNC) &FM_GAXPY);
  R_RegisterCCallable("fastmatrix", "FM_logAbsDet",             (DL_FUNC) &FM_logAbsDet);
  R_RegisterCCallable("fastmatrix", "FM_mult_mat",              (DL_FUNC) &FM_mult_mat);
  R_RegisterCCallable("fastmatrix", "FM_mult_triangular",       (DL_FUNC) &FM_mult_triangular);
  R_RegisterCCallable("fastmatrix", "FM_rank1_update",          (DL_FUNC) &FM_rank1_update);
  R_RegisterCCallable("fastmatrix", "FM_scale_mat",             (DL_FUNC) &FM_scale_mat);
  R_RegisterCCallable("fastmatrix", "FM_setzero",               (DL_FUNC) &FM_setzero);
  R_RegisterCCallable("fastmatrix", "FM_trace",                 (DL_FUNC) &FM_trace);
  R_RegisterCCallable("fastmatrix", "FM_tcrossprod",            (DL_FUNC) &FM_tcrossprod);

  /* operations on triangular matrices */
  R_RegisterCCallable("fastmatrix", "FM_cpy_lower",             (DL_FUNC) &FM_cpy_lower);
  R_RegisterCCallable("fastmatrix", "FM_cpy_upper",             (DL_FUNC) &FM_cpy_upper);
  R_RegisterCCallable("fastmatrix", "FM_cpy_lower2upper",       (DL_FUNC) &FM_cpy_lower2upper);
  R_RegisterCCallable("fastmatrix", "FM_cpy_upper2lower",       (DL_FUNC) &FM_cpy_upper2lower);
  R_RegisterCCallable("fastmatrix", "FM_sum_lower_tri",         (DL_FUNC) &FM_sum_lower_tri);
  R_RegisterCCallable("fastmatrix", "FM_sum_upper_tri",         (DL_FUNC) &FM_sum_upper_tri);

  /* matrix factorizations */
  R_RegisterCCallable("fastmatrix", "FM_chol_decomp",           (DL_FUNC) &FM_chol_decomp);
  R_RegisterCCallable("fastmatrix", "FM_QR_decomp",             (DL_FUNC) &FM_QR_decomp);
  R_RegisterCCallable("fastmatrix", "FM_QL_decomp",             (DL_FUNC) &FM_QL_decomp);
  R_RegisterCCallable("fastmatrix", "FM_LQ_decomp",             (DL_FUNC) &FM_LQ_decomp);
  R_RegisterCCallable("fastmatrix", "FM_svd_decomp",            (DL_FUNC) &FM_svd_decomp);

  /* QR, QL and LQ operations */
  R_RegisterCCallable("fastmatrix", "FM_QR_qy",                 (DL_FUNC) &FM_QR_qy);
  R_RegisterCCallable("fastmatrix", "FM_QR_qty",                (DL_FUNC) &FM_QR_qty);
  R_RegisterCCallable("fastmatrix", "FM_QR_fitted",             (DL_FUNC) &FM_QR_fitted);
  R_RegisterCCallable("fastmatrix", "FM_QR_store_R",            (DL_FUNC) &FM_QR_store_R);
  R_RegisterCCallable("fastmatrix", "FM_QL_qy",                 (DL_FUNC) &FM_QL_qy);
  R_RegisterCCallable("fastmatrix", "FM_QL_qty",                (DL_FUNC) &FM_QL_qty);
  R_RegisterCCallable("fastmatrix", "FM_LQ_yq",                 (DL_FUNC) &FM_LQ_yq);
  R_RegisterCCallable("fastmatrix", "FM_LQ_yqt",                (DL_FUNC) &FM_LQ_yqt);
  R_RegisterCCallable("fastmatrix", "FM_LQ_store_L",            (DL_FUNC) &FM_LQ_store_L);

  /* matrix inversion and linear solvers */
  R_RegisterCCallable("fastmatrix", "FM_backsolve",             (DL_FUNC) &FM_backsolve);
  R_RegisterCCallable("fastmatrix", "FM_forwardsolve",          (DL_FUNC) &FM_forwardsolve);
  R_RegisterCCallable("fastmatrix", "FM_chol_inverse",          (DL_FUNC) &FM_chol_inverse);
  R_RegisterCCallable("fastmatrix", "FM_invert_mat",            (DL_FUNC) &FM_invert_mat);
  R_RegisterCCallable("fastmatrix", "FM_invert_triangular",     (DL_FUNC) &FM_invert_triangular);

  /* least square procedures */
  R_RegisterCCallable("fastmatrix", "FM_gls_GQR",               (DL_FUNC) &FM_gls_GQR);
  R_RegisterCCallable("fastmatrix", "FM_lsfit",                 (DL_FUNC) &FM_lsfit);

  /* distances */
  R_RegisterCCallable("fastmatrix", "FM_pythag",                (DL_FUNC) &FM_pythag);
  R_RegisterCCallable("fastmatrix", "FM_mahalanobis",           (DL_FUNC) &FM_mahalanobis);
  R_RegisterCCallable("fastmatrix", "FM_WH_chisq",              (DL_FUNC) &FM_WH_chisq);
  R_RegisterCCallable("fastmatrix", "FM_WH_F",                  (DL_FUNC) &FM_WH_F);

  /* products */
  R_RegisterCCallable("fastmatrix", "FM_compensated_product",   (DL_FUNC) &FM_compensated_product);
  R_RegisterCCallable("fastmatrix", "FM_two_product_FMA",       (DL_FUNC) &FM_two_product_FMA);

  /* descriptive statistics code callable from other packages */
  R_RegisterCCallable("fastmatrix", "FM_center_and_Scatter",    (DL_FUNC) &FM_center_and_Scatter);
  R_RegisterCCallable("fastmatrix", "FM_cov_MSSD",              (DL_FUNC) &FM_cov_MSSD);
  R_RegisterCCallable("fastmatrix", "FM_find_quantile",         (DL_FUNC) &FM_find_quantile);
  R_RegisterCCallable("fastmatrix", "FM_geometric_mean",        (DL_FUNC) &FM_geometric_mean);
  R_RegisterCCallable("fastmatrix", "FM_mean_and_var",          (DL_FUNC) &FM_mean_and_var);
  R_RegisterCCallable("fastmatrix", "FM_moments",               (DL_FUNC) &FM_moments);
  R_RegisterCCallable("fastmatrix", "FM_online_center",         (DL_FUNC) &FM_online_center);
  R_RegisterCCallable("fastmatrix", "FM_online_covariance",     (DL_FUNC) &FM_online_covariance);
  R_RegisterCCallable("fastmatrix", "FM_skewness_and_kurtosis", (DL_FUNC) &FM_skewness_and_kurtosis);

  /* misc code callable from other packages */
  R_RegisterCCallable("fastmatrix", "FM_centering",             (DL_FUNC) &FM_centering);
  R_RegisterCCallable("fastmatrix", "FM_cov2cor",               (DL_FUNC) &FM_cov2cor);
  R_RegisterCCallable("fastmatrix", "FM_sherman_morrison",      (DL_FUNC) &FM_sherman_morrison);

  /* 'DEBUG' routine */
  R_RegisterCCallable("fastmatrix", "FM_print_mat",             (DL_FUNC) &FM_print_mat);
}
