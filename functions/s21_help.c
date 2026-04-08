#include <stdio.h>

#include "s21_matrix.h"

int is_matrix_ok(matrix_t *M) {
  return (M && M->matrix && M->columns > 0 && M->rows > 0);
}

void fill_matrix(matrix_t *M, double values[], size_t values_size) {
  int k = 0;
  for (int i = 0; i < M->rows; i++) {
    for (int j = 0; j < M->columns; j++) {
      if ((unsigned)k < values_size)
        M->matrix[i][j] = values[k++];
    }
  }
}

void fill_minor_matrix(matrix_t *A, matrix_t *mini_matrix, int cur_row,
                       int cur_column) {
  int mini_row = 0;
  for (int row = 0; row < A->rows; row++) {
    if (row != cur_row) {
      int mini_column = 0;
      for (int column = 0; column < A->columns; column++) {
        if (column != cur_column) {
          mini_matrix->matrix[mini_row][mini_column] = A->matrix[row][column];
          mini_column++;
        }
      }
      mini_row++;
    }
  }
}
int inverse_2(matrix_t * compl, double det, matrix_t *result) {
  matrix_t trans = {0};
  int state = s21_transpose(compl, &trans);
  if (state == 0)
    state = s21_mult_number(&trans, 1.0 / det, result);
  s21_remove_matrix(&trans);

  return state;
}

// void out_matrix(matrix_t* M) {
//   for (int i = 0; i < M->rows; i++) {
//     printf("\n");
//     for (int j = 0; j < M->columns; j++) {
//       printf(" %f,", M->matrix[i][j]);
//     }
//   }
//   printf("\n");
// }