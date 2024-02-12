#include "RunDemo.h" 
#include "RunSetup.h" 

// parameter details
const int modePin = 32;
const int leftButtonPin = 12;
const int rightButtonPin = 13;
const int pinkBuiltInLedPin = LED_BUILTIN;
const int blueLedPin = 33;
int pinStatPrev = 1;
int pinStatCurr = 1;
bool isDemoMode = true; // else it's setup mode

void setup() {
  // serial port setup
  Serial.begin(921600);

  // pin setup
  pinMode(modePin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(pinkBuiltInLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // home img in default
  runDemo();
}

void loop() {
  // read button
  pinStatPrev = pinStatCurr;
  pinStatCurr = digitalRead(modePin);
  const bool shouldSetup = pinStatPrev == 1 && pinStatCurr == 0;

  // execute actions
  if (shouldSetup) {
    runSetup();
    runDemo();
  }

  // end
  delay(33);  // ms
}
