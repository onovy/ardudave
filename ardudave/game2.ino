// Blink with LED by buttons/switches

bool blink = true;
unsigned long lastBlink = 0;
int color;

void game2(unsigned long time) {
  int brightness = analogRead(PIN_POTEN_L) / 4;
  int newColor = analogRead(PIN_POTEN_U);

  int diffC = color - newColor;
  if (abs(diffC) > 5) {
    color = newColor;
  }

  // Blink
  if (time - lastBlink > brightness) {
    lastBlink = time;
    blink = !blink;
  }

  // Set LEDs by button/switch states
  digitalWrite(PIN_LED_1, !digitalRead(PIN_BUTTON_W));
  digitalWrite(PIN_LED_2, digitalRead(PIN_SWITCH_Y) && blink);
  digitalWrite(PIN_LED_3, digitalRead(PIN_SWITCH_R) && !blink);
  digitalWrite(PIN_LED_4, !digitalRead(PIN_BUTTON_R));
  digitalWrite(PIN_LED_5, !digitalRead(PIN_BUTTON_G));
  digitalWrite(PIN_LED_6, !digitalRead(PIN_BUTTON_B));

  // Count RGB <0..1> from "color" <0.1024>
  int i = color;
  float rgbR = (float) i / 1000;
  i %= 100;
  float rgbG = (float) i / 100;
  i %= 10;
  float rgbB = (float) i / 10;

  if (rgbR > 1.00) {
    rgbR = 1.00;
  }
  if (rgbG > 1.00) {
    rgbG = 1.00;
  }
  if (rgbB > 1.00) {
    rgbB = 1.00;
  }

  if (digitalRead(PIN_SWITCH_S)) {
    analogWrite(PIN_LED_RGB_R, rgbR * brightness);
    analogWrite(PIN_LED_RGB_G, rgbG * brightness);
    analogWrite(PIN_LED_RGB_B, rgbB * brightness);
  } else {
    digitalWrite(PIN_LED_RGB_R, LOW);
    digitalWrite(PIN_LED_RGB_G, LOW);
    digitalWrite(PIN_LED_RGB_B, LOW);
  }
}

