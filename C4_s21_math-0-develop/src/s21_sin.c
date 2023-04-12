#include "s21_math.h"

long double s21_sin(double x) {
  int n = 1;
  int negative = 1;
  int j = 0;
  if (x < 0) {
    while (x < S21_M_PI && x != -S21_INF) {
      x = x + S21_M_PI;
      j++;
    }
  } else {
    while (x > S21_M_PI && x != S21_INF) {
      x = x - S21_M_PI;
      j++;
    }
  }
  if (j % 2 != 0) {
    negative = -1;
  }
  long double res = x;
  long double var = x;
  if (x == S21_INF || x == -S21_INF) {
    res = S21_NAN;
  } else {
    while (s21_fabs(var) > 1e-17) {
      var = (-var) * (x * x) / ((2 * n + 1) * (2 * n));
      res += var;
      n++;
    }
  }

  return res * negative;
}
