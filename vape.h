#ifndef __VAPE_H__
#define __VAPE_H__

#include "common.h"

class Vape {
  public:
    Vape(Mode mode, int ssPin);

    void setMode(Mode mode);

    int getPWM();
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
    static const float _min_volts = 3.0;
    static const float _max_volts = 6.0;
    static const float _min_watts = 3.0;
    static const float _max_watts = 50.0;
    static const int _potTaps[][2];

    int _ssPin;
    Mode _mode;
    float _volts;
    float _watts;
    float _ohms;
    float _battery;

    long _time;

    void _setTrim();

    float _mapf(float x, float in_min, float in_max, float out_min, float out_max);
    void _update();
};

#endif //__VAPE_H__