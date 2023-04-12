#include "s21_math.h"

long double s21_tan(double x) {
  long double res = 0;
  res = (s21_sin(x) / s21_cos(x));

  return res;
}
