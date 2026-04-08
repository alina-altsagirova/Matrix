#include "tests.h"
START_TEST(test_basic) {
  matrix_t m = {0};
  int my_m = s21_create_matrix(69, 2, &m);
  ck_assert_int_eq(my_m, 0);
  ck_assert_int_eq(m.columns, 2);
  ck_assert_int_eq(m.rows, 69);
  ck_assert_ptr_nonnull(&m.matrix);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_invalid) {
  matrix_t m1 = {0};
  int res1 = s21_create_matrix(0, 2, &m1);
  ck_assert_int_eq(res1, 1);
  ck_assert_ptr_null(m1.matrix);

  matrix_t m2 = {0};
  int res2 = s21_create_matrix(2, 0, &m2);
  ck_assert_int_eq(res2, 1);
  ck_assert_ptr_null(m2.matrix);
}
END_TEST

START_TEST(test_null) {
  int my_m = s21_create_matrix(69, 2, NULL);
  ck_assert_int_eq(my_m, 1);
}
END_TEST

Suite *s21_create_matrix_s() {
  Suite *s = suite_create("create_matrix_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_invalid);
  tcase_add_test(t_case, test_null);

  suite_add_tcase(s, t_case);
  return s;
}