#include "AccelerometerController.h"
#include <Wire.h>

// Implementation Details
constexpr uint16_t accelerometer_address = static_cast<int>(I2C::ACCELEROMETER);
constexpr uint8_t frequency_division = 16; // Should be a divisor of 255 ideally

uint8_t _i = 0; // Counter for frequency division
int16_t AcX, AcY, AcZ, Tmp;

// Interface
inline void AccelerometerController() {
  Wire.begin();
  Wire.beginTransmission(accelerometer_address);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
}

String accelerometer_serial_data() {
  Wire.beginTransmission(accelerometer_address);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(accelerometer_address, 14,
                   true); // request a total of 14 registers

  AcX = Wire.read() << 8 |
        Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 |
        Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 |
        Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)

  String temp = "";
  temp += "A:";
  temp += static_cast<String>(AcX);
  temp += ",";
  temp += static_cast<String>(AcY);
  temp += ",";
  temp += static_cast<String>(AcZ);

  /* Transmit Temperature Data */
  if (_i % frequency_division == 0) {
    temp += "T:"; // Data Identifier
    temp += Tmp;
  }

  _i++; // Update Division Counter

  return temp;
}
