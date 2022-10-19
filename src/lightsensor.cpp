#include "lightsensor.h"
LTR390 ltr390(ILB_ADDRESS);
Utils ILButils;

ILB::ILB() {}

void ILB::begin() {
  if (ILButils.found(ILB_ADDRESS)) {
    ltr390.init();
    ltr390.setMode(LTR390_MODE_ALS);
    ltr390.setGain(LTR390_GAIN_3);
    ltr390.setResolution(LTR390_RESOLUTION_18BIT);
    ok = true;
  } else {
    ok = false;
  }
  return;
}

bool ILB::get() {
  if (ltr390.newDataAvailable()) {
    if (ltr390.getMode() == LTR390_MODE_ALS) {
      lux = ltr390.getLux();
      // do something with lux
      ltr390.setGain(LTR390_GAIN_18);  // Recommended for UVI - x18
      ltr390.setResolution(
          LTR390_RESOLUTION_20BIT);  // Recommended for UVI - 20-bit
      ltr390.setMode(LTR390_MODE_UVS);
    } else if (ltr390.getMode() == LTR390_MODE_UVS) {
      uvi = ltr390.getUVI();
      // do something with uvi
      ltr390.setGain(LTR390_GAIN_3);  // Recommended for Lux - x3
      ltr390.setResolution(
          LTR390_RESOLUTION_16BIT);  // Recommended for Lux - 18-bit
      ltr390.setMode(LTR390_MODE_ALS);
    }
    return true;
  }
  return false;
}

void ILB::sleep(bool sleep) {
  uint8_t sleepReg = ltr390.readRegister(LTR390_MAIN_CTRL);
  if (sleep) {
    bitClear(sleepReg, 1);
  } else {
    bitSet(sleepReg, 1);
  }
  ltr390.writeRegister(LTR390_MAIN_CTRL, (uint8_t)sleepReg);
}