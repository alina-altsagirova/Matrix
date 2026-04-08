#include "s21_matrix.h"
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!is_matrix_ok(A) || !result) {
    return 1;
  }
  int error = 0;
  if (!s21_create_matrix(A->rows, A->columns, result)) {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[r][c] = number * A->matrix[r][c];
      }
    }
  } else {
    error = 1;
  }
  return error;
}