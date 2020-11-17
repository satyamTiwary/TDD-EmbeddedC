#pragma once
#include "SerialController.h"
#include "SliderController.h"
#include "StateManagement.h"
#include "base.h"

// ProcessCommand should not be used by other files directly
inline void ProcessCommand(const Command &c) {
  // Handle Interrupt Variable Changes
  // debug(static_cast<int>(c));
  switch (c) {
  case Command::MOVE_SLIDER_OUTWARDS:
    changeInstrumentState(State::instrumentState,
                          InstrumentState::SLIDER_OUTSIDE);
    move_outwards(); // debug("MOVE_SLIDER_OUTWARDS");
    break;
  case Command::MOVE_SLIDER_INWARDS:
    changeInstrumentState(State::instrumentState,
                          InstrumentState::SLIDER_INSIDE);
    move_inwards(); // debug("MOVE_SLIDER_INWARDS");
    break;
  case Command::STOP_SLIDER:
    changeInstrumentState(State::instrumentState,
                          InstrumentState::SLIDER_STOPPED);
    stop_slider(); // debug("STOP_SLIDER");
    break;
  case Command::SEND_ACCELERO_DATA:
    changeInstrumentState(State::instrumentState,
                          InstrumentState::SLIDER_INSIDE_ACCELERO);
    break;
  case Command::SEND_LDR_DATA:
    changeInstrumentState(State::instrumentState,
                          InstrumentState::SLIDER_INSIDE_LDR);
    break;
  case Command::SET_DEBUG_TRUE:
    Constants::DEBUG = true;
    break;
  case Command::SET_DEBUG_FALSE:
    Constants::DEBUG = false;
    break;
  default:
    break;
  }
}

inline void HandleIncommingCommands() {
  if (Serial.available()) { // Poll and Process Incoming Commands
    ProcessCommand(static_cast<Command>(Serial.parseInt()));
    if (Constants::DEBUG)
      delay(1000); // HARDCODED DELAY
  }
}

inline void ProcessInternalCommand(const Command &c) {
  ProcessCommand(c);
} // a Pass through Function
