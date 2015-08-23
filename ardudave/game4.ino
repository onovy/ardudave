// Play LED animations

#include "animations.h"

int animPos = 0;
unsigned long lastBlink2 = 0;
byte* animation = animation1;
int animLen = sizeof(animation1) / sizeof(byte);
int blinkLength = 0;
int lastPinSwitchY = 0;
int lastPinSwitchR = 0;
int lastPinSwitch3 = 0;

void game4(unsigned long time) {
  if (animation) {
    if (time - lastBlink2 > blinkLength) {
      lastBlink2 = time;
      
      if (animPos >= animLen) {
        animPos = 0;
        blinkLength = 0;
      }

      int speed = analogRead(pinPotenL);
      blinkLength = speed / *(animation + animPos);
      
      digitalWrite(pinLed1, *(animation + animPos + 1));
      digitalWrite(pinLed2, *(animation + animPos + 2));
      digitalWrite(pinLed3, *(animation + animPos + 3));
      digitalWrite(pinLed4, *(animation + animPos + 4));
      digitalWrite(pinLed5, *(animation + animPos + 5));
      digitalWrite(pinLed6, *(animation + animPos + 6));
      digitalWrite(pinLedRgbR, *(animation + animPos + 7));
      digitalWrite(pinLedRgbG, *(animation + animPos + 8));
      digitalWrite(pinLedRgbB, *(animation + animPos + 9));

      animPos += 10;
    }
  }
  
  bool reset = false;
    
  if (digitalRead(pinButtonR) == LOW) {
    animation = animation1;
    animLen = sizeof(animation1) / sizeof(byte);
    reset = true;
  } else if (digitalRead(pinButtonG) == LOW) {
    animation = animation2;
    animLen = sizeof(animation2) / sizeof(byte);
    reset = true;
  } else if (digitalRead(pinButtonB) == LOW) {
    animation = animation3;
    animLen = sizeof(animation3) / sizeof(byte);
    reset = true;
  } else if (digitalRead(pinButtonW) == LOW) {
    animation = animation4;
    animLen = sizeof(animation4) / sizeof(byte);
    reset = true;
  } else if (digitalRead(pinSwitchY) != lastPinSwitchY) {
    lastPinSwitchY = !lastPinSwitchY;
    animation = animation5;
    animLen = sizeof(animation5) / sizeof(byte);
    reset = true;    
  } else if (digitalRead(pinSwitchR) != lastPinSwitchR) {
    lastPinSwitchR = !lastPinSwitchR;
    animation = animation6;
    animLen = sizeof(animation6) / sizeof(byte);
    reset = true;    
  } else if (digitalRead(pinSwitch3) != lastPinSwitch3) {
    lastPinSwitch3 = !lastPinSwitch3;
    animation = animation5;
    animLen = sizeof(animation5) / sizeof(byte);
    reset = true;    
  }
    
  if (reset) {
    animPos = 0;
    lastBlink2 = 0;
    blinkLength = 0;
  }
}

