#include <math.h>

#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (!is_matrix_ok(A) || !result) {
    return 1;
  }
  if (A->rows != A->columns) {
    return 2;
  }
  int state = 0;
  int n = A->rows;
  matrix_t temp = {0};

  state = s21_create_matrix(n, n, &temp);
  if (!state) {
    for (int r = 0; r < n; r++) {
      for (int c = 0; c < n; c++) {
        temp.matrix[r][c] = A->matrix[r][c];
      }
    }
    int swap_count = 0;
    for (int i = 0; i < n; i++) {
      if (fabs(temp.matrix[i][i]) < EPS) {
        int swap_row = -1;
        int loop = 0;
        for (int k = i + 1; k < n && !loop; k++) {
          if (fabs(temp.matrix[k][i]) > EPS)
            swap_row = k;
          if (fabs(temp.matrix[k][i]) > EPS)
            loop = 1;
        }
        if (swap_row == -1) {
          s21_remove_matrix(&temp);
          *result = 0.0;
          return 0;
        }
        double *temp_ptr = temp.matrix[i];
        temp.matrix[i] = temp.matrix[swap_row];
        temp.matrix[swap_row] = temp_ptr;
        swap_count++;
      }
      for (int j = i + 1; j < n; j++) {
        double factor = temp.matrix[j][i] / temp.matrix[i][i];
        for (int k = i; k < n; k++) {
          temp.matrix[j][k] -= factor * temp.matrix[i][k];
        }
      }
    }
    double det = 1.0;
    for (int i = 0; i < n; i++) {
      det *= temp.matrix[i][i];
    }
    if (swap_count % 2 != 0) {
      det = -det;
    }
    *result = det;
    s21_remove_matrix(&temp);
  }
  return state;
}