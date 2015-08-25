// Play melodies

#include "pitches.h"
#include "melodies.h"

int melodyPos = 0;
unsigned long lastTone = 0;
unsigned int* melody = 0;
int melodyLen = 0;
int toneLength = 0;
int leds[99];

void sort(int a[], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}

void fillLeds() {
  int melodySort[melodyLen];
  for (int i = 0 ; i < melodyLen ; i++) {
    melodySort[i] = TONE_FREQ(melody[i]);
  }
  sort(melodySort, melodyLen);

  int len = 0;
  int melodySort2[melodyLen];
  int last = 0;
  for (int i = 0 ; i < melodyLen ; i++) {
    if (last != melodySort[i]) {
      melodySort2[len] = melodySort[i];
      last = melodySort[i];
      len++;
    }
  }

  for (int i = 0 ; i < melodyLen ; i++) {
    for (int j = 0 ; j < len ; j++) {
      if (melodySort2[j] == melody[i] << 3 >> 3) {
        leds[i] = j;
        break;
      }
    }
  }
}

void game3(unsigned long time) {  
  if (melody) {
    if (time - lastTone > toneLength) {
      int speed = analogRead(PIN_POTEN_L) * 1.5;
      int delayLength = toneLength;

      toneLength = speed / TONE_LEN(*(melody + melodyPos));
      int toneFreq = TONE_FREQ(*(melody + melodyPos));
      lastTone = time;
      
      melodyPos++;
      if (melodyPos > melodyLen) {
        melody = 0;
        reset();
        noTone(PIN_PIEZO);
        TCCR3A = (1 << WGM30);
      } else {
        reset();
        noTone(PIN_PIEZO);
        delay(delayLength / 3);
        lastTone = millis();
        if (toneFreq > 0) {
          tone(PIN_PIEZO, toneFreq);

          switch (leds[melodyPos]) {
            case 0:
              digitalWrite(PIN_LED_1, HIGH);
            break;
            case 1:
              digitalWrite(PIN_LED_2, HIGH);
            break;
            case 2:
              digitalWrite(PIN_LED_3, HIGH);
            break;
            case 3:
              digitalWrite(PIN_LED_4, HIGH);
            break;
            case 4:
              digitalWrite(PIN_LED_5, HIGH);
            break;
            case 5:
              digitalWrite(PIN_LED_6, HIGH);
            break;
            case 6:
              digitalWrite(PIN_LED_RGB_R, HIGH);
            break;
            case 7:
              digitalWrite(PIN_LED_RGB_G, HIGH);
            break;
            default:
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
      fillLeds();
    }
  }
}

