#include "tests.h"

START_TEST(test_3) {
  matrix_t A, result, true_m = {0};
  double values1[] = {1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0, 1.0};
  double true_v[] = {0.0, 10.0, -20.0, 4.0, -14.0, 8.0, -8.0, -2.0, 4.0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &true_m);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));
  fill_matrix(&true_m, true_v, sizeof(values1) / sizeof(values1[0]));

  int state = s21_calc_complements(&A, &result);
  int eq_state = s21_eq_matrix(&true_m, &result);

  // out_matrix(&result);
  // out_matrix(&true_m);

  ck_assert_int_eq(state, 0);
  ck_assert_int_eq(eq_state, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_m);
}
END_TEST

START_TEST(test_2) {
  matrix_t A, result, true_m = {0};
  double values1[] = {1.0};
  double true_v[] = {1.0};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &true_m);

  fill_matrix(&A, values1, sizeof(values1) / sizeof(values1[0]));
  fill_matrix(&true_m, true_v, sizeof(values1) / sizeof(values1[0]));

  int state = s21_calc_complements(&A, &result);
  int eq_state = s21_eq_matrix(&true_m, &result);

  // out_matrix(&A);

  // out_matrix(&result);
  // out_matrix(&true_m);

  ck_assert_int_eq(state, 0);
  ck_assert_int_eq(eq_state, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_m);
}
END_TEST

START_TEST(test_null) {
  int state = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(state, 1);
}
END_TEST

START_TEST(test_unequal_size) {
  matrix_t A, result = {0};
  s21_create_matrix(1, 2, &result);
  s21_create_matrix(1, 2, &A);
  int state = s21_calc_complements(&A, &result);

  ck_assert_int_eq(state, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_calc_complements_s() {
  Suite *s = suite_create("calc_complements_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_3);
  tcase_add_test(t_case, test_2);
  tcase_add_test(t_case, test_null);
  tcase_add_test(t_case, test_unequal_size);

  suite_add_tcase(s, t_case);
  return s;
}