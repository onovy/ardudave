// Blink with LED by buttons/switches

bool blink = true;
unsigned long lastBlink = 0;

void game2(unsigned long time) {
  int brightness = analogRead(PIN_POTEN_L) / 4;
  int color = analogRead(PIN_POTEN_U);

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
  float rgbR = (float) color / 1000;
  color %= 100;
  float rgbG = (float) color / 100;
  color %= 10;
  float rgbB = (float) color / 10;

  if (rgbR > 1.00) {
    rgbR = 1.00;
  }
  if (rgbG > 1.00) {
    rgbG = 1.00;
  }
  if (rgbB > 1.00) {
    rgbB = 1.00;
  }

  analogWrite(PIN_LED_RGB_R, rgbR * brightness);
  analogWrite(PIN_LED_RGB_G, rgbG * brightness);
  analogWrite(PIN_LED_RGB_B, rgbB * brightness);
}

