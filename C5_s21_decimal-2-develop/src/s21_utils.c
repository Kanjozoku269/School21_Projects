#include "s21_decimal.h"

int getsign(const s21_decimal *src, int i) {
  uint32_t mask = 1u << (i % BIT_LEN);
  return !!(src->bits[i / BIT_LEN] & mask);
}

void setsign(s21_decimal *src, int i, int sign) {
  if (sign) {
    src->bits[i / BIT_LEN] |= 1u << i % BIT_LEN;
  } else {
    src->bits[i / BIT_LEN] &= ~(1u << i % BIT_LEN);
  }
}

s21_decimal_data *get_info(s21_decimal *src) {
  return (s21_decimal_data *)(src->bits + INFO);
}

uint32_t ftou(float num) { return *(uint32_t *)&num; }

int first_sign(s21_decimal *src) {
  int index = -1;
  for (int i = 0; i < MAX_LEN; ++i) {
    if (getsign(src, i)) index = i;
  }
  return index;
}

int last_sign(s21_decimal *src) {
  int index = -1;
  for (int i = MAX_LEN - 1; i >= 0 && index == -1; --i) {
    if (getsign(src, i)) index = i;
  }
  return index;
}

bool is_zero(s21_decimal *src) {
  return src->bits[LOW] == 0 && src->bits[MID] == 0 && src->bits[HIGH] == 0;
}

bool is_max(s21_decimal *src) {
  return src->bits[LOW] == UINT32_MAX && src->bits[MID] == UINT32_MAX &&
         src->bits[HIGH] == UINT32_MAX;
}

bool can_10_shift(const s21_decimal *src) {
  return !(getsign(src, MAX_LEN - 1) || getsign(src, MAX_LEN - 2) ||
           getsign(src, MAX_LEN - 3) || getsign(src, MAX_LEN - 4));
}

void s21_shift_right(s21_decimal *src, int shift) {
  for (int i = shift; i < MAX_LEN; ++i) {
    setsign(src, i - shift, getsign(src, i));
  }
}

int s21_shift_left(s21_decimal *src, int shift) {
  int error = RES_OK;
  int sign_index = last_sign(src);

  if (sign_index != -1 && sign_index > MAX_LEN - shift - 1) {
    error = RES_OVER;
  }

  if (!error) {
    for (int i = MAX_LEN - shift - 1; i >= 0; --i) {
      setsign(src, i + shift, getsign(src, i));
    }
    for (int i = 0; i < shift; ++i) {
      setsign(src, i, 0);
    }
  }

  return error;
}

int s21_shift_10_left(s21_decimal *src, int shift) {
  int error = RES_OK;
  for (int i = 0; i < shift && !error; ++i) {
    s21_decimal a = *src;
    s21_decimal b = *src;

    error = s21_shift_left(&a, 3);
    if (error) continue;
    s21_shift_left(&b, 1);

    error = s21_sum(&a, &b, src);
  }
  if (error) error = RES_OVER;
  return error;
}

s21_decimal s21_shift_10_right(s21_decimal *src, int shift) {
  s21_decimal ten = {.bits = {10, 0, 0, 0}};

  s21_decimal mod = ZERO_DECIMAL;

  for (int i = 0; i < shift; ++i) {
    mod = s21_div_int(*src, ten, src);
  }

  return mod;
}

void s21_reverse(s21_decimal *src) {
  for (int i = 0; i < RANK_COUNT; ++i) {
    src->bits[i] = ~(src->bits[i]);
  }
}