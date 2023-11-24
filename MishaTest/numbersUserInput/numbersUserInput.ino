void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  //set PORTC for output and PORTB for input
  DDRC = 0x0F;
  DDRB = 0x00;
  PORTB = 0x00;
  //enable PCINT for PB0-PB3
  PCICR = 0x01;
  PCMSK0 = 0x0F;

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0) {
    // Read the entire line until a newline character is received
    // String incomingString = Serial.readStringUntil('\n');

    // for starters read incoming number and send it, queen
    uint8_t userInput = Serial.parseInt();

    // Print the received string
    Serial.print("Received: ");
    Serial.println(userInput);

    PORTC = userInput;
    Serial.print("OUTPUT: ");
    for (int i = 7; i >= 0; --i) {
    Serial.print(bitRead(PORTC, i));
    }
    Serial.println();
    
  }

}

ISR(PCINT0_vect) {
  //read PORTB and print byte on terminal

  Serial.print("INPUT: ");
  for (int i = 7; i >= 0; --i) {
    Serial.print(bitRead(PINB, i));
  }
  Serial.println();
  delay(1000);
}