#include "s21_decimal.h"

#define COMP_LOWER -1
#define COMP_EQUALS 0
#define COMP_GREATER 1

int check_num(uint32_t num_1, uint32_t num_2) {
  int result_r = COMP_EQUALS;
  if (num_1 > num_2)
    result_r = COMP_GREATER;
  else if (num_1 < num_2)
    result_r = COMP_LOWER;
  return result_r;
}

int s21_is_greater_int(s21_decimal *value_1, s21_decimal *value_2) {
  int result_r = check_num(value_1->bits[HIGH], value_2->bits[HIGH]);
  if (!result_r) result_r = check_num(value_1->bits[MID], value_2->bits[MID]);
  if (!result_r) result_r = check_num(value_1->bits[LOW], value_2->bits[LOW]);
  result_r = result_r == COMP_GREATER;
  return result_r;
}

int s21_is_lower_int(s21_decimal *value_1, s21_decimal *value_2) {
  int result_r = check_num(value_1->bits[HIGH], value_2->bits[HIGH]);
  if (!result_r) result_r = check_num(value_1->bits[MID], value_2->bits[MID]);
  if (!result_r) result_r = check_num(value_1->bits[LOW], value_2->bits[LOW]);
  result_r = result_r == COMP_LOWER;
  return result_r;
}

int s21_is_equals_int(s21_decimal *value_1, s21_decimal *value_2) {
  return value_1->bits[LOW] == value_2->bits[LOW] &&
         value_1->bits[MID] == value_2->bits[MID] &&
         value_1->bits[HIGH] == value_2->bits[HIGH];
}

void eq_comp_expo(s21_decimal *value_1, s21_decimal *value_2) {
  if (!is_zero(value_1) && !is_zero(value_2)) {
    equalize_expo(value_1, value_2, false);
  } else {
    if (is_zero(value_1)) *value_1 = ZERO_DECIMAL;
    if (is_zero(value_2)) *value_2 = ZERO_DECIMAL;
  }
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal_data *v1_info = get_info(&value_1);
  s21_decimal_data *v2_info = get_info(&value_2);

  eq_comp_expo(&value_1, &value_2);

  int result_r = s21_is_equals_int(&value_1, &value_2);

  if (v1_info->expo != v2_info->expo) {
    result_r = 0;
  }

  if (v1_info->sign != v2_info->sign) {
    result_r = 0;
  }

  return result_r;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal_data *info_val1 = get_info(&value_1);
  s21_decimal_data *info_val2 = get_info(&value_2);

  eq_comp_expo(&value_1, &value_2);
  int result_r = 0;

  if (info_val1->sign == SIGN_PLUS && info_val2->sign == SIGN_PLUS) {
    result_r = s21_is_lower_int(&value_1, &value_2);
  } else if (info_val1->sign == SIGN_MINUS && info_val2->sign == SIGN_MINUS) {
    result_r = s21_is_greater_int(&value_1, &value_2);
  } else {
    result_r = !(info_val2->sign);
  }

  return result_r;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal_data *info_val1 = get_info(&value_1);
  s21_decimal_data *info_val2 = get_info(&value_2);

  eq_comp_expo(&value_1, &value_2);
  int result_r = 0;

  if (info_val1->sign == SIGN_PLUS && info_val2->sign == SIGN_PLUS) {
    result_r = s21_is_greater_int(&value_1, &value_2);
  } else if (info_val1->sign == SIGN_MINUS && info_val2->sign == SIGN_MINUS) {
    result_r = s21_is_lower_int(&value_1, &value_2);
  } else {
    result_r = !(info_val1->sign);
  }
  return result_r;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  eq_comp_expo(&value_1, &value_2);
  int result_r =
      s21_is_less(value_1, value_2) == 1 || s21_is_equal(value_1, value_2) == 1;
  return result_r;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  eq_comp_expo(&value_1, &value_2);
  int result_r = s21_is_greater(value_1, value_2) == 1 ||
                 s21_is_equal(value_1, value_2) == 1;
  return result_r;
}