
#include "Display_image.h"

void InitialiseDisplay() {
  display.init(115200, true, 2, false);
  SPI.end();
  SPI.begin(EPD_SCK, EPD_MISO, EPD_MOSI, EPD_CS);
  display.setRotation(1);                     // Use 1 or 3 for landscape modes
  u8g2Fonts.begin(display);                   // connect u8g2 procedures to Adafruit GFX
  u8g2Fonts.setFontMode(1);                   // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);              // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
  u8g2Fonts.setFont(u8g2_font_helvB10_tf);    // Explore u8g2 fonts from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  display.fillScreen(GxEPD_WHITE);
  display.setFullWindow();
}

void drawString(int x, int y, String text) {
  int16_t x1, y1;  //the bounds of x,y and w and h of the variable 'text' in pixels.
  uint16_t w, h;
  display.setTextWrap(false);
  display.getTextBounds(text, x, y, &x1, &y1, &w, &h);
  u8g2Fonts.setCursor(x, y + h);
  u8g2Fonts.print(text);
}

void start_image_E_inc() {
  u8g2Fonts.setFont(u8g2_font_helvB14_tf);
  uint8_t distance = 20;
  uint8_t counter = 0;
  const uint8_t startX = 10;
  const uint8_t startY = 10;
  const char *DISPLAY_TYPE = "Type: WeAct Epaper Module";
  const char *DISPLAY_INTERFACE = "Interface: SPI | Chip: SSD1680";
  const char *DISPLAY_DRIVER = "Driver: GxEPD2_290_C90c";
  const char *DISPLAY_SIZE = "Size: 2.9-inch 128 x 296 pixels";
  const char *DISPLAY_COLORS = "Colors: Red, Black and White";
  const char *PROGRAM_AUTHOR = "Authors: Maxim S. and Vika Z.";

  drawString(startX, startY + 0 * distance, DISPLAY_TYPE);
  drawString(startX, startY + 1 * distance, DISPLAY_INTERFACE);
  drawString(startX, startY + 2 * distance, DISPLAY_DRIVER);
  drawString(startX, startY + 3 * distance, DISPLAY_SIZE);
  u8g2Fonts.setForegroundColor(GxEPD_RED);
  drawString(startX, startY + 4 * distance, DISPLAY_COLORS);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  drawString(startX, startY + 5 * distance, PROGRAM_AUTHOR);
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GxEPD_RED);

  display.display(false);  // Full screen update mode

  // Important use bring the display in one of the two modes to
  // avoid a damage of the display that cannot get repaired.
  //display.powerOff();
  display.hibernate();
}

