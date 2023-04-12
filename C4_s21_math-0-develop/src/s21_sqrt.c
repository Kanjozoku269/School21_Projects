#include "s21_math.h"

long double s21_sqrt(double x) {
  int i = 0;
  double res = 0;
  if (x < 0) {
    res = S21_NAN;
  } else if (x == 0) {
    res = 0;
  } else {
    res = x;
    for (i = 0; i < 1000000; i++) {
      res = (res + x / res) / 2;
    }
  }

  return res;
}
