#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (!result || rows <= 0 || columns <= 0) {
    return 1;
  }

  if (!(result->matrix = calloc(rows, sizeof(double *)))) {
    error = 1;
  } else {
    for (int i = 0; i < rows && !error; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        s21_remove_matrix(result);
        error = 1;
      }
    }
  }
  if (!error) {
    result->columns = columns;
    result->rows = rows;
  }

  return error;
}