#include "math.h"
#include "s21_matrix.h"
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!is_matrix_ok(A) || !result) {
    return 1;
  }
  if (A->columns != A->rows) {
    return 2;
  }
  int state = s21_create_matrix(A->rows, A->columns, result);

  if (state == 0 && A->rows == 1) {
    result->matrix[0][0] = 1.0;
  } else if (state == 0) {
    for (int row = 0; row < A->rows && state == 0; row++) {
      for (int column = 0; column < A->columns && state == 0; column++) {
        matrix_t a = {0};
        double det = 0;
        state = s21_create_matrix(A->rows - 1, A->columns - 1, &a);
        if (state == 0) {
          fill_minor_matrix(A, &a, row, column);
          state = s21_determinant(&a, &det);
          int sign = ((row + column) % 2 == 0) ? 1 : -1;
          result->matrix[row][column] = det * sign;
          s21_remove_matrix(&a);
        }
      }
    }
  }
  return state;
}