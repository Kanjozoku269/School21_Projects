#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define SIGN_PLUS 0
#define SIGN_MINUS 1

#define LAST_BIT 95
#define MAX_LEN 96
#define BIT_LEN 32

#define LOW 0
#define MID 1
#define HIGH 2
#define INFO 3

#define MAX_EXPO 28

#define BIT_COUNT 4
#define RANK_COUNT 3

#define RES_OK 0
#define RES_ERR 1
#define RES_INF_POS 1
#define RES_INF_NEG 2
#define RES_ZERO_DIV 3
#define RES_OVER 4

typedef struct {
  uint32_t void_1 : 16;
  uint32_t expo : 8;
  uint32_t void_2 : 7;
  uint32_t sign : 1;
} s21_decimal_data;

typedef struct {
  uint32_t bits[BIT_COUNT];
} s21_decimal;

#define ZERO_DECIMAL       \
  (s21_decimal) {          \
    .bits = { 0, 0, 0, 0 } \
  }
#define MAX_DECIMAL                                   \
  (s21_decimal) {                                     \
    .bits = { UINT32_MAX, UINT32_MAX, UINT32_MAX, 0 } \
  }

#define ONE_DECIMAL        \
  (s21_decimal) {          \
    .bits = { 1, 0, 0, 0 } \
  }

// Arithmetic

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sum(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result_r);
s21_decimal s21_div_int(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result);
void s21_reverse_to_pos(s21_decimal *src);
void s21_reverse_to_neg(s21_decimal *src);
int equalize_expo(s21_decimal *value_1, s21_decimal *value_2, bool bank_round);
// Arithmetic

void eq_comp_expo(s21_decimal *value_1, s21_decimal *value_2);
int s21_is_greater_int(s21_decimal *value_1, s21_decimal *value_2);
int s21_is_lower_int(s21_decimal *value_1, s21_decimal *value_2);
int s21_is_equals_int(s21_decimal *value_1, s21_decimal *value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
//

// Convert
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// Convert

// Other
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
// Other

int getsign(const s21_decimal *src, int i);
void setsign(s21_decimal *src, int i, int sign);

s21_decimal_data *get_info(s21_decimal *src);
uint32_t ftou(float num);

bool is_zero(s21_decimal *src);
bool is_max(s21_decimal *src);
int read_exp(float src);

// Sign
int first_sign(s21_decimal *src);
int last_sign(s21_decimal *src);
// Sign

// Shift
void s21_shift_right(s21_decimal *src, int shift);
int s21_shift_left(s21_decimal *src, int shift);
int s21_shift_10_left(s21_decimal *src, int shift);
s21_decimal s21_shift_10_right(s21_decimal *src, int shift);
bool can_10_shift(const s21_decimal *src);
// Shift

void s21_reverse(s21_decimal *src);

#endif  // S21_DECIMAL