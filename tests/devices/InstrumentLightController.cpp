#include "CppUTest/TestHarness.h"

#include "InstrumentLightController.h"
// #include <arduino>
#include <iostream>

inline std::string ldr_serial_data() { return ""; }

TEST_GROUP(InstrumentLightController){};

TEST(InstrumentLightController, LightCanBeSetup) {
  CHECK(ldr_serial_data() == "");
}