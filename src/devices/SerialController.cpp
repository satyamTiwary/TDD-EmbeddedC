#pragma once
#include "base.h"
// Serial Controller is used by most files in this program and hence SHOULD NOT
// have any dependencies other than 'base.h'

// Implementation Details
uint32_t previous_time = 0; // variable holding previous time

// Interface
template <typename T>
inline void debug(const T &str = "", const bool newLine = true) {
  if (Constants::DEBUG) {
    if (newLine) {
      Serial.print("DEBUG: ");
      Serial.println(str);
    } else
      Serial.print(str);
  }
}

inline void transmit_poll(String func(),
                          const uint32_t loop_delay = Constants::DEBUG ? 3300
                                                                       : 33) {
  if (millis() - previous_time > loop_delay) {
    String temp = func();
    temp += ";";
    Serial.println(temp);
    previous_time = millis(); // Update Previous Time
  }
}

inline void transmit(const String &str) {
  if (str != " ") {
    String temp = str + ";";
    Serial.println(temp);
  } else {
    // debug("Transmition of empty string avoided.")
  }
}

template <typename T>
inline void error(const T &str = "", const bool newLine = true) {
  if (Constants::DEBUG) {
    if (newLine) {
      Serial.print("ERROR: ");
      Serial.println(str);
    } else
      Serial.print(str);
  }
}

void show_debug_screen() {
  debug("======================== DEBUG MODE =======================");
  debug("===========================================================");
  debug("MOVE_SLIDER_OUTWARDS         => ", false);
  debug(static_cast<int>(Command::MOVE_SLIDER_OUTWARDS));
  debug("MOVE_SLIDER_INWARDS          => ", false);
  debug(static_cast<int>(Command::MOVE_SLIDER_INWARDS));
  debug("STOP_SLIDER                  => ", false);
  debug(static_cast<int>(Command::STOP_SLIDER));
  debug("SEND_ACCELERO_DATA           => ", false);
  debug(static_cast<int>(Command::SEND_ACCELERO_DATA));
  debug("SEND_LDR_DATA                => ", false);
  debug(static_cast<int>(Command::SEND_LDR_DATA));
  debug("SET_DEBUG_TRUE               => ", false);
  debug(static_cast<int>(Command::SET_DEBUG_TRUE));
  debug("SET_DEBUG_FALSE              => ", false);
  debug(static_cast<int>(Command::SET_DEBUG_FALSE));
  debug("\nChange Current Mode: by Sending the Corresponding Number.");
  debug("===========================================================");
}

void SerialController() {
  Serial.begin(Constants::baudrate); // Initialize Serial Communication
}
