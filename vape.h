#ifndef __VAPE_H__
#define __VAPE_H__

#include "common.h"

class Vape {
  public:
    Vape(Mode mode);

    void setMode(Mode mode);

    float getTime();
    float getBattery();

    void setVolts(float volts);
    float getVolts();
    float incVolts();
    float decVolts();

    void setWatts(float watts);
    float getWatts();
    float incWatts();
    float decWatts();

    void setOhms(float ohms);
    float getOhms();

  private:
    Mode _mode;
    float _volts;
    float _watts;
    float _ohms;
    float _battery;

    long _time;

    void _update();
};

#endif //__VAPE_H__