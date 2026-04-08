#include "tests.h"

int main(void) {
  int failed = 0;
  Suite *s21_matrix_suite[] = {
      s21_create_matrix_s(), s21_remove_matrix_s(),  s21_eq_matrix_s(),
      s21_sum_matrix_s(),    s21_sub_matrix_s(),     s21_mult_number_s(),
      s21_mult_matrix_s(),   s21_transpose_s(),      s21_calc_complements_s(),
      s21_determinant_s(),   s21_inverse_matrix_s(), NULL};

  for (int i = 0; s21_matrix_suite[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_matrix_suite[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  return (failed == 0) ? 0 : 1;
}
