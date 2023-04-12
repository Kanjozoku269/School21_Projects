#include "s21_math.h"

int s21_abs(int i) {
  if (i < 0) {
    i = i * (-1);
  }

  return i;
}
