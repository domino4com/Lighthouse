#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <Wire.h>

class Utils {
 public:
  Utils();
  bool found(uint8_t);
  String wakeup();

 private:

};

#endif