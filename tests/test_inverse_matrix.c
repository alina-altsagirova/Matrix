#include "tests.h"

START_TEST(test_basic) {
  matrix_t A, result, true_m = {0};
  double values1[] = {2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0, -3.0};
  double true_v[] = {1.0, -1.0, 1.0, -38.0, 41.0, -34.0, 27.0, -29.0, 24.0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &true_m);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));
  fill_matrix(&true_m, true_v, sizeof(values1) / sizeof(values1[0]));

  int state = s21_inverse_matrix(&A, &result);
  int eq_state = s21_eq_matrix(&true_m, &result);
  // out_matrix(&A);
  // out_matrix(&B);
  // ut_matrix(&result);
  // out_matrix(&true_m);

  ck_assert_int_eq(state, 0);
  ck_assert_int_eq(eq_state, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_m);
}
END_TEST

START_TEST(test_zero_det) {
  matrix_t A, result = {0};
  double values1[] = {2.0, 5.0, 7.0, 0.0, 0.0, 0.0, 5.0, -2.0, -3.0};

  s21_create_matrix(3, 3, &A);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));

  int state = s21_inverse_matrix(&A, &result);
  // out_matrix(&A);
  // out_matrix(&B);
  // ut_matrix(&result);
  // out_matrix(&true_m);

  ck_assert_int_eq(state, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_null) {
  int state = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(state, 1);
}
START_TEST(test_unequal) {
  matrix_t A, result = {0};
  s21_create_matrix(2, 3, &A);
  int state = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(state, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

Suite *s21_inverse_matrix_s() {
  Suite *s = suite_create("inverse_matrix_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_null);
  tcase_add_test(t_case, test_unequal);
  tcase_add_test(t_case, test_zero_det);

  suite_add_tcase(s, t_case);
  return s;
}