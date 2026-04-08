#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!is_matrix_ok(A) || !is_matrix_ok(B) || !result) {
    return 1;
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    return 2;
  }
  if (!s21_create_matrix(A->rows, A->columns, result)) {
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[r][c] = A->matrix[r][c] - B->matrix[r][c];
      }
    }
  }
  return 0;
}