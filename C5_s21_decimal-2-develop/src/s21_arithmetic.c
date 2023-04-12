#include "s21_decimal.h"

int equalize_expo(s21_decimal *value_1, s21_decimal *value_2, bool bank_round) {
  int error = RES_OK;

  s21_decimal_data *info_val1 = get_info(value_1);
  s21_decimal_data *info_val2 = get_info(value_2);

  int expo_val1 = info_val1->expo;
  int expo_val2 = info_val2->expo;

  int min_expo = expo_val1 < expo_val2 ? expo_val1 : expo_val2;
  int max_expo = expo_val1 < expo_val2 ? expo_val2 : expo_val1;

  s21_decimal *min_dec = min_expo == expo_val1 ? value_1 : value_2;
  s21_decimal *max_dec = max_expo == expo_val1 ? value_1 : value_2;

  s21_decimal_data *min_info = min_expo == expo_val1 ? info_val1 : info_val2;
  s21_decimal_data *max_info = max_expo == expo_val1 ? info_val1 : info_val2;

  if (min_expo != max_expo) {
    int expo_difference = max_expo - min_expo;

    for (int i = 0; i < expo_difference && can_10_shift(min_dec); ++i) {
      s21_shift_10_left(min_dec, 1);
      min_expo += 1;
      min_info->expo = min_expo;
    }
  }

  if (min_expo != max_expo) {
    int expo_difference = max_expo - min_expo;

    s21_shift_10_right(max_dec, expo_difference);
    max_info->expo = min_expo;

    if (bank_round && is_zero(max_dec)) {
      int sign = info_val1->sign != info_val2->sign;

      if (sign == SIGN_MINUS) {
        setsign(min_dec, 0, 0);
      } else {
        if (is_max(value_1)) {
          error = RES_OVER;
        } else {
          if (getsign(min_dec, 0)) {
            s21_decimal one = ONE_DECIMAL;
            s21_sum(min_dec, &one, min_dec);
          }
        }
      }
    }
  }

  return error;
}

int s21_sum(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result_r) {
  int save_v1 = 0;
  int save_v2 = 0;
  int tmp = 0;

  for (int i = 0; i < MAX_LEN; ++i) {
    save_v1 = getsign(value_1, i);
    save_v2 = getsign(value_2, i);

    setsign(result_r, i, save_v1 ^ save_v2 ^ tmp);

    tmp = (save_v1 && save_v2) || ((save_v1 || save_v2) && tmp);
  }

  return tmp;
}

void s21_reverse_to_pos(s21_decimal *src) {
  s21_decimal one = MAX_DECIMAL;
  s21_sum(src, &one, src);
  s21_reverse(src);
}

void s21_reverse_to_neg(s21_decimal *src) {
  s21_decimal one = ONE_DECIMAL;

  s21_reverse(src);

  s21_sum(src, &one, src);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = ZERO_DECIMAL;

  int error = RES_OK;

  s21_decimal_data *info_val1 = get_info(&value_1);
  s21_decimal_data *info_val2 = get_info(&value_2);
  s21_decimal_data *res_info = get_info(result);

  int expo = 0;

  if (!is_zero(&value_1) && !is_zero(&value_2)) {
    error = equalize_expo(&value_1, &value_2, true);
    expo = info_val1->expo;
  } else {
    expo =
        info_val1->expo > info_val2->expo ? info_val1->expo : info_val2->expo;
  }

  if (is_zero(&value_1) && !error) info_val1->sign = 0;
  if (is_zero(&value_2) && !error) info_val2->sign = 0;

  int sign1 = info_val1->sign;
  int sign2 = info_val2->sign;

  bool sign_difference = sign1 != sign2;
  int sign = SIGN_PLUS;

  if (error == RES_OVER) {
    if (info_val1->sign == SIGN_MINUS && info_val2->sign == SIGN_MINUS)
      sign = SIGN_MINUS;
  }

  if (sign1 == SIGN_MINUS && sign2 == SIGN_MINUS) sign = SIGN_MINUS;

  if (sign_difference) {
    if (sign1 == SIGN_MINUS) s21_reverse_to_neg(&value_1);
    if (sign2 == SIGN_MINUS) s21_reverse_to_neg(&value_2);
  }

  if (!error) {
    int tmp = s21_sum(&value_1, &value_2, result);

    if ((sign1 == SIGN_MINUS || sign2 == SIGN_MINUS) && sign_difference) {
      sign = sign1 ^ sign2 ^ tmp;
    } else if (tmp) {
      error = RES_OVER;
    }
  }

  if (!error) {
    if (sign == SIGN_MINUS && sign_difference) s21_reverse_to_pos(result);
    res_info->sign = sign;
    res_info->expo = expo;
  } else {
    *result = ZERO_DECIMAL;
  }

  if (error == RES_OVER) {
    error = sign == SIGN_PLUS ? RES_INF_POS : RES_INF_NEG;
  }

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal_data *v2_info = get_info(&value_2);

  if (first_sign(&value_2) == -1) {
    v2_info->sign = 0;
  } else {
    v2_info->sign ^= 1;
  }
  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = ZERO_DECIMAL;
  int error = RES_OK;

  s21_decimal_data *v1_info = get_info(&value_1);
  s21_decimal_data *v2_info = get_info(&value_2);
  s21_decimal_data *res_info = get_info(result);

  int sign = v1_info->sign ^ v2_info->sign;

  int length1 = last_sign(&value_1) + 1;
  int length2 = last_sign(&value_2) + 1;

  int save_v1 = 0;
  int save_v2 = 0;

  s21_decimal tmp = ZERO_DECIMAL;

  if (length1 != 1 && length2 != 1 && length1 + length2 >= MAX_LEN + 2) {
    error = RES_OVER;
  }

  for (int i_value_2 = 0; i_value_2 < length2 && !error; ++i_value_2) {
    tmp = ZERO_DECIMAL;

    save_v1 = getsign(&value_2, i_value_2);

    for (int i_value_1 = 0; i_value_1 < length1; ++i_value_1) {
      save_v2 = getsign(&value_1, i_value_1);

      setsign(&tmp, i_value_1 + i_value_2, save_v1 && save_v2);
    }

    error = s21_sum(result, &tmp, result);
    if (error) error = RES_OVER;
  }

  if (error == RES_OVER) error = sign == SIGN_PLUS ? RES_INF_POS : RES_INF_NEG;

  if (error) {
    *result = ZERO_DECIMAL;
  } else {
    if (length1 == 0 || length2 == 0) {
      res_info->sign = 0;
    } else {
      res_info->sign = sign;
      int expo = v1_info->expo + v2_info->expo;

      if (expo > MAX_EXPO) {
        s21_decimal mod = s21_shift_10_right(result, expo - MAX_EXPO);
        s21_decimal one = ONE_DECIMAL;

        if (mod.bits[LOW] >= 5) s21_sum(result, &one, result);

        expo = MAX_EXPO;
      }

      res_info->expo = expo;
    }
  }

  return error;
}

