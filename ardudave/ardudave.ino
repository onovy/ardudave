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

  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);
  pinMode(PIN_LED_6, OUTPUT);
  pinMode(PIN_LED_RGB_R, OUTPUT);
  pinMode(PIN_LED_RGB_G, OUTPUT);
  pinMode(PIN_LED_RGB_B, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_BUTTON_B, INPUT_PULLUP);
  pinMode(PIN_BUTTON_W, INPUT_PULLUP);
  pinMode(PIN_BUTTON_G, INPUT_PULLUP);
  pinMode(PIN_BUTTON_R, INPUT_PULLUP);
  pinMode(PIN_SWITCH_Y, INPUT_PULLUP);
  pinMode(PIN_SWITCH_R, INPUT_PULLUP);
  pinMode(PIN_SWITCH_S, INPUT_PULLUP);
  pinMode(PIN_POTEN_U, INPUT);
  pinMode(PIN_POTEN_L, INPUT);
  pinMode(PIN_IO, INPUT);

  game = eepromLoadGame();
  indicateGame(game);
}

void reset() {
  digitalWrite(PIN_LED_1, LOW);
  digitalWrite(PIN_LED_2, LOW);
  digitalWrite(PIN_LED_3, LOW);
  digitalWrite(PIN_LED_4, LOW);
  digitalWrite(PIN_LED_5, LOW);
  digitalWrite(PIN_LED_6, LOW);
  digitalWrite(PIN_LED_RGB_R, LOW);
  digitalWrite(PIN_LED_RGB_G, LOW);
  digitalWrite(PIN_LED_RGB_B, LOW);
  noTone(PIN_PIEZO);
}

void debug() {
  Serial.println("---------");

  Serial.print("ButtonR: ");
  Serial.println(digitalRead(PIN_BUTTON_R));

  Serial.print("ButtonG: ");
  Serial.println(digitalRead(PIN_BUTTON_G));

  Serial.print("ButtonB: ");
  Serial.println(digitalRead(PIN_BUTTON_B));

  Serial.print("ButtonW: ");
  Serial.println(digitalRead(PIN_BUTTON_W));

  Serial.print("Switch3: ");
  Serial.println(digitalRead(PIN_SWITCH_S));

  Serial.print("SwitchY: ");
  Serial.println(digitalRead(PIN_SWITCH_Y));

  Serial.print("SwitchR: ");
  Serial.println(digitalRead(PIN_SWITCH_R));

  Serial.print("PotenU: ");
  Serial.println(analogRead(PIN_POTEN_U));

  Serial.print("PotenL: ");
  Serial.println(analogRead(PIN_POTEN_L));
}

void indicateGame(byte game) {
  reset();
  
  switch (game) {
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
    case 7:
      digitalWrite(PIN_LED_RGB_R, HIGH);
      digitalWrite(PIN_LED_RGB_G, HIGH);
      digitalWrite(PIN_LED_RGB_B, HIGH);
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
  if (digitalRead(PIN_BUTTON_R) == LOW && digitalRead(PIN_BUTTON_W) == LOW) {
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

