#include <TFT_eSPI.h>
//#include "Beach_Bitmap_rgb565.h" //(Bitmap generated with LCD Image Converter) https://sourceforge.net/projects/lcd-image-converter/
//Don't forget to change User_Setup.h inside TFT_eSPI library !
#include "Our1th_Bitmap_rgb565.h"
#include "Our2th_Bitmap_rgb565.h"
//#include "Our520_1th_Bitmap_rgb565.h"
//#include "Our520_2th_Bitmap_rgb565.h"

extern const int pinkBuiltInLedPin;
extern const int blueLedPin;
extern TFT_eSPI tft;   // Invoke library

void runDefaultImg(const int index) {
  Serial.println("runDefaultImg");
  digitalWrite(pinkBuiltInLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);

  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.fillScreen(TFT_BLACK);

  if (index == 0){
    tft.pushImage(0,0,240,320,oneth_bitmap_demo);
  }else if (index == 1){
    tft.pushImage(0,0,240,320,twoth_bitmap_demo);
  }

  tft.setSwapBytes(false); // Swap the byte order for pushImage() - corrects endianness
}