// Play melodies

#include "pitches.h"
#include "melodies.h"

int melodyPos = 0;
unsigned long lastTone = 0;
int* melody = 0;
int melodyLen = 0;
int toneLength = 0;

void game3(unsigned long time) {
  if (melody) {
    if (time - lastTone > toneLength) {
      int speed = analogRead(pinPotenL) * 1.5;
      int delayLength = toneLength;
      toneLength = speed / *(melody + melodyPos);
      int toneFreq = *(melody + melodyPos + 1);
      lastTone = time;
      
      melodyPos += 2;
      if (melodyPos > melodyLen) {
        melody = 0;
        noTone(pinPiezo);
        TCCR3A = (1 << WGM30);
      } else {
        noTone(pinPiezo);
        delay(delayLength / 3);
        lastTone = millis();
        if (toneFreq > 0) {
          tone(pinPiezo, toneFreq);
        }
      }
    }
  } else {
    bool play = false;
    
    if (digitalRead(pinButtonR) == LOW) {
      melody = melody1;
      melodyLen = sizeof(melody1) / sizeof(int);
      play = true;
    } else if (digitalRead(pinButtonG) == LOW) {
      melody = melody2;
      melodyLen = sizeof(melody2) / sizeof(int);
      play = true;
    } else if (digitalRead(pinButtonB) == LOW) {
      melody = melody3;
      melodyLen = sizeof(melody3) / sizeof(int);
      play = true;
    } else if (digitalRead(pinButtonW) == LOW) {
      melody = melody4;
      melodyLen = sizeof(melody4) / sizeof(int);
      play = true;
    }
    
    if (play) {
      melodyPos = 0;
      lastTone = 0;
      toneLength = 0;
    }
  }
}

