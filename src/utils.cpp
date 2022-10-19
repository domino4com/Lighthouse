#include "utils.h"

Utils::Utils() {}

bool Utils::found(uint8_t address) {
  Wire.beginTransmission(address);
  byte error = Wire.endTransmission();
  if (error == 0) return true;
  return false;
}

String Utils::wakeup() {
  esp_deep_sleep_enable_gpio_wakeup(0x08, ESP_GPIO_WAKEUP_GPIO_HIGH);

  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      return "Wakeup caused by external signal using RTC_IO";
    case ESP_SLEEP_WAKEUP_EXT1:
      return "Wakeup caused by external signal using RTC_CNTL";
    case ESP_SLEEP_WAKEUP_TIMER:
      return "Wakeup caused by timer";
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      return "Wakeup caused by touchpad";
    case ESP_SLEEP_WAKEUP_ULP:
      return "Wakeup caused by ULP program";
    default:
      char s[80];
      sprintf(s, "Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
      return String(s);
  }
}