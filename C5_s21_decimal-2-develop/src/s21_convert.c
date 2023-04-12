#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = dst == NULL;

  if (!error) {
    int new_src = src;

    *dst = ZERO_DECIMAL;
    s21_decimal_data *dec_data = get_info(dst);

    if (src < 0) {
      dec_data->sign = 1;
      new_src *= -1;
    }
    dst->bits[LOW] = new_src;
  }

  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_truncate(src, &src);

  s21_decimal_data *src_data = get_info(&src);

  int error = last_sign(&src) >= 31;
  error = dst == NULL;

  if (!error) {
    *dst = src.bits[LOW];
    if (src_data->sign) {
      *dst *= -1;
    }
  }

  return error;
}

int read_exp(float src) {
  int nev_src = *(uint32_t *)&src;

  int mask = 0b11111111u << 23;
  int expo = nev_src & mask;
  expo >>= 23;

  return expo - 127;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = dst == NULL;

  if (!error) {
    *dst = ZERO_DECIMAL;
    s21_decimal_data *dst_info = get_info(dst);

    int exp_fut = read_exp(src);

    if (exp_fut > LAST_BIT) {
      error = RES_ERR;
    } else if (src != 0.0) {
      if (src < 0) {
        src = -src;
        dst_info->sign = 1;
      }

      float srct = src;
      float ulti = 1.0f;

      for (; !((int)srct); srct *= 10, ulti *= 10) dst_info->expo += 1;
      for (; srct < 10000000 && srct != (int)srct; srct *= 10, ulti *= 10)
        dst_info->expo += 1;

      if (ulti != 1.0f && fmodf(src * ulti, 10.0f) == 0) {
        ulti /= 10;
        dst_info->expo -= 1;
      }

      if (ulti != 1.0f) {
        src *= ulti;
      }

      exp_fut = read_exp(src);

      if (exp_fut < -94 || dst_info->expo > MAX_EXPO) {
        error = RES_ERR;
      } else {
        uint32_t usrc = ftou(src);

        setsign(dst, exp_fut, 1);
        exp_fut -= 1;

        for (int mask = 0x400000; mask > 0 && exp_fut >= 0;
             mask >>= 1, exp_fut -= 1) {
          int bit = !!(mask & usrc);
          setsign(dst, exp_fut, bit);
        }
      }
    }
  }

  if (error && dst != NULL) {
    *dst = ZERO_DECIMAL;
  }

  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = dst == NULL;

  if (!error) {
    float result_r = 0.0f;
    s21_decimal_data *src_data = get_info(&src);

    for (int i = 0; i < MAX_LEN; ++i) {
      if (getsign(&src, i)) {
        result_r += powf(2.0f, (float)i);
      }
    }

    float del = 1.0f;
    for (int i = 0; i < src_data->expo; ++i) {
      del *= 10.0f;
    }

    if (del != 1.0f) {
      result_r /= del;
    }

    if (src_data->sign) {
      result_r = -result_r;
    }

    *dst = result_r;
  }

  return error;
}
