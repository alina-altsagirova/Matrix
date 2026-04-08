#include "math.h"
#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (!is_matrix_ok(A) || !is_matrix_ok(B)) {
    return FAILTURE;
  }
  int state = SUCCESS;
  int loop = 1;

  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows && loop; i++) {
      for (int j = 0; j < A->columns && loop; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          loop = 0;
          state = FAILTURE;
        }
      }
    }
  } else {
    state = FAILTURE;
  }
  return state;
}