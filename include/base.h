#ifdef BASE_H
#define BASE_H

namespace Constants {
bool DEBUG = true;
constexpr uint32_t baudrate = 115200;

/* Implementation Variables */
constexpr uint8_t freq_divider =
    16; // Should be divisor of 255 [AccelerometerController]
uint8_t position_to_micro_divider = 200; // MUST be a float
} // namespace Constants

enum class InstrumentState {
  SLIDER_INSIDE = 0,
  SLIDER_OUTSIDE,
  SLIDER_MOVING_INSIDE,
  SLIDER_MOVING_OUTSIDE,
  SLIDER_STOPPED,

  SLIDER_INSIDE_ACCELERO,
  SLIDER_INSIDE_LDR,
};

enum class Command {
  INVALID = 0,
  MOVE_SLIDER_OUTWARDS,
  MOVE_SLIDER_INWARDS,
  STOP_SLIDER,
  SEND_ACCELERO_DATA,
  SEND_LDR_DATA,
  SET_DEBUG_TRUE = 100, // Does not effect InstrumentState
  SET_DEBUG_FALSE       // Does not effect InstrumentState
};

enum class PIN {
  INTERRUPT_ENCODER1 = 4,
  INTERRUPT_ENCODER2 = 5,

  DO_MOTOR_ENABLE = 10,
  DO_MOTOR_STEP = 7,
  DO_MOTOR_DIRECTION = 6,
  INTERRUPT_LIMITSWITCH1 = 2,
  INTERRUPT_LIMITSWITCH2 = 3,

  ADC_LDR = 1,
  DO_INSTRUMENTLIGHTS = 9,
};

enum class I2C { ACCELEROMETER = 0x68 };
/* --- */

// State VARIABLES
namespace State {
auto instrumentState = InstrumentState::SLIDER_OUTSIDE;
}

// Signals
void OnDebugChanged();

#endif // BASE_H