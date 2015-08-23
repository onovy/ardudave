// Play 2 tones according to potenU with potenL speed

#include "pitches.h"

int tones[] = {
  NOTE_C3,
  NOTE_CS3,
  NOTE_D3,
  NOTE_DS3,
  NOTE_E3,
  NOTE_F3, 
  NOTE_FS3,
  NOTE_G3,
  NOTE_GS3,
  NOTE_A3,
  NOTE_AS3,
  NOTE_B3
};

unsigned long lastTime = 0;
bool plusOne = false;

void game1(unsigned long time) {
  int toneA = analogRead(pinPotenU);
  int speedA = analogRead(pinPotenL);

  int toneI = (int) ceil(toneA * (sizeof(tones) / sizeof(int) - 1) / 1024);
  
  if (time - lastTime > speedA / 2) {
    plusOne = !plusOne;
    lastTime = millis();
  }
  
  if (plusOne) {
    toneI++;
  }

  int toneF = tones[toneI];

  tone(pinPiezo, toneF);
}

