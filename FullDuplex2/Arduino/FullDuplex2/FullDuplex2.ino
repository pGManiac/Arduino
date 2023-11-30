const int ledPin = 12; // Assuming the LED is connected to digital pin 13

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Use the same baud rate as in your C code
}

void loop() {

  if (Serial.available() > 0) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin,LOW);
    delay(500);
  }
  // Add other logic here if needed
}
