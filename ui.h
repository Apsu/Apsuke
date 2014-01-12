#ifndef __UI_H__
#define __UI_H__

#include "common.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4 // OLED reset pin

#if (SSD1306_LCDHEIGHT != 32)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Forward decls
class Apsuke;
class Joystick;
class Vape;

class UI {
  public:
    UI(Mode mode);
    void setContrast(Contrast contrast);
    int getContrast();

    void setCursor(int x, int y);
    void setTextSize(TextSize textSize);
    void setTextColor(int fgColor, int bgColor);

    void startScroll(Scroll dir);
    void stopScroll();

    void clear();
    void reset();
    void put(char *buf);
    void print(char *buf);

    void setMode(Mode mode);
    Mode getMode();
    void update(Apsuke *apsuke);

  private:
    Mode _mode;
    Adafruit_SSD1306 _display;
    int _textSize;
    int _fgColor;
    int _bgColor;
    int _contrast;

    void _show();
};

#endif //__UI_H__