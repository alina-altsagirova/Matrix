#ifndef TESTS_H
#define TESTS_H
#include "check.h"
#include "s21_matrix.h"

Suite *s21_create_matrix_s(void);
Suite *s21_remove_matrix_s(void);
Suite *s21_eq_matrix_s(void);
Suite *s21_sum_matrix_s(void);
Suite *s21_sub_matrix_s(void);
Suite *s21_mult_number_s(void);
Suite *s21_mult_matrix_s(void);
Suite *s21_transpose_s(void);
Suite *s21_calc_complements_s(void);
Suite *s21_determinant_s(void);
Suite *s21_inverse_matrix_s(void);

#endif