#include "AccelerometerController.h"
#include "CommandInterpretter.h"
#include "DisplayController.h"
#include "SerialController.h"
#include "SliderController.h"
#include "StateManagement.h"
#include "base.h"

void setup() {
  SerialController();        // Initialize Serial Communication
  SliderController();        // Initialize Slider
  AccelerometerController(); // Initialize Accelerometer
  DisplayController();       // Initialize Display
  DistanceController();      // Initialize DistanceController
  show_debug_screen();       // debug screen should be called LAST
}

void loop() {
  HandleIncommingCommands();
  ActAccordingToState(State::instrumentState);
}
