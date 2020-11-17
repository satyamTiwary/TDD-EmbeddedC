#pragma once
#include "base.h"

constexpr uint8_t pin = static_cast<uint8_t>(PIN::DO_INSTRUMENTLIGHTS);

void InstrumentLightController() { pinMode(pin, OUTPUT); }

void set_lights(const bool enabled) {
  // switch on or off
  if (enabled) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}