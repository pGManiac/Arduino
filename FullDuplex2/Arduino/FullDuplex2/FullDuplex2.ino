const int testPin = 12; // Assuming the LED is connected to digital pin 12



void setup() {
  pinMode(testPin, OUTPUT);
  Serial.begin(9600); // Use the same baud rate as in your C code
}

void loop() {
    if (Serial.available() > 0) {
        // Read a byte from the serial port
        uint8_t receivedData = Serial.read();

        // Check if the received data is equal to 1
        if (receivedData == 254) {

            // Execute code only when the received data is 1
            digitalWrite(testPin, HIGH);
            delay(50);
            digitalWrite(testPin, LOW);
            delay(50);
            digitalWrite(testPin, HIGH);
            delay(50);
            digitalWrite(testPin, LOW);
            delay(50);
            digitalWrite(testPin, HIGH);
            delay(50);
            digitalWrite(testPin, LOW);
            delay(50);
            digitalWrite(testPin, HIGH);
            delay(50);
            digitalWrite(testPin, LOW);
            delay(50);
        }
    }
    // Add other logic here if needed
}
