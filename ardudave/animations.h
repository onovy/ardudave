#include <avr/pgmspace.h>

#define ANIMATION(len, led1, led2, led3, led4, led5, led6, led7, led8, led9) ( \
  ((len==1 ? 0 : (len == 2 ? 1 : (len == 4 ? 2 : (len == 8 ? 3 : (len == 16 ? 4 : 0))))) << 9) + \
  (led9 << 8) + \
  (led8 << 7) + \
  (led7 << 6) + \
  (led6 << 5) + \
  (led5 << 4) + \
  (led4 << 3) + \
  (led3 << 2) + \
  (led2 << 1) + \
  (led1) )
#define ANIMATION_LEN(anim) ( pow(2, (anim >> 9)) )
#define ANIMATION_LED9(anim) ( anim << 7 >> 7 >> 8 )
#define ANIMATION_LED8(anim) ( anim << 8 >> 8 >> 7 )
#define ANIMATION_LED7(anim) ( anim << 9 >> 9 >> 6 )
#define ANIMATION_LED6(anim) ( anim << 10 >> 10 >> 5 )
#define ANIMATION_LED5(anim) ( anim << 11 >> 11 >> 4 )
#define ANIMATION_LED4(anim) ( anim << 12 >> 12 >> 3 )
#define ANIMATION_LED3(anim) ( anim << 13 >> 13 >> 2 )
#define ANIMATION_LED2(anim) ( anim << 14 >> 14 >> 1 )
#define ANIMATION_LED1(anim) ( anim << 15 >> 15 )

const static unsigned int animation1[] PROGMEM = {
  ANIMATION(4, 1, 0, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 1, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 1, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 1, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 1, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 1, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 1, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 0, 1, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 0, 0, 1),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 0, 1, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 1, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 1, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 1, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 1, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 1, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 1, 0, 0, 0, 0, 0, 0, 0),
};

const static unsigned int animation2[] PROGMEM = {
  ANIMATION(4, 1, 0, 1, 0, 1, 0, 1, 0, 1),
  ANIMATION(4, 0, 1, 0, 1, 0, 1, 0, 1, 0),
};

const static unsigned int animation3[] PROGMEM = {
  ANIMATION(4, 1, 0, 0, 0, 0, 0, 1, 1, 1),
  ANIMATION(4, 0, 1, 0, 0, 0, 1, 0, 0, 0),
  ANIMATION(4, 0, 0, 1, 0, 1, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 1, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 1, 0, 1, 0, 0, 0, 0),
  ANIMATION(4, 0, 1, 0, 0, 0, 1, 0, 0, 0),
  ANIMATION(4, 1, 0, 0, 0, 0, 0, 1, 1, 1),
  ANIMATION(4, 1, 1, 0, 0, 0, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 0, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 0, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 0, 0, 0, 1, 1, 1, 1),
};

const static unsigned int animation4[] PROGMEM = {
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 0, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 1, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 1, 1, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 1, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 0, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 0, 0, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 0, 0, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 0, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 0, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 0, 1, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 1, 1, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 1, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 1, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 1, 0, 0, 0, 0, 0, 0, 0, 0),
};

const static unsigned int animation5[] PROGMEM = {
  ANIMATION(4, 1, 1, 0, 0, 1, 1, 0, 0, 0),
  ANIMATION(4, 0, 1, 1, 0, 0, 1, 1, 1, 1),
  ANIMATION(4, 0, 0, 1, 1, 0, 0, 1, 1, 1),
  ANIMATION(4, 1, 0, 0, 1, 1, 0, 0, 0, 0),
};

const static unsigned int animation6[] PROGMEM = {
  ANIMATION(4, 0, 1, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 0, 1, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 0, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 0, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 0, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 1, 0, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 1, 1, 0, 0, 0),
  ANIMATION(4, 1, 1, 1, 1, 1, 0, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 1, 0, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 1, 0, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 1, 0, 1, 1, 1, 1, 1, 1),
  ANIMATION(4, 1, 0, 1, 1, 1, 1, 1, 1, 1),
};

const static unsigned int animation7[] PROGMEM = {
  ANIMATION(4, 1, 0, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 1, 1, 1),
  ANIMATION(4, 0, 1, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 1, 0, 0, 0),
  ANIMATION(4, 0, 0, 1, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 1, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 1, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 1, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 1, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 1, 0, 0, 0),
  ANIMATION(4, 0, 1, 0, 0, 0, 0, 0, 0, 0),
  ANIMATION(4, 0, 0, 0, 0, 0, 0, 1, 1, 1),
};
