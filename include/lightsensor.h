#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <LTR390.h>
#include <Wire.h>
#include "utils.h"

#define ILB_ADDRESS 0x53

class ILB {
 public:
  ILB();
  void begin();
  bool get();
  void sleep(bool);
  long lux;
  float uvi;
  bool ok;
 private:

};

#endif