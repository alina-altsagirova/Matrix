#include "s21_matrix.h"
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!is_matrix_ok(A) || !is_matrix_ok(B) || !result) {
    return 1;
  }
  if (A->columns != B->rows) {
    return 2;
  }
  int error = s21_create_matrix(A->rows, B->columns, result);
  for (int r = 0; r < result->rows && error == 0; r++) {
    for (int c = 0; c < result->columns; c++) {
      for (int i = 0; i < A->columns; i++) {
        result->matrix[r][c] += A->matrix[r][i] * B->matrix[i][c];
      }
    }
  }
  return error;
}