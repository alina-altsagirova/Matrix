#include "tests.h"

START_TEST(test_basic) {
  matrix_t A, B, result, true_m = {0};
  double values1[] = {1.0, -2.0, 3.3, 44.9099, 1.123, 2.123456};
  double values2[] = {10.0, -20.0, 3.3, 44.9099, 1.12, 2.1234567};
  double true_v[] = {11.0, -22.0, 6.6, 89.8198, 2.243, 4.246913};

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(2, 3, &true_m);
  // s21_create_matrix(2,3, &result);
  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));
  fill_matrix(&B, values2, sizeof(values1) / sizeof(values1[0]));
  fill_matrix(&true_m, true_v, sizeof(values1) / sizeof(values1[0]));

  int state = s21_sum_matrix(&A, &B, &result);
  int eq_state = s21_eq_matrix(&true_m, &result);
  // out_matrix(&A);
  // out_matrix(&B);
  // out_matrix(&result);
  // out_matrix(&true_m);

  ck_assert_int_eq(state, 0);
  ck_assert_int_eq(eq_state, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_m);
}
END_TEST

START_TEST(test_null) {
  int state = s21_sum_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(state, 1);
}
END_TEST

START_TEST(test_unequal_size) {
  matrix_t A, B, result = {0};
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(1, 8, &B);
  int state = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(state, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}

Suite *s21_sum_matrix_s() {
  Suite *s = suite_create("sum_matrix_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_unequal_size);
  tcase_add_test(t_case, test_null);

  suite_add_tcase(s, t_case);
  return s;
}