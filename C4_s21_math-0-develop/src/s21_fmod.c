#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double n = 0;

  int v = 0;
  v = x / y;
  n = x - y * v;
  if (y == 0) n = S21_NAN;
  if (x == S21_INF) n = S21_NAN;
  if (y == S21_INF) n = 0;
  if (x != 0 && y == S21_HUGE_V) n = S21_NAN;

  return n;
}