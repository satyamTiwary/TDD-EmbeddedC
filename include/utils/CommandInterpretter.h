#ifdef COMMAND_INTERPRETTER_H
#define COMMAND_INTERPRETTER_H

#include "SerialController.h"
#include "SliderController.h"
#include "StateManagement.h"
#include "base.h"

inline void HandleIncommingCommands();
inline void ProcessInternalCommand(const Command &c);

#endif // COMMAND_INTERPRETTER_H