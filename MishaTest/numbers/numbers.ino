void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  //set PORTD for output and PORTB for input
  DDRD = 0x0F;
  DDRB = 0x00;
  //enable PCINT for PB0-PB3
  PCICR = 0x01;
  PCMSK0 = 0x0F;

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //send numbers from 0 to 255 and print them
  for (uint8_t i = 0; i < 256; ++i) {
    PORTD = i;
    Serial.print("OUTPUT: ");
    for (int i = 7; i >= 0; --i) {
    Serial.print(bitRead(PORTD, i));
    }
    Serial.println();
    delay(1000);
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