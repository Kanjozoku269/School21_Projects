#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdlib.h>

#define S21_M_PI 3.14159265358979323846
#define S21_E 2.71828182845904523536
#define S21_HUGE_V (__builtin_inff())
#define EPS 1E-6
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0
#define S21_MAXFLOAT 0x1.fffffep+127f

#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_pow(double base, double e);
long double s21_sqrt(double x);
long double s21_log(double x);
long double s21_cos(double x);
long double s21_sin(double x);
long double s21_tan(double x);
long double s21_exp(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_fmod(double x, double y);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_fact(double x);
long double intermediate_pow(double base, int exp);

int factorial(int x);

#endif  // SRC_S21_MATH_H_
