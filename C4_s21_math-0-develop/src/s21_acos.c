#include "s21_math.h"

long double s21_acos(double x) {
  long double s = 0;
  if (x > 0 && x < 1) {
    s = s21_asin(s21_sqrt(1 - x * x));
  } else if (x > 1 || x != x) {
    s = S21_NAN;
  } else if (x > -1 && x < 0) {
    s = S21_M_PI - s21_asin(s21_sqrt(1 - x * x));
  } else if (x == 0) {
    s = S21_M_PI / 2;
  } else if (x == -1) {
    s = S21_M_PI;
  }

  return s;
}
