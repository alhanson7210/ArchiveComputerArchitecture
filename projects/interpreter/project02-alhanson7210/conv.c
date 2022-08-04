/* conv.h - performs conversions between string/uint and between bases */
/* 
 * comments are notes for remembering
 */
/* libraries and imports */
#include <ctype.h>
#include "ntcalc.h"
/* macros */
#define DEFAULT 0
#define VALUESTOP 0
#define ZEROMARK 0
#define IDENTITY 1
#define USEDBITS 2
#define BINARYBASE 2
#define HEXBITS 0xf
#define HEXWIDTH 4
#define HEXDIGITS 8
#define DECIMALBASE 10
#define HEX 10
#define HEXBASE 16
#define BITSIZE 32
#define MAXHEXVALUE 0xFFFFFFFF
#define NULTERMINATE '\0'
#define ZEROBIT '0'
#define ONEBIT '1'
#define BINARYIDENTITY 'b'
#define HEXIDENTITY 'x'
#define SIGN '-'
#define DIGITS "0123456789ABCDEF"
/* globals */
enum numbers { ONE=1, TWO, THREE, FOUR, FIVE};
char digits[] = DIGITS;
/* prototypes */
uint32_t conv_width_mask(int width);
/* methods */
/**
 * get int value of string binary or decimal character
 */
uint32_t conv_str_digit_to_digit(char ch) {
  return ch - '0';
}
/**
 * get int value of string hexadecimal identity
 */
uint32_t conv_str_hex_identity_to_digit(char ch) {
  uint32_t digit = DEFAULT;

  switch (ch)
  {
    case 'a':
      digit = HEX;
      break;
    case 'b':
      digit = HEX + ONE;
      break;
    case 'c':
      digit = HEX + TWO;
      break;
    case 'd':
      digit = HEX + THREE;
      break;
    case 'e':
      digit = HEX + FOUR;
      break;
    case 'f':
      digit = HEX + FIVE;
      break;
    default:
      break;
  }

  return digit;
}
/**
 * check for valid hex identity
 */
bool conv_is_hex_identity(char ch) {
  return ch >= 'a' && ch <= 'f';
}
/**
 * check for valid binary or decimal value
 */
bool conv_is_digit(char ch) {
  return ch >= '0' && ch <= '9';
}
/**
 * convert string decimal, binary, and/or hex to an unsigned 
 * int based on the given base
 */
uint32_t conv_str_to_uint32(char *str, uint32_t base) {
  uint32_t retval = DEFAULT;
  uint32_t place_val = ONE;

  for (int i = strlen(str) - ONE; i >= VALUESTOP; i--) {

    char ch = tolower(str[i]);
    uint32_t digit;

    if (conv_is_hex_identity(ch))
      digit = conv_str_hex_identity_to_digit(ch);
         
    if (conv_is_digit(ch))
      digit = conv_str_digit_to_digit(ch);

    retval += digit * place_val;
    place_val *= base;
  }
  return retval;
}
/**
 * convert 32 bit integer to a string decimal form
 * added implementation handles negative numbers using msb
 *
 * the same result for getting negative numbers can also be
 * obtained by converting value to a binary string of 2's
 * compliment and masking it by counting the bits
 * 
 * or getting the 2's compliment of value and by masking by 
 * the width again to get the values you want
 * 
 */
void conv_uint32_to_decstr(struct ntlang_config_st *nc, uint32_t value, 
                           char *result_str) {
  uint32_t div, rem;
  int i, j = DEFAULT, len;
  int msb = nc->width - ONE;
  char tmp[SCAN_INPUT_LEN] = { DEFAULT };
  bool sign = false;
    
  if (!nc->unsigned_output) {
    if (((value >> msb) & 0b1)) {
      sign = true;
      value = (~value + 0b1) & conv_width_mask(nc->width);
    }
  }
    
  len = DEFAULT;
  if (value == VALUESTOP) {
        tmp[len++] = digits[VALUESTOP];
  } else {
    while (value != VALUESTOP) {
      div = value / DECIMALBASE;
      rem = value % DECIMALBASE;
      tmp[len] = digits[rem];
      ++len;
      value = div;
    }
        
    if (sign)
      tmp[len++] = SIGN;
  }

  for (i = len; i > VALUESTOP; i--, j++) {
    result_str[j] = tmp[i-ONE];
  }
  result_str[j] = NULTERMINATE;
}
/**
 * convert 32 bit integer to a string binary form
 */
void conv_uint32_to_binstr(int width, uint32_t value, 
                           char *result_str) {
  int i, j;
    
  result_str[ZEROMARK] = ZEROBIT;
  result_str[IDENTITY] = BINARYIDENTITY;
  j = USEDBITS;

  for (i = width - ONE; i >= VALUESTOP; --i) {
    if (((value >> i) & 0b1))
      result_str[j] = ONEBIT;
    else
      result_str[j] = ZEROBIT;
    ++j;      
  }

  result_str[j] = NULTERMINATE;
}
/**
 * convert 32 bit integer to string hex form
 */
void conv_uint32_to_hexstr(int width, uint32_t value,
                           char *result_str) {
  int hexidx, resultidx, hexwidth, bit, counter;
  int hexlit[HEXDIGITS] = { DEFAULT };
    
  hexwidth = width / HEXWIDTH;
  result_str[ZEROMARK] = ZEROBIT;
  result_str[IDENTITY] = HEXIDENTITY;
  resultidx = USEDBITS;
  bit = DEFAULT;

  for(counter = hexwidth; counter > VALUESTOP; counter--) {
  	hexlit[bit++] = value & HEXBITS;
  	value = value >> HEXWIDTH;
  }

  for (hexidx = hexwidth; hexidx > VALUESTOP; hexidx--, resultidx++) {
    result_str[resultidx] = digits[hexlit[hexidx-ONE]];
  }
  result_str[resultidx] = NULTERMINATE;
}
/**
 * remove bit values from 32 bits down masked width
 * this can also can be done in reverse by taking ONE and shifting
 * by the width of bits, and subtracting by 1:
 * (1 << width) - 1
 */
uint32_t conv_width_mask(int width) {
  return MAXHEXVALUE >> (BITSIZE-width);
}
/*
 * convert a given 32 bit integer to a string in the form or prism
 * of a BINARYBASE, DECIMALBASE, or HEXBASE for printing
 */
void conv_uint32_to_str(struct ntlang_config_st *nc, uint32_t value,
                        char *result_str) {
  uint32_t iresult;
    
  iresult = value & conv_width_mask(nc->width);
    
  switch (nc->base) {
    case BINARYBASE:
      conv_uint32_to_binstr(nc->width, iresult, result_str);
      break;
    case DECIMALBASE:
      conv_uint32_to_decstr(nc, iresult, result_str);
      break;
    case HEXBASE:
      conv_uint32_to_hexstr(nc->width, iresult, result_str);
      break;
  }
}
