#include "DistanceController.h"

// Implementation Details
int16_t _old_micron = 0;
Encoder KnobEncoder(static_cast<uint8_t>(PIN::INTERRUPT_ENCODER1),
                    static_cast<uint8_t>(PIN::INTERRUPT_ENCODER2));
inline int16_t getRawPosition() { return KnobEncoder.read(); }
inline int16_t getMicron() {
  return (getRawPosition() /
          static_cast<int16_t>(Constants::position_to_micro_divider));
}

// Interface
inline void DistanceController() {}
inline int16_t distance_data() { return getMicron(); }
inline String distance_serial_data() {
  int16_t new_micron = getMicron();
  if (new_micron != _old_micron) {
    String temp = "D:" + String(new_micron); // This is particular to arduino:
                                             // Call the String Constructor
    _old_micron = new_micron;
    return temp;
  } else {
    return " ";
  }
}

inline void clear_distance() { _old_micron = 0; }
