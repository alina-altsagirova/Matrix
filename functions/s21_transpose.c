#include "s21_matrix.h"
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!is_matrix_ok(A) || !result) {
    return 1;
  }
  int state = s21_create_matrix(A->columns, A->rows, result);
  if (!state) {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[c][r] = A->matrix[r][c];
      }
    }
  }
  return state;
}