// Blink with LED by buttons/switches

bool blink = true;
unsigned long lastBlink = 0;

void game2(unsigned long time) {
  int brightness = analogRead(pinPotenL) / 4;
  int color = analogRead(pinPotenU);

  // Blink
  if (time - lastBlink > brightness) {
    lastBlink = time;
    blink = !blink;
  }

  // Set LEDs by button/switch states
  digitalWrite(pinLed1, !digitalRead(pinButtonW));
  digitalWrite(pinLed2, digitalRead(pinSwitchY) && blink);
  digitalWrite(pinLed3, digitalRead(pinSwitchR) && !blink);
  digitalWrite(pinLed4, !digitalRead(pinButtonR));
  digitalWrite(pinLed5, !digitalRead(pinButtonG));
  digitalWrite(pinLed6, !digitalRead(pinButtonB));

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

  analogWrite(pinLedRgbR, rgbR * brightness);
  analogWrite(pinLedRgbG, rgbG * brightness);
  analogWrite(pinLedRgbB, rgbB * brightness);
}

