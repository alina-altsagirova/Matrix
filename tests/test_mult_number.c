#include "tests.h"

START_TEST(test_basic) {
  matrix_t A, result, true_m = {0};

  s21_create_matrix(3, 3, &A);
  double number = 2.5;
  s21_create_matrix(3, 3, &true_m);

  double values1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  double true_v[] = {2.5, 5.0, 7.5, 10.0, 12.5, 15.0, 17.5, 20.0, 22.5};

  size_t s = sizeof(values1) / sizeof(values1[0]);
  fill_matrix(&A, values1, s);
  fill_matrix(&true_m, true_v, s);

  // out_matrix(&A);
  // out_matrix(&true_m);

  int state = s21_mult_number(&A, number, &result);
  // out_matrix(&result);
  int eq_state = s21_eq_matrix(&result, &true_m);

  ck_assert_int_eq(state, 0);
  ck_assert_int_eq(eq_state, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_m);
}
END_TEST

START_TEST(test_null) {
  int state = s21_mult_number(NULL, 0.0, NULL);
  ck_assert_int_eq(state, 1);
}

Suite *s21_mult_number_s() {
  Suite *s = suite_create("mult_number_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_null);

  suite_add_tcase(s, t_case);
  return s;
}