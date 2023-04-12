#include "s21_math.h"

long double s21_asin(double x) {
  long double temp = (long double)x;
  long double s = 0;
  if (temp != temp) {
    s = S21_NAN;
  } else if (temp == -S21_HUGE_V) {
    s = S21_NAN;
  } else if (temp == S21_HUGE_V) {
    s = S21_NAN;
  } else if (temp < 1 && temp > -1) {
    s = s21_atan(temp / (s21_sqrt(1 - temp * temp)));
  } else if (temp == 1) {
    s = S21_M_PI / 2;
  } else if (temp == -1) {
    s = (-1) * S21_M_PI / 2;
  } else if (temp > 1 || temp < -1) {
    s = S21_NAN;
  }

  return s;
}
