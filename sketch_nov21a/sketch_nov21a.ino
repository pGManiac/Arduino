const int outputPins[] = {2, 3, 4, 5};
const int inputPins[] = {6, 7, 8, 9};


void setup() {
  // Set output pins
  for (int i = 0; i < 4; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  for(int i = 4; i < 8; i++) {
    pinMode(inputPins[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(outputPins[i], HIGH); // Set the pin HIGH
    delay(500); // Wait for 500 milliseconds (adjust as needed)
    digitalWrite(outputPins[i], LOW);  // Set the pin LOW
    delay(500); // Wait for 500 milliseconds (adjust as needed)
  }
}