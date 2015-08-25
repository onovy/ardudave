// Play LED animations

#include "animations.h"

int animPos = 0;
unsigned long lastBlink2 = 0;
byte* animation = animation1;
int animLen = sizeof(animation1) / sizeof(byte);
int blinkLength = 0;
int lastPinSwitchY = 0;
int lastPinSwitchR = 0;
int lastPinSwitchS = 0;

void game4(unsigned long time) {
  if (animation) {
    if (time - lastBlink2 > blinkLength) {
      lastBlink2 = time;
      
      if (animPos >= animLen) {
        animPos = 0;
        blinkLength = 0;
      }

      int speed = analogRead(PIN_POTEN_L);
      blinkLength = speed / *(animation + animPos);
      
      digitalWrite(PIN_LED_1, *(animation + animPos + 1));
      digitalWrite(PIN_LED_2, *(animation + animPos + 2));
      digitalWrite(PIN_LED_3, *(animation + animPos + 3));
      digitalWrite(PIN_LED_4, *(animation + animPos + 4));
      digitalWrite(PIN_LED_5, *(animation + animPos + 5));
      digitalWrite(PIN_LED_6, *(animation + animPos + 6));
      digitalWrite(PIN_LED_RGB_R, *(animation + animPos + 7));
      digitalWrite(PIN_LED_RGB_G, *(animation + animPos + 8));
      digitalWrite(PIN_LED_RGB_B, *(animation + animPos + 9));

      animPos += 10;
    }
  }
  
  bool reset = false;
    
  if (digitalRead(PIN_BUTTON_R) == LOW) {
    animation = animation1;
    animLen = sizeof(animation1) / sizeof(byte);
    reset = true;
  } else if (digitalRead(PIN_BUTTON_G) == LOW) {
    animation = animation2;
    animLen = sizeof(animation2) / sizeof(byte);
    reset = true;
  } else if (digitalRead(PIN_BUTTON_B) == LOW) {
    animation = animation3;
    animLen = sizeof(animation3) / sizeof(byte);
    reset = true;
  } else if (digitalRead(PIN_BUTTON_W) == LOW) {
    animation = animation4;
    animLen = sizeof(animation4) / sizeof(byte);
    reset = true;
  } else if (digitalRead(PIN_SWITCH_Y) != lastPinSwitchY) {
    lastPinSwitchY = !lastPinSwitchY;
    animation = animation5;
    animLen = sizeof(animation5) / sizeof(byte);
    reset = true;    
  } else if (digitalRead(PIN_SWITCH_R) != lastPinSwitchR) {
    lastPinSwitchR = !lastPinSwitchR;
    animation = animation6;
    animLen = sizeof(animation6) / sizeof(byte);
    reset = true;    
  } else if (digitalRead(PIN_SWITCH_S) != lastPinSwitchS) {
    lastPinSwitchS = !lastPinSwitchS;
    animation = animation7;
    animLen = sizeof(animation7) / sizeof(byte);
    reset = true;    
  }
    
  if (reset) {
    animPos = 0;
    lastBlink2 = 0;
    blinkLength = 0;
  }
}

