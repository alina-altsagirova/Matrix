#include "math.h"
#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!is_matrix_ok(A) || !result) {
    return 1;
  }
  if (A->columns != A->rows) {
    return 2;
  }
  int state = 0;
  double det = 0.0;
  state = s21_determinant(A, &det);

  if (state == 0 && fabs(det) < EPS) {
    state = 2;
  } else if (state == 0) {
    matrix_t compl = {0};
    state = s21_calc_complements(A, &compl );
    if (state == 0)
      state = inverse_2(&compl, det, result);
    if (state != 0)
      s21_remove_matrix(result);
    s21_remove_matrix(&compl );
  }
  return state;
}
