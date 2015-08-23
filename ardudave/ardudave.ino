#include "pitches.h"
#include "pins.h"
#include <EEPROM.h>

byte game;
void eepromSaveGame(byte game) {
  Serial.println("EEPROM write");
  
  EEPROM.write(0, game);
}

byte eepromLoadGame() {
  return EEPROM.read(0);
}

void setup() {
  Serial.begin(9600); 

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
  pinMode(pinSwitchR, INPUT_PULLUP);
  pinMode(pinSwitch3, INPUT_PULLUP);
  pinMode(pinPotenU, INPUT);
  pinMode(pinPotenL, INPUT);
  pinMode(pinIO, INPUT);

  game = eepromLoadGame();
  indicateGame(game);
}

void reset() {
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);
  digitalWrite(pinLed4, LOW);
  digitalWrite(pinLed5, LOW);
  digitalWrite(pinLed6, LOW);
  digitalWrite(pinLedRgbR, LOW);
  digitalWrite(pinLedRgbG, LOW);
  digitalWrite(pinLedRgbB, LOW);
  noTone(pinPiezo);
}

void debug() {
  Serial.println("---------");

  Serial.print("ButtonR: ");
  Serial.println(digitalRead(pinButtonR));

  Serial.print("ButtonG: ");
  Serial.println(digitalRead(pinButtonG));

  Serial.print("ButtonB: ");
  Serial.println(digitalRead(pinButtonB));

  Serial.print("ButtonW: ");
  Serial.println(digitalRead(pinButtonW));

  Serial.print("Switch3: ");
  Serial.println(digitalRead(pinSwitch3));

  Serial.print("SwitchY: ");
  Serial.println(digitalRead(pinSwitchY));

  Serial.print("SwitchR: ");
  Serial.println(digitalRead(pinSwitchR));

  Serial.print("PotenU: ");
  Serial.println(analogRead(pinPotenU));

  Serial.print("PotenL: ");
  Serial.println(analogRead(pinPotenL));
}

void indicateGame(byte game) {
  reset();
  
  switch (game) {
    case 1:
      digitalWrite(pinLed1, HIGH);
    break;
    case 2:
      digitalWrite(pinLed2, HIGH);
    break;
    case 3:
      digitalWrite(pinLed3, HIGH);
    break;
    case 4:
      digitalWrite(pinLed4, HIGH);
    break;
    case 5:
      digitalWrite(pinLed5, HIGH);
    break;
    case 6:
      digitalWrite(pinLed6, HIGH);
    break;
    case 7:
      digitalWrite(pinLedRgbR, HIGH);
      digitalWrite(pinLedRgbG, HIGH);
      digitalWrite(pinLedRgbB, HIGH);
    break;
  }

  delay(500);

  reset();
}

unsigned long holdingFrom = 0;
byte games = 4;
void loop() {
  // debug();
  unsigned long time = millis();

  // Red and white button pressed together -> change game
  if (digitalRead(pinButtonR) == LOW && digitalRead(pinButtonW) == LOW) {
    if (!holdingFrom) {
      holdingFrom = time;
    }
    if (time - holdingFrom > 1000) {
      game++;
      if (game > games) {
        game = 1;
      }
      eepromSaveGame(game);
      indicateGame(game);
      holdingFrom = time;
    }

    return;
  } else {
    holdingFrom = 0;
  }

  switch (game) {
    case 1:
      game1(time);
    break;
    case 2:
      game2(time);
    break;
    case 3:
      game3(time);
    break;
    case 4:
      game4(time);
    break;
    default:
      game = 1;
    break;
  }
}

