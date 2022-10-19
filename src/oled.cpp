
#include "oled.h"

Utils ODAutils;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

ODA::ODA() { ok = false; }

void ODA::begin() {
  if (!ODAutils.found(0x3C)) {
    ok = false;
  } else {
    ok = true;
    u8g2.begin();
    u8g2.setBusClock(400000);
    u8g2.setFontPosTop();
  }
  oldll = 0;
}

void ODA::centerString(int x, int y, char *s) {
  int w = u8g2.getStrWidth(s);
  int z = (((128 - x) - w) / 2) + x;
  u8g2.drawStr(z, y, s);
}
void ODA::rightString(int y, char *s) {
  int x = 128 - u8g2.getStrWidth(s);
  u8g2.drawStr(x, y, s);
}

void ODA::drawlight(bool onoff) {
  if (!onoff) {
    oldll = ll;
    // oda.drawlight(false);
    // ledlighton = false;
  } else {
    // ledlighton = true;
    oldll = ll;
    ll = ll + 5;
    if (ll > 127 - startl) ll = startl;
    // oda.drawlight(true);
  }

  if (ok) {
    u8g2.setDrawColor(0);
    for (int i = 1; i < 16; i = i + 2) {
      u8g2.drawLine(startl, 11, oldll, i);
    }
    if (onoff) {
      u8g2.setDrawColor(1);
      for (int i = 1; i < 16; i = i + 2) {
        u8g2.drawLine(startl, 11, ll, i);
      }
    }
    u8g2.sendBuffer();
  }
}

void ODA::showData(long lux, float uvi) {
  if (ok) {
    char b[20];

// Clear area with measurement. Faster than clearing the whole screen and the draw it all over again.
    u8g2.setDrawColor(0);
    u8g2.drawBox(32, 32, 128 - 32, 52 - 32);
    u8g2.drawBox(65, 54, 128 - 70, 64 - 54);

    u8g2.setDrawColor(1);

// Show Lux measurement
    u8g2.setFont(u8g2_font_luBS19_tn);
    sprintf(b, "%ld", lux);
    rightString(32, b);

// Show UVI measurement
    u8g2.setFont(u8g2_font_luBS08_tn);
    sprintf(b, "%f", uvi);
    rightString(54, b);

    u8g2.sendBuffer();
  }
}

void ODA::showError() {
  if (ok) {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_VCR_OSD_mu);
    centerString(0, 0, (char *)"ERROR");
    centerString(0, 16, (char *)"NO");
    centerString(0, 32, (char *)"LIGHT");
    centerString(0, 48, (char *)"SENSOR");
    u8g2.sendBuffer();
  }
}

void ODA::showInfinity(int i) {
  if (ok) {
    char c[2] = {0, 0};
    c[0] = i;
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
    u8g2.drawStr(5, 23, c);
    u8g2.sendBuffer();
  }
}

void ODA::showSplash() {
  if (ok) {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.drawXBMP(4, 0, maine_width, maine_height, maine_bits);
    u8g2.setFont(u8g2_font_VCR_OSD_mu);
    centerString(40, 0, (char *)"MAINE");
    centerString(40, 16, (char *)"SPACE");
    centerString(40, 32, (char *)"STEM");
    centerString(40, 48, (char *)"PROGRAM");
    u8g2.sendBuffer();
    delay(SPLASHSCREEN * 1000);
  }
}

void ODA::showHelp() {
#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))
  char *s[] = {"1 Press: ",       "   Help On-Off", "2 Press:",
               "   Run Non-Stop", "Long Press:",    "   Power Off"};
  if (ok) {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.drawXBMP(77, 16, help_width, help_height, help_bits);
    u8g2.setFont(u8g2_font_VCR_OSD_mu);
    u8g2.drawStr(2, 0, "HELP");
    u8g2.setFont(u8g2_font_nokiafc22_tf);
    u8g2.drawStr(54, 0, "Lighthouse App");
    u8g2.drawStr(61, 8, "2022");
    u8g2.drawStr(88, 8, GIT_VERSION);
    u8g2.setFont(u8g2_font_8x13_t_symbols);
    char c[2] = {169, 0};  // Copyright Symbol
    u8g2.drawStr(53, 7, c);

    u8g2.setFont(u8g2_font_NokiaSmallPlain_te);
    for (int i = 0; i < ELEMENTS(s); i++) {
      u8g2.drawStr(2, i * 8 + 16, s[i]);
    }
    u8g2.sendBuffer();
  }
}

void ODA::showLighthouse() {
  if (ok) {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.drawXBMP(0, 0, lighthouse_width, lighthouse_height, lighthouse_bits);
    u8g2.setFont(u8g2_font_luBS12_tf);
    u8g2.drawStr(32, 16, "Lux:");
    u8g2.drawLine(32, 53, 127, 53);
    u8g2.setFont(u8g2_font_luBS08_tf);
    u8g2.drawStr(32, 54, "UVI:");
    u8g2.sendBuffer();
  }
}

void ODA::sleep() {
  if (ok) {
    u8g2.setPowerSave(true);
  }
}