#include "vape.h"
#include <SPI.h>

const int Vape::_potTaps[][2] = {
  {12, 189},
  {12, 107},
  {11, 167},
  {11, 98},
  {10, 187},
  {10, 104},
  {10, 72},
  {9, 140},
  {9, 87},
  {9, 63},
  {8, 151},
  {8, 90},
  {8, 64},
  {8, 50},
  {7, 139},
  {7, 84},
  {7, 60},
  {7, 47},
  {7, 38},
  {6, 134},
  {6, 81},
  {6, 58},
  {6, 45},
  {6, 37},
  {6, 31},
  {5, 211},
  {5, 100},
  {5, 65},
  {5, 49},
  {5, 39},
  {5, 32}
};

Vape::Vape(Mode mode, int ssPin) {
  pinMode(_ssPin, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST); // MSB first
  SPI.setDataMode(SPI_MODE0); // Clock rising-edge/idle-low

  _mode = mode;
  _ssPin = ssPin;
  _volts = 3.0;
  _watts = 4.5;
  _ohms = 2.0;
  _battery = 3.7;
  _update();
}

void Vape::setMode(Mode mode) {
  _mode = mode;
  _update();
}

void Vape::_setTrim() {
  const int *taps = _potTaps[int((_volts - 3.0) * 10)];

  digitalWrite(_ssPin, LOW);
  SPI.transfer(0);
  SPI.transfer(taps[0]);
  digitalWrite(_ssPin, HIGH);
  delay(20);
  digitalWrite(_ssPin, LOW);
  SPI.transfer(1);
  SPI.transfer(taps[1]);
  digitalWrite(_ssPin, HIGH);
  delay(20);
}

void Vape::_update() {
  switch(_mode) {
    case M_VW:
      _volts = sqrt(_watts * _ohms);
      break;
    case M_VV:
      _watts = square(_volts) / _ohms;
      break;
    case M_FIRE:
      _time = millis();
      break;
  }

  _setTrim();
}

float Vape::_mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Vape::getPWM() {
  return _mapf(_volts, _min_volts, _max_volts, 0, 255);
}

float Vape::getTime() {
  return float(millis() - _time) / 1000.0;
}

float Vape::getBattery() {
  return _battery / 4.2 * 100.0;
}

void Vape::setVolts(float volts) {
  _volts = volts;
  _update();
}

float Vape::getVolts() {
  return _volts;
}

float Vape::incVolts() {
  _volts = min(_volts + 0.1, _max_volts);
  _update();
  return _volts;
}

float Vape::decVolts() {
  _volts = max(_volts - 0.1, _min_volts);
  _update();
  return _volts;
}

void Vape::setOhms(float ohms) {
  _ohms = ohms;
  _update();
}

float Vape::getOhms() {
  return _ohms;
}

void Vape::setWatts(float watts) {
  _watts = watts;
  _update();
}

float Vape::getWatts() {
  return _watts;
}

float Vape::incWatts() {
  _watts = min(_watts + 0.1, _max_watts);
  _update();
  return _watts;
}

float Vape::decWatts() {
  _watts = max(_watts - 0.1, _min_watts);
  _update();
  return _watts;
}
