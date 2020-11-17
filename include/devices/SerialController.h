#ifdef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include "base.h"

// Interface
inline void transmit_poll(String func(),
                          const uint32_t loop_delay = Constants::DEBUG ? 3300
                                                                       : 33);

inline void transmit(const String &str);

template <typename T>
inline void debug(const T &str = "", const bool newLine = true);
template <typename T>
inline void error(const T &str = "", const bool newLine = true);

void show_debug_screen();
void SerialController();

#endif // SERIAL_CONTROLLER_H