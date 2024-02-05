#pragma once
#include <Arduino.h>

enum ClickType {
  CLICK,
  DOUBLE_CLICK,
  HOLD,
  CLICK_AND_HOLD,
  NO_CLICK
};

class Button {
public:
  Button(uint8_t pin = -1);
  void begin();
  ClickType getState();
  bool click();
  bool doubleClick();
  bool hold();
  bool clickAndHold();

private:
  uint8_t pin;
  bool btn_flag;
  unsigned long anti_rattling;
  unsigned long previous_hold;
  uint8_t clicks;
};
