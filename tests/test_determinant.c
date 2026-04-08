#include "tests.h"

START_TEST(test_3) {
  matrix_t A = {0};
  double result = 0.0;
  double true_v = -40.0;
  double values1[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};

  s21_create_matrix(3, 3, &A);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));

  int state = s21_determinant(&A, &result);

  // out_matrix(&A);

  ck_assert_int_eq(state, 0);
  ck_assert_double_eq(true_v, result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_2) {
  matrix_t A = {0};
  double result = 0.0;
  double true_v = -6.0;
  double values1[] = {
      1.0,
      2.0,
      3.0,
      0.0,
  };

  s21_create_matrix(2, 2, &A);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));

  int state = s21_determinant(&A, &result);

  // out_matrix(&A);

  ck_assert_int_eq(state, 0);
  ck_assert_double_eq(true_v, result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_1) {
  matrix_t A = {0};
  double result = 0.0;
  double true_v = 1.0;
  double values1[] = {1.0};

  s21_create_matrix(1, 1, &A);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));

  int state = s21_determinant(&A, &result);

  // out_matrix(&A);

  ck_assert_int_eq(state, 0);
  ck_assert_double_eq(true_v, result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_null) {
  int state = s21_determinant(NULL, NULL);
  ck_assert_int_eq(state, 1);
}
END_TEST

START_TEST(test_unequal_size) {
  matrix_t A = {0};
  s21_create_matrix(2, 3, &A);
  double result = 0.0;
  int state = s21_determinant(&A, &result);
  ck_assert_int_eq(state, 2);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_s() {
  Suite *s = suite_create("determinant_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_3);
  tcase_add_test(t_case, test_2);
  tcase_add_test(t_case, test_1);
  tcase_add_test(t_case, test_null);
  tcase_add_test(t_case, test_unequal_size);

  suite_add_tcase(s, t_case);
  return s;
}