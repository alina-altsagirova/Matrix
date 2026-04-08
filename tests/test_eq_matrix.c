#include "tests.h"

START_TEST(test_equal) {
  matrix_t first, secnd = {0};
  double values[] = {1.0, 2.0, 3.0, 4.0};
  s21_create_matrix(2, 2, &first);
  s21_create_matrix(2, 2, &secnd);

  fill_matrix(&first, values, sizeof(values) / sizeof(values[0]));
  fill_matrix(&secnd, values, sizeof(values) / sizeof(values[0]));

  // out_matrix(&first); //!!!!!!!!!
  // out_matrix(&secnd);

  int state = s21_eq_matrix(&first, &secnd);
  ck_assert_int_eq(state, SUCCESS); // success

  s21_remove_matrix(&first);
  s21_remove_matrix(&secnd);
}
END_TEST

START_TEST(test_unequal_size) {
  matrix_t first, second = {0};
  s21_create_matrix(4, 2, &first);
  s21_create_matrix(1, 2, &second);

  int state = s21_eq_matrix(&first, &second);
  ck_assert_int_eq(state, FAILTURE); // failture

  s21_remove_matrix(&first);
  s21_remove_matrix(&second);
}
END_TEST

START_TEST(test_unequal_data) {
  matrix_t first, second = {0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  s21_create_matrix(4, 2, &first);
  s21_create_matrix(4, 2, &second);
  fill_matrix(&first, values, sizeof(values) / sizeof(values[0]));
  fill_matrix(&second, values, sizeof(values) / sizeof(values[0]));
  second.matrix[3][1] = 66.0;

  // out_matrix(&first);//!!!!!!!!!!!!!!
  // out_matrix(&second);

  int state = s21_eq_matrix(&first, &second);
  ck_assert_int_eq(state, FAILTURE); // failture

  s21_remove_matrix(&first);
  s21_remove_matrix(&second);
}
END_TEST

START_TEST(test_unequal_data_small) {
  matrix_t first, second = {0};
  double values[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  s21_create_matrix(4, 2, &first);
  s21_create_matrix(4, 2, &second);
  fill_matrix(&first, values, sizeof(values) / sizeof(values[0]));
  fill_matrix(&second, values, sizeof(values) / sizeof(values[0]));
  second.matrix[3][1] += 0.000002;

  // out_matrix(&first);//!!!!!!!!!!!!!!!!!!
  // out_matrix(&second);

  int state = s21_eq_matrix(&first, &second);
  ck_assert_int_eq(state, FAILTURE); // failture

  s21_remove_matrix(&first);
  s21_remove_matrix(&second);
}
END_TEST

START_TEST(test_null) {
  int state = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(state, FAILTURE);
}

Suite *s21_eq_matrix_s() {
  Suite *s = suite_create("eq_matrix_s");
  TCase *t_case = tcase_create("core");

  tcase_add_test(t_case, test_equal);
  tcase_add_test(t_case, test_null);
  tcase_add_test(t_case, test_unequal_size);
  tcase_add_test(t_case, test_unequal_data);
  tcase_add_test(t_case, test_unequal_data_small);

  suite_add_tcase(s, t_case);
  return s;
}