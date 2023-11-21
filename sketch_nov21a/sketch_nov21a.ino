const int outputPins = {0, 1, 2, 3};
const int intputPins = {4, 5, 6, 7};


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
  
}
