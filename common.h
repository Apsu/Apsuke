#ifndef __COMMON_H__
#define __COMMON_H__

#include <Arduino.h>

enum Scroll {
  S_LEFT,
  S_RIGHT,
  S_DIAGRIGHT,
  S_DIAGLEFT
};

enum Button {
  B_UP,
  B_DOWN,
  B_LEFT,
  B_RIGHT,
  B_CLICK
};

enum Mode {
  M_SPLASH,
  M_VW,
  M_VV,
  M_FIRE,
  M_DIAG
};

enum Contrast {
  C_MIN=0,
  C_MAX=255
};

enum TextSize {
  T_SMALL=1,
  T_LARGE=2
};

#endif //__COMMON_H__