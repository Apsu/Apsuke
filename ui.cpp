#include "Apsuke.h"
#include "ui.h"
#include "joystick.h"
#include "vape.h"

UI::UI(Mode mode) : _display(OLED_RESET) {
  setMode(mode);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  _display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)
  clear();
}

void UI::setMode(Mode mode) {
  _mode = mode;
}

Mode UI::getMode() {
  return _mode;
}

void UI::update(Apsuke *apsuke) {
  Joystick *joy = apsuke->getJoystick();
  Vape *vape = apsuke->getVape();
  char buf[100];
  String tmp;

  switch(_mode) {
    case M_SPLASH:
      reset();
      setTextSize(T_LARGE);
      setTextColor(WHITE, BLACK);
      setContrast(C_MAX);
      print("Apsuke 1.0");
      startScroll(S_DIAGLEFT);
      delay(3000);
      clear();
      stopScroll();
      _mode = M_VW;
      break;
    case M_VW:
      reset();
      setTextSize(T_SMALL);
      setTextColor(WHITE, BLACK);
      setContrast(C_MAX);

      put("VW");
      tmp = String(vape->getBattery(), 0) + "%";
      tmp.toCharArray(buf, 100);
      setCursor(128 - (strlen(buf)*6), 0);
      put(buf);


      tmp = String(vape->getVolts(), 1) + "V\n" + String(vape->getOhms(), 1) + "\xE9";
      tmp.toCharArray(buf, 100);
      setCursor(0, 17);
      put(buf);

      setTextSize(T_LARGE);
      tmp = String(vape->getWatts(), 1) + "W";
      tmp.toCharArray(buf, 100);
      setCursor(128 - (strlen(buf)*12), 18);
      print(buf);

      break;
    case M_VV:
      reset();
      setTextSize(T_SMALL);
      setTextColor(WHITE, BLACK);
      setContrast(C_MAX);

      put("VV");
      tmp = String(vape->getBattery(), 0) + "%";
      tmp.toCharArray(buf, 100);
      setCursor(128 - (strlen(buf)*6), 0);
      put(buf);

      tmp = String(vape->getWatts(), 1) + "W\n" + String(vape->getOhms(), 1) + "\xE9";
      tmp.toCharArray(buf, 100);
      setCursor(0, 17);
      put(buf);

      setTextSize(T_LARGE);
      tmp = String(vape->getVolts(), 1) + "V";
      tmp.toCharArray(buf, 100);
      setCursor(128 - (strlen(buf)*12), 18);
      print(buf);

      break;
    case M_FIRE:
      reset();
      setTextSize(T_LARGE);
      setTextColor(WHITE, BLACK);
      setContrast(C_MIN);

      tmp = String(vape->getTime(), 1) + "s";
      tmp.toCharArray(buf, 100);
      setCursor(46, 9); // Left-aligned center
      print(buf);

      break;
    case M_DIAG:
      joy->update();
      int *states = joy->getStates();
      int contrast = getContrast();
      sprintf(buf, "Up: %d, Down: %d\nLeft: %d, Right: %d\nClick: %d\nContrast: %s", states[B_UP], states[B_DOWN], states[B_LEFT], states[B_RIGHT], states[B_CLICK], !contrast ? "Min" : "Max");
      reset();
      setTextSize(T_SMALL);
      setTextColor(WHITE, BLACK);
      setContrast(C_MAX);
      print(buf);
      if(states[B_CLICK]) {
        _mode = M_SPLASH;
      }
      break;
  }
}

void UI::setContrast(Contrast contrast) {
  _contrast = contrast;
  _display.ssd1306_command(SSD1306_SETCONTRAST);
  _display.ssd1306_command(contrast);
}

int UI::getContrast() {
  return _contrast;
}

void UI::setCursor(int x, int y) {
  _display.setCursor(x, y);
}

void UI::setTextSize(TextSize textSize) {
   _textSize = textSize;
   _display.setTextSize(textSize);
}

void UI::setTextColor(int fgColor, int bgColor) {
  _fgColor = fgColor;
  _bgColor = bgColor;
  _display.setTextColor(_fgColor, _bgColor);
}

void UI::startScroll(Scroll dir) {
  switch(dir) {
    case S_LEFT:
      _display.startscrollleft(0x00, 0x0F);
      break;
    case S_RIGHT:
      _display.startscrollright(0x00, 0x0F);
      break;
    case S_DIAGLEFT:
      _display.startscrolldiagleft(0x00, 0x07);
      break;
    case S_DIAGRIGHT:
      _display.startscrolldiagright(0x00, 0x07);
      break;
  }
}

void UI::stopScroll() {
  _display.stopscroll();
}

void UI::clear() {
  _display.clearDisplay();
}

void UI::reset() {
  clear();
  setCursor(0, 0);
  stopScroll();
}

void UI::_show() {
  _display.display();
}

void UI::put(char *buf) {
   _display.print(buf);
}

void UI::print(char *buf) {
  put(buf);
  _show();
}