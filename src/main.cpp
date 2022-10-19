#include "main.h"

void IRAM_ATTR checkTicks() { button.tick(); }

void sleepClick() {
  led.sleep();             // Turn LED off
  oda.sleep();             // Turn OLED off
  ilb.sleep(true);         // Turn Light Sensor Off
}

void powerOff() {
  esp_deep_sleep_start();  // Turn MCU off
}

void runforeverClick() {
  runForever = !runForever;
}

void helpClick() {
  helpWanted = !helpWanted;
  if (helpWanted) {
    oda.showHelp();
    led.setColor('G');
  } else {
    oda.showLighthouse();
  }
}

void setup() {
  led.begin();
  led.setColor('B');

  attachInterrupt(digitalPinToInterrupt(BUTTON), checkTicks, CHANGE);
  button.attachClick(helpClick);
  button.attachDoubleClick(runforeverClick);
  button.setPressTicks(LONGPRESS*1000);
  button.attachLongPressStart(sleepClick);
  button.attachLongPressStop(powerOff);

  // I2C
  Wire.setPins(I2C_SDA, I2C_SCL);
  Wire.begin();

  // OLED
  oda.begin();
  if (!oda.ok) {
    led.setColor('R');
  }
  oda.showSplash();
  oda.showLighthouse();

  // Wake Up - make sure the it wakes up again.
    utils.wakeup();

  // Light Sensor
  ilb.begin();
  if (!ilb.ok) {
    oda.showError();
    led.setColor('R');
  }
}

void loop() {
  button.tick();
  if (helpWanted) return;

  if (ilb.ok) {
    if (ilb.get()) {
      oda.showData(ilb.lux, ilb.uvi);
    }
  } else {
    oda.showError();
    ledlighton = false;
    led.setColor('R');
  }

  led.lighthouse(ledlighton);

  if (ilb.lux > LUXLEVEL) {
    ledlighton = false;
    oda.drawlight(false);
  } else {
    ledlighton = true;
    oda.drawlight(true);
  }

  int infinity;
  if (runForever) {
    infinity = 187; // Infinity symbol
  } else {
    infinity = 217; // A solid square to print over the Infinity symbol
    if (millis() > RUNTIME*1000) {
      sleepClick();
      powerOff();
    }
  }
  oda.showInfinity(infinity);
}
