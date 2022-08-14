#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  tft.init();
  tft.fillScreen(TFT_GREEN);
  Serial.println("init success");
}

void loop() {
  // put your main code here, to run repeatedly:

}
