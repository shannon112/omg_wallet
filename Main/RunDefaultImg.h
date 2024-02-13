#include <TFT_eSPI.h>
#include "Beach_Bitmap_rgb565.h" //(Bitmap generated with LCD Image Converter) https://sourceforge.net/projects/lcd-image-converter/
//Don't forget to change User_Setup.h inside TFT_eSPI library !

extern const int pinkBuiltInLedPin;
extern const int blueLedPin;
extern TFT_eSPI tft;   // Invoke library

void runDefaultImg() {
  Serial.println("runDefaultImg");
  digitalWrite(pinkBuiltInLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);

  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,240,320,epd_bitmap_demo);
  tft.setSwapBytes(false); // Swap the byte order for pushImage() - corrects endianness
}