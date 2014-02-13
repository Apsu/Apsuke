#include "Apsuke.h"
#include "joystick.h"
#include "vape.h"
#include "ui.h"

Apsuke::Apsuke(const int buttonCount, const int *buttonMapping, const int ssPin) {
  _mode = _prevMode = M_VW;
  _joy = new Joystick(buttonCount, buttonMapping);
  _vape = new Vape(_mode, ssPin);
  _ui = new UI(_mode);
  _fire = LOW;

  pinMode(12, OUTPUT);
  digitalWrite(12, _fire);
}

Joystick *Apsuke::getJoystick() {
  return _joy;
}

Vape *Apsuke::getVape() {
  return _vape;
}

UI *Apsuke::getUI() {
  return _ui;
}

void Apsuke::update() {
  _joy->update();
  int *states = _joy->getStates();

  if(states[B_CLICK] && _mode != M_FIRE) {
    _prevMode = _mode;
    _mode = M_FIRE;
    _vape->setMode(_mode);
    _ui->setMode(_mode);
    _fire = HIGH;
    digitalWrite(12, _fire);
  }
  else if(!states[B_CLICK] && _mode == M_FIRE) {
    _mode = _prevMode;
    _vape->setMode(_mode);
    _ui->setMode(_mode);
    _fire = LOW;
    digitalWrite(12, _fire);
  }

  switch(_mode) {
    case M_VW:
      if(states[B_UP]) _vape->incWatts();
      if(states[B_DOWN]) _vape->decWatts();
      if(states[B_LEFT] || states[B_RIGHT]) {
        _mode = M_VV;
        _vape->setMode(_mode);
        _ui->setMode(_mode);
      }
      break;
    case M_VV:
      if(states[B_UP]) _vape->incVolts();
      if(states[B_DOWN]) _vape->decVolts();
      if(states[B_LEFT] || states[B_RIGHT]) {
        _mode = M_VW;
        _vape->setMode(_mode);
        _ui->setMode(_mode);
      }
      break;
    }

  _ui->update(this);
}