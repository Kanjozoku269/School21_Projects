#include "s21_math.h"

long double s21_log(double x) {
  long double temp = (long double)x;
  long double result = 0;
  if (temp < 0) {
    result = S21_NAN;
  } else if (temp == 0) {
    result = S21_HUGE_V;
  } else {
    long double termin = (temp - 1) / (temp + 1);
    long double squared = termin * termin;
    long double next_termin = termin;
    int k = 1;
    while (s21_fabs(next_termin) > 1e-15) {
      result += next_termin / k;
      k += 2;
      next_termin *= squared;
    }
  }

  return result * 2;
}