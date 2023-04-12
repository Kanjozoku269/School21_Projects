#include "s21_math.h"

long double s21_ceil(double x) {
  double ceil = S21_NAN;

  if (x > 0 && x > (int)x) ceil = (int)x + 1;
  if (x < 0 || x < (int)x) ceil = (int)x;
  if (x == (int)x) ceil = x;
  if (x > 0 && x == S21_HUGE_V) ceil = S21_INF;
  if (x < 0 && x == -S21_HUGE_V) ceil = -S21_INF;
  if (x > 0 && x == S21_MAXFLOAT) ceil = S21_MAXFLOAT;
  if (x < 0 && x == -S21_MAXFLOAT) ceil = -S21_MAXFLOAT;

  return ceil;
}