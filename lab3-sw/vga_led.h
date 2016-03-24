#ifndef _VGA_LED_H
#define _VGA_LED_H

#include <linux/ioctl.h>

#define VGA_LED_DIGITS 8

typedef struct {
  unsigned char digit;    /* 0, 1, .. , VGA_LED_DIGITS - 1 */
  unsigned char segments; /* LSB is segment a, MSB is decimal point */
} vga_led_arg_t;

#define VGA_LED_MAGIC 'q'

/* ioctls and their arguments */
#define VGA_LED_WRITE_DIGIT _IOW(VGA_LED_MAGIC, 1, vga_led_arg_t *)
#define VGA_LED_READ_DIGIT  _IOWR(VGA_LED_MAGIC, 2, vga_led_arg_t *)

#endif


#define B_0000  0
#define B_0001  1
#define B_0010  2
#define B_0011  3
#define B_0100  4
#define B_0101  5
#define B_0110  6
#define B_0111  7
#define B_1000  8
#define B_1001  9
#define B_1010  a
#define B_1011  b
#define B_1100  c
#define B_1101  d
#define B_1110  e
#define B_1111  f

#define _B2H(bits)  B_##bits
#define B2H(bits)   _B2H(bits)
#define _HEX(n)     0x##n
#define HEX(n)      _HEX(n)
#define _CCAT(a,b)  a##b
#define CCAT(a,b)   _CCAT(a,b)

#define BYTE(a,b)       HEX( CCAT(B2H(a),B2H(b)) )
#define NUMBER(a,b,c)   HEX(CCAT(CCAT(B2H(a), B2H(b)), B2H(c)))
#define DNUMBER(a,b,c,d,e,f) HEX(CCAT(CCAT(CCAT(B2H(a), B2H(b)), CCAT(B2H(c), B2H(d))),CCAT(B2H(e),B2H(f))))
