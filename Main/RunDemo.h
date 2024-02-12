#include <TFT_eSPI.h>
#include "bitmap_rgb565.h" //(Bitmap generated with LCD Image Converter) https://sourceforge.net/projects/lcd-image-converter/
//Don't forget to change User_Setup.h inside TFT_eSPI library !

extern const int pinkBuiltInLedPin;
extern const int blueLedPin;
TFT_eSPI tft = TFT_eSPI();   // Invoke library

void runDemo() {
  Serial.println("runDemo");
  digitalWrite(pinkBuiltInLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);

  tft.begin();     // initialize a ST7789 chip
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,240,320,epd_bitmap_demo);
}