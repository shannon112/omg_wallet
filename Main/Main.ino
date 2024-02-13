#include "RunDefaultImg.h" 
#include "RunWebImg.h" 
#include "RunSetup.h" 

// parameter details
const int modePin = 32;
const int leftButtonPin = 12;
const int rightButtonPin = 13;
const int pinkBuiltInLedPin = LED_BUILTIN;
const int blueLedPin = 33;

int syncPinStatPrev = 1;
int syncPinStatCurr = 1;
int negLeftPinStatPrev = 1;
int negLeftPinStatCurr = 1;
int posRightPinStatPrev = 1;
int posRightPinStatCurr = 1;

String mySSID;
String myPassword;
String myURLPrev = "";
String myURLCurr = "";

int imgIndex = 1;

TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

void setup() {
  // serial port setup
  Serial.begin(921600);

  // pin setup
  pinMode(modePin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(pinkBuiltInLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  tft.begin();     // initialize a ST7789 chip

  // home img in default
  runDefaultImg(0);
}

void loop() {
  // read button
  syncPinStatPrev = syncPinStatCurr;
  syncPinStatCurr = digitalRead(modePin);
  const bool shouldSetup = syncPinStatPrev == 1 && syncPinStatCurr == 0;

  negLeftPinStatPrev = negLeftPinStatCurr;
  negLeftPinStatCurr = digitalRead(leftButtonPin);
  const bool shouldNegOne = negLeftPinStatPrev == 1 && negLeftPinStatCurr == 0;

  posRightPinStatPrev = posRightPinStatCurr;
  posRightPinStatCurr = digitalRead(rightButtonPin);
  const bool shouldPosOne = posRightPinStatPrev == 1 && posRightPinStatCurr == 0;

  // execute actions
  if (shouldSetup) {
    runSetup();
    runWebImg();
    imgIndex = 0;
  }

  if (shouldNegOne)
  {
    imgIndex = (imgIndex -1 > 0) ? imgIndex -1 : imgIndex;
  }
  if (shouldPosOne)
  {
    imgIndex = imgIndex + 1;
  }

  if (shouldPosOne || shouldNegOne)
  {
    if (imgIndex % 3 == 0){
      runWebImg();
    }else if (imgIndex % 3 == 1){
      runDefaultImg(0);
    }else if (imgIndex % 3 == 2){
      runDefaultImg(1);    
    }
  }

  // end
  delay(33);  // ms
}
