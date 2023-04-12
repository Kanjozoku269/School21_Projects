#include "s21_math.h"

long double s21_exp(double x) {
  long double temp = (long double)x;
  long double result = 1;
  long double termin = 1;
  int i = 1;
  if (temp < -14) {
    result = 1;
  } else if (temp == S21_HUGE_V || temp == S21_MAXFLOAT) {
    result = S21_HUGE_V;
  } else {
    while (termin > 1e-7 || termin < -1e-7) {
      result += termin;
      termin *= temp / i;
      i++;
    }
    if (temp != temp) {
      result = S21_NAN;
    }
  }

  return result - 1;
}
