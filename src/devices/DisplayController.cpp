#include "DisplayController.h"

// Implementation Details
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); // <- do not bother
inline void util_draw_um(int32_t position) {
  u8g2.setFont(u8g2_font_10x20_t_greek); // HARD CODED
  int32_t n = position;
  uint8_t _digit_count = 0;
  while (n != 0) {
    n /= 10;
    ++_digit_count;
  }
  if (_digit_count == 0)
    _digit_count = 1;
  if (position < 0)
    ++_digit_count;

  u8g2.drawUTF8((_digit_count * 20 + 4), 28, "μm");
}
inline void util_draw_distance(uint32_t position) {
  // 18px: u8g2_font_VCR_OSD_tn
  // 30px: u8g2_font_logisoso30_tn
  // 32px: u8g2_font_logisoso32_tn
  u8g2.setFont(u8g2_font_logisoso32_tn);
  char strOut[7];
  ltoa(position, strOut, 10);
  u8g2.drawStr(0, 32, strOut);
}

// Interface
inline void DisplayController() { u8g2.begin(); }
inline void display_distance() {
  u8g2.firstPage();
  do {
    auto micron = distance_data();
    util_draw_distance(micron);
    util_draw_um(micron);
  } while (u8g2.nextPage());
}
inline void clear_display() {
  u8g2.clear(); // HARDCODED
  clear_distance();
}
