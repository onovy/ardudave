// Play melodies

#include "pitches.h"
#include "melodies.h"

int melodyPos = 0;
unsigned long lastTone = 0;
const unsigned int* melody = 0;
int melodyLen = 0;
int toneLength = 0;
unsigned int leds[99];

void sort(unsigned int a[], unsigned int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    unsigned int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}

void fillLeds() {
  unsigned int melodySort[melodyLen];
  for (int i = 0 ; i < melodyLen ; i++) {
    unsigned int oneTone = pgm_read_word_near(melody + i);
    melodySort[i] = TONE_FREQ(oneTone);
  }
  sort(melodySort, melodyLen);
  
  int len = 0;
  unsigned int melodySort2[melodyLen];
  unsigned int last = 0;
  for (int i = 0 ; i < melodyLen ; i++) {
    if (last != melodySort[i]) {
      melodySort2[len] = melodySort[i];
      last = melodySort[i];
      len++;
    }
  }

  for (int i = 0 ; i < melodyLen ; i++) {
    for (int j = 0 ; j < len ; j++) {
      unsigned int oneTone = pgm_read_word_near(melody + i);
      if (melodySort2[j] == TONE_FREQ(oneTone)) {
        leds[i] = j;
        break;
      }
    }
  }
}

unsigned long melodySleep = 0;
int toneFreq = 0;
bool blinkLed = true;
void game3(unsigned long time) {  
  blinkLed = digitalRead(PIN_SWITCH_Y) == LOW;

  if (melody) {
    if (melodySleep) {
      if (time - lastTone > melodySleep) {
        melodySleep = 0;
        lastTone = time; 

        if (toneFreq > 0) {
          tone(PIN_PIEZO, toneFreq);

          if (blinkLed) {
            digitalWriteLed(leds[melodyPos], HIGH);
          }
        }
      } else {
        powerSave();
      }
    } else if (time - lastTone > toneLength) {
      int speed = analogRead(PIN_POTEN_L) * 1.5;
      int delayLength = toneLength / 3;

      unsigned int oneTone = pgm_read_word_near(melody + melodyPos);
      toneLength = speed / TONE_LEN(oneTone);
      toneFreq = TONE_FREQ(oneTone);
      lastTone = time;
      
      melodyPos++;
      if (melodyPos > melodyLen) {
        melody = 0;
      } else {
        melodySleep = delayLength + 1;
      }
      
      resetLed();
      noTone(PIN_PIEZO);
      TCCR3A = (1 << WGM30);
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
    } else {
      powerSave();
    }
  }
}
