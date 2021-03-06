// Play 2 tones according to potenU with potenL speed

#include "pitches.h"

int tones[] = {
  NOTE_C3,
  NOTE_D3,
  NOTE_E3,
  NOTE_F3, 
  NOTE_G3,
  NOTE_A3,
  NOTE_B3
};

unsigned long lastTime = 0;
bool plusOne = false;

void game1(unsigned long time) {
  int toneA = analogRead(PIN_POTEN_U);
  int speedA = analogRead(PIN_POTEN_L);

  int toneI = (int) ceil(toneA * (sizeof(tones) / sizeof(int) - 1) / 1024);
  
  if (time - lastTime > speedA / 2) {
    plusOne = !plusOne;
    lastTime = _millis();
  }
  
  if (plusOne) {
    toneI++;
  }

  int toneF = tones[toneI];

  tone(PIN_PIEZO, toneF);
  resetLed();
  digitalWriteLed(toneI, HIGH);
}

