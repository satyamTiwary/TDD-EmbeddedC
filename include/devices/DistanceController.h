#ifdef DISTANCE_CONTROLLER_H
#define DISTANCE_CONTROLLER_H

#include "base.h"
#include <Encoder.h>

// Interface
inline void DistanceController();
inline int16_t distance_data();
inline String distance_serial_data();

inline void clear_distance();

#endif // DISTANCE_CONTROLLER_H