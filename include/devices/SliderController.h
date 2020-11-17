#ifdef SLIDER_CONTROLLER_H
#define SLIDER_CONTROLLER_H

// #include "SerialController.h"
#include "CommandInterpretter.h"
#include "base.h"

char find_state();

void limitswitch_ISR();

inline void set_interrupts(bool enable = true);
inline void SliderController();

inline void move_outwards();
inline void move_inwards();
inline void stop_slider();

#endif // SLIDER_CONTROLLER_H