#include "vape.h"

Vape::Vape(Mode mode) {
  _mode = mode;
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
}

float Vape::getTime() {
  return float(millis() - _time) / 1000.0;
}

float Vape::getBattery() {
  return _battery;
}

void Vape::setVolts(float volts) {
  _volts = volts;
  _update();
}

float Vape::getVolts() {
  return _volts;
}

float Vape::incVolts() {
  _volts = min(_volts + 0.1, 6.0);
  _update();
  return _volts;
}

float Vape::decVolts() {
  _volts = max(_volts - 0.1, 3.0);
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
  _watts = min(_watts + 0.5, 50.0);
  _update();
  return _watts;
}

float Vape::decWatts() {
  _watts = max(_watts - 0.5, 3.0);
  _update();
  return _watts;
}