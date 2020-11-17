#ifdef STATE_MANAGEMENT_H
#define STATE_MANAGEMENT_H

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

inline void ActAccordingToState(const InstrumentState);
inline void changeInstrumentState(InstrumentState &, const InstrumentState);

#endif // STATE_MANAGEMENT_H