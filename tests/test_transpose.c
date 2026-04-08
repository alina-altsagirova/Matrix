#include "tests.h"

START_TEST(test_basic) {
  matrix_t A, result, true_m = {0};
  double values1[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};
  double true_v[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &true_m);
  // s21_create_matrix(2,3, &result);
  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));
  fill_matrix(&true_m, true_v, sizeof(values1) / sizeof(values1[0]));

  int state = s21_transpose(&A, &result);
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

START_TEST(test_null) {
  int state = s21_transpose(NULL, NULL);
  ck_assert_int_eq(state, 1);
}

Suite *s21_transpose_s() {
  Suite *s = suite_create("transpose_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_null);

  suite_add_tcase(s, t_case);
  return s;
}