s21_decimal s21_div_int(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result) {
  result->bits[LOW] = result->bits[MID] = result->bits[HIGH] = 0;
  s21_decimal v2_save = value_2;

  int len1 = 0;
  int len2 = last_sign(&value_2);
  int len_distinction = 0;

  while (s21_is_equals_int(&value_1, &value_2) ||
         s21_is_greater_int(&value_1, &value_2)) {
    len1 = last_sign(&value_1);
    len_distinction = len1 - len2;
    s21_shift_left(&value_2, len_distinction);

    if (s21_is_greater_int(&value_2, &value_1)) {
      s21_shift_right(&value_2, 1);
      len_distinction -= 1;
    }

    s21_reverse_to_neg(&value_2);
    s21_sum(&value_1, &value_2, &value_1);

    s21_decimal result_r = ONE_DECIMAL;
    s21_shift_left(&result_r, len_distinction);

    s21_sum(result, &result_r, result);

    value_2 = v2_save;
  }

  s21_decimal mod = value_1;
  return mod;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = RES_OK;
  *result = ZERO_DECIMAL;

  if (is_zero(&value_2)) {
    error = RES_ZERO_DIV;
  }

  if (!error) {
    equalize_expo(&value_1, &value_2, false);
    if (is_zero(&value_2)) error = RES_OVER;
  }

  s21_decimal_data *v1_info = get_info(&value_1);
  s21_decimal_data *v2_info = get_info(&value_2);
  s21_decimal_data *res_info = get_info(result);

  int sign = v1_info->sign != v2_info->sign;

  while (!is_zero(&value_1) && can_10_shift(result) && !error &&
         res_info->expo < MAX_EXPO) {
    int expo = 0;
    while (s21_is_lower_int(&value_1, &value_2) && can_10_shift(&value_1) &&
           can_10_shift(result)) {
      s21_shift_10_left(&value_1, 1);
      s21_shift_10_left(result, 1);
      expo += 1;
    }

    if (expo == 0 && s21_is_lower_int(&value_1, &value_2)) {
      value_1 = ZERO_DECIMAL;
    }

    s21_decimal result_r = ZERO_DECIMAL;
    value_1 = s21_div_int(value_1, value_2, &result_r);

    error = s21_sum(result, &result_r, result);
    res_info->expo += expo;
  }

  if (res_info->expo > MAX_EXPO) {
    s21_shift_10_right(result, res_info->expo - MAX_EXPO + 1);
    res_info->expo = MAX_EXPO;
  }

  if (error == RES_OVER) error = sign == SIGN_PLUS ? RES_INF_POS : RES_INF_NEG;

  if (error) {
    *result = ZERO_DECIMAL;
  } else if (is_zero(result)) {
    res_info->sign = 0;
    res_info->expo = 0;
  } else {
    res_info->sign = sign;
  }

  return error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = RES_OK;
  *result = ZERO_DECIMAL;

  if (is_zero(&value_2)) {
    error = RES_ZERO_DIV;
  }

  if (!error) {
    equalize_expo(&value_1, &value_2, false);
  }

  bool is_zero_delim = is_zero(&value_2);

  s21_decimal_data *v1_info = get_info(&value_1);
  s21_decimal_data *v2_info = get_info(&value_2);
  s21_decimal_data *res_info = get_info(result);

  int inv_sign = v1_info->sign != v2_info->sign;
  int sign = v2_info->sign;

  if (!error && !is_zero_delim) {
    int expo = v1_info->expo > v2_info->expo ? v1_info->expo : v2_info->expo;

    s21_decimal tmp = ZERO_DECIMAL;
    *result = s21_div_int(value_1, value_2, &tmp);

    if (inv_sign) res_info->sign = 1;

    res_info->expo = expo;
  }

  if (error == RES_OVER) error = sign == SIGN_PLUS ? RES_INF_POS : RES_INF_NEG;

  if (error) {
    *result = ZERO_DECIMAL;
  } else if (is_zero(result)) {
    res_info->sign = 0;
    res_info->expo = 0;
  }

  return error;
}
