#include "pitches.h"
#include "pins.h"
#include <EEPROM.h>
#include <avr/sleep.h>

unsigned long lastAction;
// Auto sleep after 3 minutes
#define SLEEP_AFTER_MILIS 180000

void wakeupInterrupt() {
  detachInterrupt(1);
  detachInterrupt(2);
  detachInterrupt(3);
}

void sleep() {
  Serial.println("Sleeping");
  reset();

  attachInterrupt(1, wakeupInterrupt, LOW);
  attachInterrupt(2, wakeupInterrupt, LOW);
  attachInterrupt(3, wakeupInterrupt, LOW);

  delay(100);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable(); 

  lastAction = millis();
}

byte game;
void eepromSaveGame(byte game) {
  Serial.println("EEPROM write");
  
  EEPROM.write(0, game);
}

byte eepromLoadGame() {
  return EEPROM.read(0);
}

void setup() {
  lastAction = millis();
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

  Serial.print(F("Last action: "));
  Serial.println(lastAction);

  Serial.print(F("ButtonR: "));
  Serial.println(digitalRead(PIN_BUTTON_R));

  Serial.print(F("ButtonG: "));
  Serial.println(digitalRead(PIN_BUTTON_G));

  Serial.print(F("ButtonB: "));
  Serial.println(digitalRead(PIN_BUTTON_B));

  Serial.print(F("ButtonW: "));
  Serial.println(digitalRead(PIN_BUTTON_W));

  Serial.print(F("Switch3: "));
  Serial.println(digitalRead(PIN_SWITCH_S));

  Serial.print(F("SwitchY: "));
  Serial.println(digitalRead(PIN_SWITCH_Y));

  Serial.print(F("SwitchR: "));
  Serial.println(digitalRead(PIN_SWITCH_R));

  Serial.print(F("PotenU: "));
  Serial.println(analogRead(PIN_POTEN_U));

  Serial.print(F("PotenL: "));
  Serial.println(analogRead(PIN_POTEN_L));

  delay(200);
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
bool stateDigital[7];
int stateAnalog[2];
void loop() {
  // debug();
  unsigned long time = millis();

  // Auto sleep Arduino after specified time
  if (time - lastAction > SLEEP_AFTER_MILIS) {
    sleep();
  }
  if (stateDigital[0] != digitalRead(PIN_BUTTON_W)) {
    stateDigital[0] = !stateDigital[0];
    lastAction = time;
  }
  if (stateDigital[1] != digitalRead(PIN_BUTTON_B)) {
    stateDigital[1] = !stateDigital[1];
    lastAction = time;
  }
  if (stateDigital[2] != digitalRead(PIN_BUTTON_G)) {
    stateDigital[2] = !stateDigital[2];
    lastAction = time;
  }
  if (stateDigital[3] != digitalRead(PIN_BUTTON_R)) {
    stateDigital[3] = !stateDigital[3];
    lastAction = time;
  }
  if (stateDigital[4] != digitalRead(PIN_SWITCH_R)) {
    stateDigital[4] = !stateDigital[4];
    lastAction = time;
  }
  if (stateDigital[5] != digitalRead(PIN_SWITCH_Y)) {
    stateDigital[5] = !stateDigital[5];
    lastAction = time;
  }
  if (stateDigital[6] != digitalRead(PIN_SWITCH_S)) {
    stateDigital[6] = !stateDigital[6];
    lastAction = time;
  }
  int diffU = stateAnalog[0] - analogRead(PIN_POTEN_U);
  if (abs(diffU) > 5) {
    stateAnalog[0] = analogRead(PIN_POTEN_U);
    lastAction = time;
  }
  int diffL = stateAnalog[1] - analogRead(PIN_POTEN_L);
  if (abs(diffL) > 5) {
    stateAnalog[1] = analogRead(PIN_POTEN_L);
    lastAction = time;
  }
  
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

