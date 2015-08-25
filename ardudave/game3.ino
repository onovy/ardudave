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
      int speed = analogRead(PIN_POTEN_L) * 1.5;
      int delayLength = toneLength;
      toneLength = speed / *(melody + melodyPos);
      int toneFreq = *(melody + melodyPos + 1);
      lastTone = time;
      
      melodyPos += 2;
      if (melodyPos > melodyLen) {
        melody = 0;
        noTone(PIN_PIEZO);
        TCCR3A = (1 << WGM30);
        reset();
      } else {
        noTone(PIN_PIEZO);
        delay(delayLength / 3);
        lastTone = millis();
        if (toneFreq > 0) {
          tone(PIN_PIEZO, toneFreq);
         
          switch (leds[melodyPos]) {
            case 1:
              digitalWrite(PIN_LED_1, HIGH);
            break;
            case 2:
              digitalWrite(PIN_LED_2, HIGH);
            break;
            case 3:
              digitalWrite(PIN_LED_3, HIGH);
            break;
            case 4:
              digitalWrite(PIN_LED_4, HIGH);
            break;
            case 5:
              digitalWrite(PIN_LED_5, HIGH);
            break;
            case 6:
              digitalWrite(PIN_LED_6, HIGH);
            break;
            default:
              digitalWrite(PIN_LED_RGB_R, HIGH);
              digitalWrite(PIN_LED_RGB_G, HIGH);
              digitalWrite(PIN_LED_RGB_B, HIGH);
            break;
          }
        }
      }
    }
  } else {
    bool play = false;
    
    if (digitalRead(PIN_BUTTON_R) == LOW) {
      melody = melody1;
      melodyLen = sizeof(melody1) / sizeof(int);
      play = true;
    } else if (digitalRead(PIN_BUTTON_G) == LOW) {
      melody = melody2;
      melodyLen = sizeof(melody2) / sizeof(int);
      play = true;
    } else if (digitalRead(PIN_BUTTON_B) == LOW) {
      melody = melody3;
      melodyLen = sizeof(melody3) / sizeof(int);
      play = true;
    } else if (digitalRead(PIN_BUTTON_W) == LOW) {
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

