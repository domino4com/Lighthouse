#ifndef OLED_H
#define OLED_H

#include <U8g2lib.h>

#include "utils.h"

//.xbm files can be edited with FOSS https://www.gimp.org
#include "help.xbm"
#include "lighthouse.xbm"
#include "maine.xbm"

#define startl 17

class ODA {
 public:
  ODA();
  void begin();
  void drawlight(bool);

  void showData(long, float);
  void showError();
  void showInfinity(int);
  void showSplash();
  void showLighthouse();
  void showHelp();

  void sleep();
  int ok;

 private:
  void centerString(int, int, char *);
  void rightString(int, char *);
  int ll = startl;
  int oldll;
};

#endif