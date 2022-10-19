#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

#ifdef D4_CORE_CWB
#define D4_CORE "CWB"
#define SPI_CLASS FSPI
#define SPI_MISO 8
#define SPI_MOSI 7
#define SPI_SCK 10
#define SPI_CS_SD 4
#define I2C_SDA 5
#define I2C_SCL 6
#define BUTTON 3
#endif

#include <Wire.h>

#include "oled.h"
ODA oda;

#include "lightsensor.h"
ILB ilb;

#include "utils.h"
Utils utils;

#include "neopixel.h"
Neopixel led;

#include "OneButton.h"
OneButton button(BUTTON, false);

bool ledlighton = false;
bool runForever = false;
bool helpWanted = false;

#endif