#include "base.h"

inline String ldr_serial_data() {
  String temp = "";
  temp += "L:";
  temp += analogRead(static_cast<uint32_t>(PIN::ADC_LDR));
  return temp;
}
