// Play LED animations

#include "animations.h"

int animPos = 0;
unsigned long lastBlink2 = 0;
const unsigned int* animation = animation1;
int animLen = sizeof(animation1) / sizeof(int);
int blinkLength = 0;
int lastPinSwitchY = 0;
int lastPinSwitchR = 0;
int lastPinSwitchS = 0;

void game4(unsigned long time) {
  powerSave();

  bool reset = false;
  if (digitalRead(PIN_BUTTON_R) == LOW) {
    animation = animation1;
    animLen = sizeof(animation1) / sizeof(int);
    reset = true;
  } else if (digitalRead(PIN_BUTTON_G) == LOW) {
    animation = animation2;
    animLen = sizeof(animation2) / sizeof(int);
    reset = true;
  } else if (digitalRead(PIN_BUTTON_B) == LOW) {
    animation = animation3;
    animLen = sizeof(animation3) / sizeof(int);
    reset = true;
  } else if (digitalRead(PIN_BUTTON_W) == LOW) {
    animation = animation4;
    animLen = sizeof(animation4) / sizeof(int);
    reset = true;
  } else if (digitalRead(PIN_SWITCH_Y) != lastPinSwitchY) {
    lastPinSwitchY = !lastPinSwitchY;
    animation = animation5;
    animLen = sizeof(animation5) / sizeof(int);
    reset = true;    
  } else if (digitalRead(PIN_SWITCH_R) != lastPinSwitchR) {
    lastPinSwitchR = !lastPinSwitchR;
    animation = animation6;
    animLen = sizeof(animation6) / sizeof(int);
    reset = true;    
  } else if (digitalRead(PIN_SWITCH_S) != lastPinSwitchS) {
    lastPinSwitchS = !lastPinSwitchS;
    animation = animation7;
    animLen = sizeof(animation7) / sizeof(int);
    reset = true;    
  }
    
  if (reset) {
    animPos = 0;
    lastBlink2 = time;
    blinkLength = 0;
  }

  if (animation) {
    if (time - lastBlink2 > blinkLength) {
      lastBlink2 = time;
      
      if (animPos >= animLen) {
        animPos = 0;
        blinkLength = 0;
      }

      int speed = analogRead(PIN_POTEN_L);
      unsigned int oneAnim = pgm_read_word_near(animation + animPos);
      blinkLength = speed / ANIMATION_LEN(oneAnim);
      
      digitalWrite(PIN_LED_1, ANIMATION_LED1(oneAnim));
      digitalWrite(PIN_LED_2, ANIMATION_LED2(oneAnim));
      digitalWrite(PIN_LED_3, ANIMATION_LED3(oneAnim));
      digitalWrite(PIN_LED_4, ANIMATION_LED4(oneAnim));
      digitalWrite(PIN_LED_5, ANIMATION_LED5(oneAnim));
      digitalWrite(PIN_LED_6, ANIMATION_LED6(oneAnim));
      digitalWrite(PIN_LED_RGB_R, ANIMATION_LED7(oneAnim));
      digitalWrite(PIN_LED_RGB_G, ANIMATION_LED8(oneAnim));
      digitalWrite(PIN_LED_RGB_B, ANIMATION_LED9(oneAnim));

      animPos++;
    }
  }
}

