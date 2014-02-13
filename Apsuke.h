#ifndef __APSUKE_H__
#define __APSUKE_H__

#include "common.h"

// Forward decls
class Joystick;
class Vape;
class UI;

class Apsuke {
  public:
    Apsuke(const int buttonCount, const int *buttonMapping, const int ssPin);

    Joystick *getJoystick();
    Vape *getVape();
    UI *getUI();

    void update();

  private:
    Mode _mode;
    Mode _prevMode;
    Joystick *_joy;
    Vape *_vape;
    UI *_ui;
    int _pwm;
    int _fire;
};

#endif //__APSUKE_H__