// Include the jpeg decoder library
#include <TJpg_Decoder.h>

// Include SPIFFS
#define FS_NO_GLOBALS
#include <FS.h>

// Include WiFi and http client
#include "SPIFFS.h" // Required for ESP32 only
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// Load tabs attached to this sketch
#include "List_SPIFFS.h"
#include "Web_Fetch.h"

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library

extern TFT_eSPI tft;         // Invoke custom library

extern String mySSID;
extern String myPassword;
extern String myURL; // https://i.imgur.com/C77RWcq.jpg for test

// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}

void runWebImg()
{
  Serial.println("runDemo");
  digitalWrite(pinkBuiltInLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);

  // Initialise SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  Serial.println("\r\nSPIFFS Initialisation done.");

  // Formatting
  bool formatted = SPIFFS.format();
  if(formatted){
    Serial.println("\n\nSuccess formatting");
  }else{
    Serial.println("\n\nError formatting");
  }

  // Initialise the TFT
  tft.fillScreen(TFT_BLACK);

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);

  // Initialise the Wifi
  Serial.print("Attempting to connect to SSID with PWD");
  Serial.print(mySSID.c_str());
  Serial.println(myPassword.c_str());
  WiFi.begin(mySSID.c_str(), myPassword.c_str());

  // attempt to connect to Wifi network:
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    digitalWrite(pinkBuiltInLedPin, count++ % 2);
    delay(500);
  }
  digitalWrite(pinkBuiltInLedPin, HIGH);

  Serial.print("Connected to ");
  Serial.println(mySSID.c_str());

  // Fetch the jpg file from the specified URL, examples only, from imgur
  uint32_t t = millis();
  bool loaded_ok = getFile(myURL, "/webImg.jpg"); // Note name preceded with "/"
  t = millis() - t;
  if (loaded_ok) { Serial.print(t); Serial.println(" ms to download"); }

  // Now draw the SPIFFS file
  t = millis();
  TJpgDec.drawFsJpg(0, 0, "/webImg.jpg");
  t = millis() - t;
  Serial.print(t); Serial.println(" ms to draw to TFT");

  WiFi.disconnect(); // to eliminate the blinking on the screen
}