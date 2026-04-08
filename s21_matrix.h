#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <stdlib.h>

#define EPS 1e-6
#define SUCCESS 1
#define FAILTURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int is_matrix_ok(matrix_t *M);

void fill_minor_matrix(matrix_t *A, matrix_t *mini_matrix, int cur_row,
                       int cur_column);
void fill_matrix(matrix_t *M, double values[], size_t values_size);
int inverse_2(matrix_t * compl, double det, matrix_t *result);
// void out_matrix(matrix_t* M);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif