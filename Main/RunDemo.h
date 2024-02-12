extern const int pinkBuiltInLedPin;
extern const int blueLedPin;

void runDemo() {
  Serial.println("runDemo");
  digitalWrite(pinkBuiltInLedPin, HIGH);
  digitalWrite(blueLedPin, LOW);

}