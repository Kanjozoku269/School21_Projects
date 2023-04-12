#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = result == NULL;

  if (!error) {
    s21_decimal_data *info = get_info(&value);
    s21_shift_10_right(&value, info->expo);
    info->expo = 0;
    *result = value;
  }

  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = result == NULL;

  if (!error) {
    *result = value;
    get_info(result)->sign = !(get_info(&value)->sign);
  }

  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = result == NULL;

  if (!error) {
    *result = ZERO_DECIMAL;

    s21_decimal_data *info = get_info(&value);
    bool expo_bool = info->expo > 0;

    if (expo_bool) {
      s21_truncate(value, &value);
    }

    if (info->sign == SIGN_MINUS && expo_bool) {
      if (is_max(&value)) {
        error = RES_ERR;
      } else {
        s21_decimal one = ONE_DECIMAL;
        s21_sum(&value, &one, &value);
      }
    }

    if (!error) {
      *result = value;
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = result == NULL;

  if (!error) {
    *result = ZERO_DECIMAL;

    s21_decimal_data *info = get_info(&value);
    s21_decimal mod = s21_shift_10_right(&value, info->expo);
    info->expo = 0;

    if (mod.bits[LOW] >= 5) {
      if (is_max(&value)) {
        error = RES_ERR;
      } else {
        s21_decimal one = ONE_DECIMAL;
        s21_sum(&value, &one, &value);
      }
    }

    if (!error) {
      *result = value;
    }
  }
  return error;
}
