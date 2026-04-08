#include "tests.h"
START_TEST(test_basic) {
  matrix_t m = {0};
  s21_create_matrix(69, 2, &m);

  s21_remove_matrix(&m);

  ck_assert_int_eq(m.columns, 0);
  ck_assert_int_eq(m.rows, 0);
  ck_assert_ptr_null(m.matrix);
}
END_TEST

START_TEST(test_zero_matrix) {
  matrix_t m = {0};
  m.columns = 0;
  m.matrix = NULL;
  m.rows = 0;

  s21_remove_matrix(&m);
  ck_assert_ptr_null(m.matrix);
}
END_TEST

Suite *s21_remove_matrix_s() {
  Suite *s = suite_create("remove_matrix_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_basic);
  tcase_add_test(t_case, test_zero_matrix);

  suite_add_tcase(s, t_case);
  return s;
}