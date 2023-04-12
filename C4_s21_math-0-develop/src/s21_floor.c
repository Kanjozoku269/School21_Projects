#include "s21_math.h"

long double s21_floor(double x) {
  long double floor = x;
  if (x > 0) floor = (int)x;
  if (x < 0 && (int)x > x) floor = (int)x - 1;
  if (x < 0 && x == -S21_INF) floor = -S21_INF;
  if (x > 0 && x == S21_INF) floor = S21_INF;
  if (x > 0 && x == S21_MAXFLOAT) floor = S21_MAXFLOAT;
  if (x < 0 && x == -S21_MAXFLOAT) floor = S21_MAXFLOAT;

  return floor;
}