#include <check.h>

#include "../backend/backend.h"

#define EPS 1e-4

START_TEST(calc_test_1) {
  char src[100] = "4^acos(1.2/4)/tan(2*1.2)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = -6.31492;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-1 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_2) {
  char src[100] = "2+2";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 4;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-2 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_3) {
  char src[100] = "123+0.456";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 123.456;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-3 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_4) {
  char src[100] = "log(-2)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = NAN;
  ck_assert_msg(isnan(res) && isnan(real_result), "test-4 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_5) {
  char src[100] = "-(-1)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 1;
  ck_assert_msg(res == real_result, "test-5 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_6) {
  char src[100] = "cos(10 % 2.2)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 0.362358;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-6 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_7) {
  char src[100] = "sqrt(ln(10))";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 1.517427;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-7 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_8) {
  char src[100] = "atan(10)+sin(10)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 0.92710;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-8 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_9) {
  char src[100] = "asin(1)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 1.570796;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-9 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_10) {
  char src[100] = "10-20*(-10)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 210;
  ck_assert_msg(fabs(res - real_result) <= EPS, "test-10 failed");
  ck_assert_int_eq(result, SUCCESS);
}
END_TEST

START_TEST(calc_test_11) {
  char src[100] = "-(o(i(a(10.01)*n(2))/10m2))^q(5)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  ck_assert_double_eq(res, 0.0);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(calc_test_12) {
  char src[100] = ")(s(2)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  ck_assert_double_eq(res, 0.0);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(calc_test_13) {
  char src[100] = ".+m)";
  double res = 0.0;
  int result = smartCalc(src, &res);
  ck_assert_double_eq(res, 0.0);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(calc_test_14) {
  char src[100] = "2 ^ 3 ^ 2";
  double res = 0.0;
  int result = smartCalc(src, &res);
  double real_result = 512.0;
  ck_assert_double_eq(res, real_result);
  ck_assert_int_eq(result, SUCCESS);
}

START_TEST(calc_test_15) {
  char src[100] = "4^acos(x/4)/tan(2*x)";

  double x_numbers[3] = {-1.0, 0.0, 1.0};
  double y_numbers[3] = {0.0, 0.0, 0.0};

  int result = graphic(src, x_numbers, y_numbers, 3);

  ck_assert_int_eq(result, SUCCESS);
  ck_assert(fabs(y_numbers[0] - 5.73301) <= EPS);
  ck_assert(isinf(y_numbers[1]));
  ck_assert(fabs(y_numbers[2] - -2.84528) <= EPS);
}

// ########################################################

START_TEST(s21_test_0) {
  double res = 0;
  double orig = 10;

  char str[255] = "5 + 5";
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq(res, orig);
}
END_TEST

START_TEST(s21_test_1) {
  double res = 0;
  double orig = 162;

  char str[255] = "   4 * 5 * 2 * 2 * 2 + 2";
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq(res, orig);
}
END_TEST

START_TEST(s21_test_2) {
  double res = 0;
  double orig = 20;
  // int error = 0;

  char str[255] = "  150 / 10 + 5 * 2 / 2";
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq(res, orig);
}
END_TEST

START_TEST(s21_test_3) {
  double res = 0;
  double orig = 9;
  // int error = 0;

  char str[255] = "  5 + 5 - 2 * 3 / 6";
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq(res, orig);
}
END_TEST

START_TEST(s21_test_4) {
  double res = 0;
  double orig = 69;
  // int error = 0;

  char str[255] = "2+(5 * 5 * 5 + 5 + 2 * 2) / (2)";

  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq(res, orig);
}
END_TEST

START_TEST(s21_test_5) {
  double res = 0.0;
  char *str = "24*4 -3 * 2";
  double orig = 90;
  int result = smartCalc(str, &res);

  ck_assert_int_eq(result, SUCCESS);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_test_6) {
  double orig = 4;
  char *str = "2 - (-2)";
  double res = 0.0;
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_int_eq(res, orig);
}
END_TEST

START_TEST(s21_test_7) {
  double orig = -0.41211848524;
  char *str = "-sin(9)";
  double res = 0.0;
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_int_eq(res, orig);
}
END_TEST
START_TEST(s21_test_8) {
  double orig = 2.41211848524;
  char *str = "sin(9)-(-2)";
  double res = 0.0;
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_int_eq(res, orig);
}
END_TEST
START_TEST(s21_test_9) {
  double orig = 0.91113026188;
  char *str = "-cos(9)";
  double res = 0.0;
  int result = smartCalc(str, &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_int_eq(res, orig);
}
END_TEST
START_TEST(plus_t) {
  double res = 0.0;
  int result = smartCalc("(-2)+2", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_float_eq(res, 0);
}
END_TEST

START_TEST(minus_t) {
  double res = 0.0;
  int result = smartCalc("(-2.2)-2.2", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_float_eq(res, -4.4);
}
END_TEST

START_TEST(mult_t) {
  double res = 0.0;
  int result = smartCalc("(-2.2)*(+2.2)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_float_eq(res, -4.84);
}
END_TEST

START_TEST(division_t) {
  double res = 0.0;
  int result = smartCalc("(-2.2)/2.2", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_float_eq(res, -1);
}
END_TEST

START_TEST(degr_t) {
  double res = 0.0;
  int result = smartCalc("(2.2)^(-2.2)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq_tol(res, 0.17647, 0.17647);
}
END_TEST

START_TEST(cos_t) {
  double res = 0.0;
  int result = smartCalc("cos(2)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_double_eq_tol(res, cos(2), 1e-7);
}
END_TEST

START_TEST(tan_t) {
  double res = 0.0;
  int result = smartCalc("tan(2)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, tan(2));
}
END_TEST

START_TEST(asin_t) {
  double res = 0.0;
  int result = smartCalc("asin(1)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, asin(1));
}
END_TEST

START_TEST(acos_t) {
  double res = 0.0;
  int result = smartCalc("acos(1)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, acos(1));
}
END_TEST

START_TEST(atan_t) {
  double res = 0.0;
  int result = smartCalc("atan(1)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, atan(1));
}
END_TEST

START_TEST(ln_t) {
  double res = 0.0;
  int result = smartCalc("log(1)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, log(1));
}
END_TEST

START_TEST(log_t) {
  double res = 0.0;
  int result = smartCalc("log(1)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, log10(1));
}
END_TEST

START_TEST(sqrt_t) {
  double res = 0.0;
  int result = smartCalc("sqrt(1)", &res);
  ck_assert_int_eq(result, SUCCESS);
  ck_assert_ldouble_eq(res, sqrt(1));
}
END_TEST

Suite *SmartCalc(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("SmartCalc Tests (38)");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, calc_test_1);
  tcase_add_test(tc_core, calc_test_2);
  tcase_add_test(tc_core, calc_test_3);
  tcase_add_test(tc_core, calc_test_4);
  tcase_add_test(tc_core, calc_test_5);
  tcase_add_test(tc_core, calc_test_6);
  tcase_add_test(tc_core, calc_test_7);
  tcase_add_test(tc_core, calc_test_8);
  tcase_add_test(tc_core, calc_test_9);
  tcase_add_test(tc_core, calc_test_10);
  tcase_add_test(tc_core, calc_test_11);
  tcase_add_test(tc_core, calc_test_12);
  tcase_add_test(tc_core, calc_test_13);
  tcase_add_test(tc_core, calc_test_14);
  tcase_add_test(tc_core, calc_test_15);

  /*
  ARMENIAN TEST
  */

  tcase_add_test(tc_core, s21_test_0);
  tcase_add_test(tc_core, s21_test_1);
  tcase_add_test(tc_core, s21_test_2);
  tcase_add_test(tc_core, s21_test_3);
  tcase_add_test(tc_core, s21_test_4);
  tcase_add_test(tc_core, s21_test_5);
  tcase_add_test(tc_core, s21_test_6);
  tcase_add_test(tc_core, s21_test_7);
  tcase_add_test(tc_core, s21_test_8);
  tcase_add_test(tc_core, s21_test_9);

  tcase_add_test(tc_core, plus_t);
  tcase_add_test(tc_core, minus_t);
  tcase_add_test(tc_core, division_t);
  tcase_add_test(tc_core, mult_t);
  tcase_add_test(tc_core, degr_t);
  tcase_add_test(tc_core, cos_t);
  tcase_add_test(tc_core, tan_t);
  tcase_add_test(tc_core, asin_t);
  tcase_add_test(tc_core, acos_t);
  tcase_add_test(tc_core, atan_t);
  tcase_add_test(tc_core, ln_t);
  tcase_add_test(tc_core, log_t);
  tcase_add_test(tc_core, sqrt_t);

  suite_add_tcase(s, tc_core);

  return s;
}

void run_testcase(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);

  putchar('\n');

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main() {
  run_testcase(SmartCalc());

  return 0;
}
