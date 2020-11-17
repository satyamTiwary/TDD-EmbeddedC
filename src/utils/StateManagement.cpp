#pragma once
#include "base.h"
// Include all Functions that get sensor data
// and function to trnasmit Serial data
// Functions to enable and disable interrupts
#include "AccelerometerController.h"
#include "DisplayController.h"
#include "DistanceController.h"
#include "InstrumentLightController.h"
#include "LdrController.h"
#include "SerialController.h"
#include "SliderController.h"

inline void ActAccordingToState(const InstrumentState s) {
  switch (s) {
  case InstrumentState::SLIDER_INSIDE:
  case InstrumentState::SLIDER_INSIDE_ACCELERO: // Waiting for Command to move
                                                // Inside or Outside
    transmit_poll(accelerometer_serial_data);   // Transmit Accelerometer Data
    break;
  case InstrumentState::SLIDER_INSIDE_LDR:
    transmit_poll(ldr_serial_data); // Transmit LDR Data
    break;
  case InstrumentState::SLIDER_OUTSIDE: // Waiting for Command to move slider
                                        // Inside or Outside
    display_distance();
    transmit(distance_serial_data()); // Transmit & Display Data (on Oled)
    break;
  case InstrumentState::SLIDER_MOVING_INSIDE:
    // Waiting for Either Limit Switches or Encoders
    break;
  case InstrumentState::SLIDER_MOVING_OUTSIDE:
    // Waiting for Either Limit Switches or Encoders
    break;
  default:
    break;
  }
}

inline void changeInstrumentState(InstrumentState &s,
                                  const InstrumentState new_s) {
  debug("changeInstrumentState");
  switch (new_s) {
  case InstrumentState::SLIDER_INSIDE:
    s = InstrumentState::SLIDER_INSIDE_ACCELERO; // Set InstrumentSate to
                                                 // SLIDER_INSIDE_ACCELERO
    set_lights(false);                           // Switch Lights OFF
    clear_display();                             // Switch off the oled display
    break;
  case InstrumentState::SLIDER_INSIDE_ACCELERO:
    // No transition Steps
    break;
  case InstrumentState::SLIDER_INSIDE_LDR:
    // No transition Steps
    break;
  case InstrumentState::SLIDER_OUTSIDE:
    // Disable Limit Switch Interrupts
    set_lights(true); // Switch Lights ON
    break;
  case InstrumentState::SLIDER_MOVING_INSIDE:
    // No transition Steps
    break;
  case InstrumentState::SLIDER_MOVING_OUTSIDE:
    // No transition Steps
    break;
  default: // ERROR
    error("State action MUST NOT be DEFAULT.");
    break;
  }
  s = new_s;
}