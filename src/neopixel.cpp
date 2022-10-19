#include "neopixel.h"

Freenove_ESP32_WS2812 strip =
    Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

Neopixel::Neopixel() {}

void Neopixel::begin() {
  strip.begin();
  strip.setBrightness(10);
}

void Neopixel::sleep() { strip.setLedColor(0, 0, 0, 0); }

void Neopixel::setColor(char color) {
  switch (color) {
    case 'R':
      strip.setLedColor(0, 255, 0, 0);
      break;
    case 'G':
      strip.setLedColor(0, 0, 255, 0);
      break;
    case 'B':
      strip.setLedColor(0, 0, 0, 255);
      break;
  }
}

void Neopixel::lighthouse(bool onoff) {
  if (onoff) {
    if (goingdown) {
      rgblevel -= STEP;
      if (rgblevel <= 0) goingdown = false;
    } else {
      rgblevel += STEP;
      if (rgblevel >= 255) goingdown = true;
    }
  } else
    rgblevel = 0;

  strip.setLedColor(0, rgblevel, rgblevel, rgblevel);
}