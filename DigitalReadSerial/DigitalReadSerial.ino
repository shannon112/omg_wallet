/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
const int syncPin = 32;
const int leftPin = 12;
const int rightPin = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(syncPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int syncState = digitalRead(syncPin);
  int leftState = digitalRead(leftPin);
  int rightState = digitalRead(rightPin);

  // print out the state of the button:
  Serial.print("syncState");
  Serial.println(syncState);
  Serial.print("leftState");
  Serial.println(leftState);
  Serial.print("rightState");
  Serial.println(rightState);
  delay(1);        // delay in between reads for stability
}
