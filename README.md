Apsuke
===

Welcome to a first stab at a library for powering the Apsuke mod!

This is a work in progress, and probably unusable by most anyone but... here it is.

Requirements
---
- Adafruit GFX
- Adafruit SSD1306

Installation
---
Refer to the Arduino documentation for installing the library, but, basically it's just "copy the contents of this repo to the Arduino libraries directory, in a subdirectory named Apsuke".

Example
---

```
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Apsuke.h>

const int buttonCount = 5; // joystick buttons
const int buttonMapping[buttonCount] = {5,8,9,7,6}; // button -> pin mapping

Apsuke *apsuke;

void setup() {
    apsuke = new Apsuke(buttonCount, buttonMapping);
}

void loop() {
  apsuke->update();
}
```
