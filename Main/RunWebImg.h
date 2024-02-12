// Chenge next 2 lines to suit your WiFi network
const char* my_ssid     = "Lee Home";     // your network SSID (name of wifi network)
const char* my_password = "0920998891"; // your network my_password

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
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(my_ssid);
  WiFi.begin(my_ssid, my_password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(my_ssid);

  // Fetch the jpg file from the specified URL, examples only, from imgur
  uint32_t t = millis();
  bool loaded_ok = getFile("https://i.imgur.com/C77RWcq.jpg", "/M81.jpg"); // Note name preceded with "/"
  t = millis() - t;
  if (loaded_ok) { Serial.print(t); Serial.println(" ms to download"); }

  // Now draw the SPIFFS file
  t = millis();
  TJpgDec.drawFsJpg(0, 0, "/M81.jpg");
  t = millis() - t;
  Serial.print(t); Serial.println(" ms to draw to TFT");
}