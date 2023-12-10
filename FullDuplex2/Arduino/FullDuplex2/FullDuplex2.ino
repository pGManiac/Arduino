volatile uint8_t numberCollectedBytes = 0;
volatile uint8_t bytesToSend[8];
volatile ToBeSentToPC sendToPCQueue = ToBeSentToPC();


struct Node {
  uint8_t byte;
  Node* next;

  Node(uint8_t _byte, Node* nextNode) : byte(_byte), next(nextNode) {}
};

struct ToBeSentToPC {
  Node* head;
  Node* tail;

  ToBeSentToPC() : head(nullptr), tail(nullptr) {pinMode(testPin, OUTPUT);}

  void enqueue(uint8_t receivedByte) {
    Node* newNode = new Node{receivedByte, nullptr};
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
  }

  void dequeue() {
    if (head != nullptr) {
        Serial.write(head->byte);

        Node* temp = head;
        head = head->next;

        delete temp;

        if (head == nullptr) {
            tail = nullptr; // The queue is now empty
        }
    }
}

};

void sendToArduino() {
  if (numberCollectedBytes < 8) {
    uint8_t receivedData = Serial.read();
    bytesToSend[numberCollectedBytes] = receivedData;
    numberCollectedBytes++;
  } else {
    numberCollectedBytes = 0;
    for (uint8_t i = 0; i < 8; i++) {
      PORTC = bytesToSend[i];
      delay(50); //testen, welcher delay passt
    }
  }
}

ISR(PCINT0_vect) {
  sendToPCQueue.enqueue(PINB);
}

void setup() {
  Serial.begin(9600);  // Use the same baud rate as in your C code
  //set PORTC for output and PORTB for input
  DDRC = 0x0F;
  DDRB = 0x00;
  PORTB = 0x00;
  //enable PCINT for PB0-PB3
  PCICR = 0x0F; //PIN Change nur auf Takt: 0x04
  PCMSK0 = 0x0F;
}

void loop() {
  if (Serial.available() > 0) {
    sendToArduino();
    sendToPCQueue.dequeue();
  }
  // Add other logic here if needed
}
