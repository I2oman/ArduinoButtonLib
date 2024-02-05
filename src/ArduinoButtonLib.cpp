#include "ArduinoButtonLib.h"

Button::Button(uint8_t pin) {
  if (pin > 0) {
    this->pin = pin;
  }
}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);
}

ClickType Button::getState() {bool btn = !digitalRead(pin);
  if (btn != btn_flag && millis() - anti_rattling >= 50) {
    btn_flag = btn;
    anti_rattling = millis();

    if (btn_flag) {
      previous_hold = millis();
    } else {
      clicks++;
    }
  }

  unsigned long hold_delta = millis() - previous_hold;
  if (hold_delta >= 300 || clicks > 1) {
    ClickType clickType = NO_CLICK;
    if (btn_flag == 0) {
      if (hold_delta <= 350 && clicks > 0) {
        clickType = (clicks == 1) ? CLICK : clickType;
        clickType = (clicks == 2) ? DOUBLE_CLICK : clickType;
      }
      clicks = 0;
    } else {
      clickType = (clicks == 0) ? HOLD : CLICK_AND_HOLD;
    }
    return clickType;
  }
  return NO_CLICK;
}

bool Button::click() {
  return getState() == CLICK;
}

bool Button::doubleClick() {
  return getState() == DOUBLE_CLICK;
}

bool Button::hold() {
  return getState() == HOLD;
}

bool Button::clickAndHold() {
  return getState() == CLICK_AND_HOLD;
}
