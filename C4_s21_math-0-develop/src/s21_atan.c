#include "s21_math.h"

long double s21_atan(double x) {
  long double temp = (long double)x;
  long double s = 0;
  if (temp < 1 && temp > -1) {
    for (int n = 1; n < 1000; n++) {
      s += (s21_pow(-1, n - 1) * s21_pow(temp, 2 * n - 1)) / (2 * n - 1);
    }
  } else if (temp == S21_INF) {
    s = S21_M_PI / 2;
  } else if (temp == -S21_INF) {
    s = -S21_M_PI / 2;
  } else if (temp > 1 || temp < -1) {
    for (int n = 0; n < 1000; n++) {
      s += s21_pow(-1, n) * s21_pow(temp, -1 - (2 * n)) / (1 + (2 * n));
    }
    s = S21_M_PI * s21_sqrt(temp * temp) / (2 * temp) - s;
  } else if (temp == 1) {
    s = S21_M_PI / 4;
  } else if (temp == -1) {
    s = (-1) * S21_M_PI / 4;
  } else if (temp != temp) {
    s = S21_NAN;
  }

  return s;
}