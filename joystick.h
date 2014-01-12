#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "common.h"

class Joystick {
  public:
    Joystick(const int num, const int pins[]);
    int* getStates();
    void update();

  private:
    int _numButtons; // button count
    int *_pins; // pin mappings
    int *_states; // the current states of the input pins
};

#endif //__JOYSTICK_H__