#include "tests.h"

START_TEST(test_basic) {
  matrix_t A, B, result, true_m = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &true_m);

  double values1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double values2[] = {0.0, 0.5, 0.0, 1.0, 1.0, 0.0, 2.0, 0.5, 0.0};
  double true_v[] = {8.0, 4.0, 0.0, 17.0, 10.0, 0.0, 26.0, 16.0, 0.0};

  size_t s = sizeof(values1) / sizeof(values1[0]);
  fill_matrix(&A, values1, s);
  fill_matrix(&B, values2, s);
  fill_matrix(&true_m, true_v, s);

  int state = s21_mult_matrix(&A, &B, &result);
  int eq_state = s21_eq_matrix(&result, &true_m);

  ck_assert_int_eq(state, 0);
  ck_assert_int_eq(eq_state, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_m);
}
END_TEST

START_TEST(test_null) {
  int state = s21_mult_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(state, 1);
}
START_TEST(test_unequal_size) {
  matrix_t A, B, result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &result);
  int state = s21_mult_matrix(&A, &B, &result);
  ck_assert_int_eq(state, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_mult_matrix_s() {
  Suite *s = suite_create("mult_matrix_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_null);
  tcase_add_test(t_case, test_unequal_size);

  suite_add_tcase(s, t_case);
  return s;
}