#include "joystick.h"

Joystick::Joystick(const int num, const int pins[]) {
  _numButtons = num;
  _pins = new int[num];
  _states = new int[num];

  for(int i = 0; i < num; i++) {
    pinMode(pins[i], INPUT_PULLUP); // set pin modes to INPUT
    _pins[i] = pins[i];
    _states[i] = LOW;
  }
}

void Joystick::update() {
  for(int i = 0; i < _numButtons; i++) {
    _states[i] = !digitalRead(_pins[i]);
  }
}

int* Joystick::getStates() {
  return _states;
}