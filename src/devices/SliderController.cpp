#pragma once
// #include "SerialController.h"
#include "CommandInterpretter.h"
#include "base.h"

#include <AccelStepper.h>
#include <TMC2208Stepper.h>

const uint8_t STEP = static_cast<uint8_t>(PIN::DO_MOTOR_STEP);
const uint8_t DIR = static_cast<uint8_t>(PIN::DO_MOTOR_DIRECTION);
const uint8_t ENABLE = static_cast<uint8_t>(PIN::DO_MOTOR_ENABLE);

TMC2208Stepper driver = TMC2208Stepper(&Serial);
AccelStepper stepper(1, STEP, DIR); // HARDCODED '1'

constexpr uint16_t MAXSPEED = 2000;
constexpr uint16_t ACCELERATION = 30000;
constexpr uint16_t LONG_DURATION = 800000UL;

constexpr uint8_t LM1 = static_cast<uint8_t>(PIN::INTERRUPT_LIMITSWITCH1);
constexpr uint8_t LM2 = static_cast<uint8_t>(PIN::INTERRUPT_LIMITSWITCH2);

int32_t _freespace = -1;

char find_state() {
  String temp = "L1, L2: ";
  temp += String(digitalRead(LM1));
  temp += " -> ";
  temp += String(digitalRead(LM2));
  debug(temp);

  if (digitalRead(LM1) && digitalRead(LM2)) // MIDDLE
    return 'm';
  else if (!digitalRead(LM1)) // BACKWARD
    return 'b';
  else if (!digitalRead(LM2)) // FORWARD
    return 'f';
}

void limitswitch_ISR() {
  if (_freespace >= 1000) {
    _freespace = -1;
    stop_slider();
    // ProcessInternalCommand(Command::STOP_SLIDER);
  }
}

inline void set_interrupts(bool enable = true) {
  if (enable) {
    attachInterrupt(digitalPinToInterrupt(LM1), limitswitch_ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(LM2), limitswitch_ISR, FALLING);
  } else {
    detachInterrupt(digitalPinToInterrupt(LM1));
    detachInterrupt(digitalPinToInterrupt(LM2));
  }
}

inline void SliderController() { // FULL OF HARDCODED PARAMETERS
  pinMode(ENABLE, OUTPUT);
  pinMode(STEP, OUTPUT);

  digitalWrite(ENABLE, HIGH);

  // driver.pdn_disable(1);      // Use PDN/UART pin for communication
  // driver.mstep_reg_select(1); // TRYING TO SET THE MICROSTEPS
  // driver.microsteps(0);       // TRYING TO SET THE MICROSTEPS
  // driver.I_scale_analog(0);   // Adjust current from the registers
  // driver.rms_current(500);    // Set driver current 500mA
  // driver.toff(0x2);           // Enable driver

  digitalWrite(ENABLE, LOW); // Enable driver

  stepper.setMaxSpeed(MAXSPEED);
  stepper.setAcceleration(ACCELERATION);

  set_interrupts(true);

  ProcessCommand(
      Command::MOVE_SLIDER_INWARDS); // Initial State of the Instrument
}

inline void move_outwards() {
  stepper.moveTo(-1L * LONG_DURATION);
  stepper.run();
  _freespace++;
}
inline void move_inwards() {
  stepper.moveTo(LONG_DURATION);
  stepper.run();
  _freespace++;
}
inline void stop_slider() { stepper.stop(); }