void Disp1_refresh() {

  display.fillScreen(GxEPD_WHITE);

  // Вывод на дисплей показателей СО2 ---------
  u8g2Fonts.setFont(u8g2_font_inr33_mn);  // 33px только цифры
  if (CO2 >= 1400) {
    u8g2Fonts.setForegroundColor(GxEPD_RED);
  } else {
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  }
  int spix = 0;
  char out[10];
  dtostrf(CO2, 5, 0, out);
  if (CO2 < 1000) {
    for (int i = 0; i < 10 - 1; i++) {
      out[i] = out[i + 1];
    }
    spix = spix + 33;
  }
  if (CO2 < 10000) {
    for (int i = 0; i < 10 - 1; i++) {
      out[i] = out[i + 1];
    }
    spix = spix + 33;
  }
  drawString(0, 27, out);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setFont(u8g2_font_crox4h_tf);  // 14px
  drawString(145 - spix, 23, "ppm");
  u8g2Fonts.setForegroundColor(GxEPD_RED);
  drawString(145 - spix, 9, "CO");
  u8g2Fonts.setFont(u8g2_font_crox1hb_tf);  // 9px
  drawString(172 - spix, 9, "2");
  display.drawRect(0, 0, 190 - spix, 38, GxEPD_RED);
  //----------------------------------------------------

  //Вывод на дисплей показателей температуры
  u8g2Fonts.setFont(u8g2_font_inr21_mn);  // 21px только цифры
  if (Temp_BME280 >= 28.0 || Temp_BME280 <= 21.0) {
    u8g2Fonts.setForegroundColor(GxEPD_RED);
  } else {
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  }
  int spix1 = 0;
  char out1[10];
  char out2[4];
  char out3[2];
  dtostrf(Temp_BME280, 5, 1, out1);
  if (Temp_BME280 >= 0.0) {
    spix1 = spix1 + 18;
  }
  for (int i = 0; i < 4; i++) {
    if (out1[i] == '.') {
      break;
    }
    out2[i] = out1[i];
  }
  out2[3] = '\0';
  out3[0] = out1[4];
  out3[1] = '\0';
  drawString(61 - 10 - spix1, 56, ".");
  drawString(0 - spix1, 56, out2);
  drawString(84 - 20 - spix1, 56, out3);
  u8g2Fonts.setFont(u8g2_font_crox4h_tf);  // 14px
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  drawString(103 - 20 - spix1, 56, "°C");
  if (Temp_BME280 >= 28.0) {
    display.drawBitmap(103 + 28 - 20 - spix1, 41, fire2, fire2_widht, fire2_height, GxEPD_RED);
    display.drawBitmap(103 + 28 - 20 - spix1, 41, fire1, fire1_widht, fire1_height, GxEPD_BLACK);
  }
  if (Temp_BME280 <= 21.0) {
    display.drawBitmap(103 + 28 - 20 - spix1, 41, snowflake1, snowflake1_widht, snowflake1_height, GxEPD_BLACK);
  }
  if (Temp_BME280 < 28.0 && Temp_BME280 > 21.0) {
    display.drawBitmap(103 + 28 - 20 - spix1, 41, sheet1, sheet1_widht, sheet1_height, GxEPD_BLACK);
  }
  display.drawRect(0, 39, 138 - spix1, 29, GxEPD_RED);
  //--------------------------------------

  //Вывод на дисплей показателей влажности
  u8g2Fonts.setFont(u8g2_font_inr21_mn);  // 21px только цифры
  if (RH_BME280 >= 75.0 || RH_BME280 <= 40.0) {
    u8g2Fonts.setForegroundColor(GxEPD_RED);
  } else {
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  }
  int spix2 = 0;
  char out4[10];
  char out5[4];
  char out6[2];
  dtostrf(RH_BME280, 5, 1, out4);
  if (RH_BME280 < 100.0) {
    spix2 = spix2 + 18;
  }
  for (int i = 0; i < 4; i++) {
    if (out4[i] == '.') {
      break;
    }
    out5[i] = out4[i];
  }
  out5[3] = '\0';
  out6[0] = out4[4];
  out6[1] = '\0';
  drawString(61 - 10 - spix2, 86, ".");
  drawString(0 - spix2, 86, out5);
  drawString(84 - 20 - spix2, 86, out6);
  u8g2Fonts.setFont(u8g2_font_crox4h_tf);  // 14px
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  drawString(103 - 20 - spix2, 87, "%");
  u8g2Fonts.setFont(u8g2_font_crox1hb_tf);  // 9px
  u8g2Fonts.setForegroundColor(GxEPD_RED);
  drawString(103 - 20 - spix2, 72, "Rh");

  if (RH_BME280 >= 75.0) {
    display.drawBitmap(103 + 28 - 20 - spix2, 71, drops1, drops1_widht, drops1_height, GxEPD_BLACK);
  }
  if (RH_BME280 <= 40.0) {
    display.drawBitmap(103 + 28 - 20 - spix2, 71, cactus, cactus_widht, cactus_height, GxEPD_BLACK);
    display.drawBitmap(103 + 28 - 20 - spix2, 71, cactus_flow, cactus_flow_widht, cactus_flow_height, GxEPD_RED);
  }
  if (RH_BME280 > 40.0 && RH_BME280 < 75.0) {
    display.drawBitmap(103 + 28 - 20 - spix2, 71, sheet1, sheet1_widht, sheet1_height, GxEPD_BLACK);
  }

  display.drawRect(0, 69, 138 - spix2, 29, GxEPD_RED);
  //--------------------------------------

  //Вывод на дисплей показателей давления и высоты
  u8g2Fonts.setFont(u8g2_font_crox1hb_tf);  // 9px
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  drawString(2, 103, "Pres:");
  drawString(4, 117, "  Alt:");
  display.drawRect(0, 99, 190 - spix, 29, GxEPD_RED);
  //--------------------------------------

  // Полный рефреш для RBW
  display.display(false);  
  // Усыпление
  display.hibernate();
}

// void Ugar(){
//   display.fillScreen(GxEPD_WHITE);
//   display.drawBitmap(0, 0, image, 296, 128, GxEPD_RED);
//   // Полный рефреш для RBW
//   display.display(false);
//   // Усыпление
//   display.hibernate();
// }
