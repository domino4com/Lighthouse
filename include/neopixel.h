#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#define NEOPIXEL 2

#include <Arduino.h>

#include "Freenove_WS2812_Lib_for_ESP32.h"
#define LEDS_COUNT  1
#define LEDS_PIN	NEOPIXEL
#define CHANNEL		0
#define STEP 10

class Neopixel {
 public:
  Neopixel();
  void begin();
  void sleep();
  void setColor(char);
  void lighthouse(bool);

 private:
int rgblevel = 0;
bool goingdown = false;
};

#endif