#include "pitches.h"
#include "pins.h"

void setup() {
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  pinMode(pinLed5, OUTPUT);
  pinMode(pinLed6, OUTPUT);
  pinMode(pinLedRgbR, OUTPUT);
  pinMode(pinLedRgbG, OUTPUT);
  pinMode(pinLedRgbB, OUTPUT);
  pinMode(pinPiezo, OUTPUT);
  pinMode(pinButtonB, INPUT_PULLUP);
  pinMode(pinButtonW, INPUT_PULLUP);
  pinMode(pinButtonG, INPUT_PULLUP);
  pinMode(pinButtonR, INPUT_PULLUP);
  pinMode(pinSwitchY, INPUT_PULLUP);
  pinMode(pinSwitch2, INPUT_PULLUP);
  pinMode(pinSwitch3, INPUT_PULLUP);
  pinMode(pinPoten1, INPUT);
  pinMode(pinPoten2, INPUT);
  pinMode(pinIO, INPUT);
}

int fadeValue = 0;
int fadeStep = 1;
int fadeMax = 10;
bool music = false;

void loop() {
   fadeValue += fadeStep;
  
    if (fadeValue >= fadeMax || fadeValue <= 0) {
        fadeStep = -fadeStep;
    }

    if (!music) {
    analogWrite(pinLed1, fadeValue); // green
    analogWrite(pinLed2, fadeMax - fadeValue); // red
    analogWrite(pinLed3, fadeValue); // blue
    analogWrite(pinLed4, fadeMax - fadeValue); // yellow
    analogWrite(pinLed5, fadeValue);
    analogWrite(pinLed6, fadeMax - fadeValue);
    } else {
      digitalWrite(pinLed1, 1);
      digitalWrite(pinLed2, 1);
      digitalWrite(pinLed3, 1);
      digitalWrite(pinLed4, 1);
      digitalWrite(pinLed5, 1);
      digitalWrite(pinLed6, 1);
    }

    int color = analogRead(pinPoten1);
    int brig = analogRead(pinPoten2);
    brig = 512;

    long colorR = color & (B111 << 7) >> 2;
    long colorG = color & (B1111 << 3) << 1;
    long colorB = color & B111 << 5;

    colorR = colorR * brig / 1024;
    colorG = colorG * brig / 1024;
    colorB = colorB * brig / 1024;

    colorR = 128;
    colorG = 64;
    colorB = 64;

    analogWrite(pinLedRgbR, fadeValue);
    analogWrite(pinLedRgbG, fadeMax - fadeValue);
    analogWrite(pinLedRgbB, fadeValue);

    if (digitalRead(pinButtonB) == LOW or true) {
      if (!music) {
        tone(pinPiezo, NOTE_D3);
        music = true;
      }
    } else if (digitalRead(pinButtonW) == LOW) {
      if (!music) {
        tone(pinPiezo, NOTE_D3);
        music = true;
      }
    } else if (digitalRead(pinButtonG) == LOW) {
      if (!music) {
        tone(pinPiezo, NOTE_E3);
        music = true;
      }
    } else if (digitalRead(pinButtonR) == LOW) {
      if (!music) {
        tone(pinPiezo, NOTE_F3);
        music = true;
      }
    } else if (digitalRead(pinSwitchY) == LOW) {
      if (!music) {
        tone(pinPiezo, NOTE_G3);
        music = true;
      }
    } else if (digitalRead(pinSwitch2) == LOW) {
      if (!music) {
        tone(pinPiezo, NOTE_A3);
        music = true;
      }
    } else if (digitalRead(pinSwitch3) == LOW) {
      if (!music) {
        tone(pinPiezo, NOTE_B3);
        music = true;
      }
    } else {
      if (music) {
        noTone(pinPiezo);
        TCCR3A = (1 << WGM30);
        music = false;
      }
    }
    
    delay(100);
}

