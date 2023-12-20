struct Node {
  uint8_t byte;
  Node* next;

  Node(uint8_t _byte, Node* nextNode) : byte(_byte), next(nextNode) {}
};

struct ToBeSentToPC {
  Node* head;
  Node* tail;

  ToBeSentToPC() : head(nullptr), tail(nullptr) {
    
  }

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

volatile ToBeSentToPC sendToPCQueue;
volatile uint8_t numberCollectedBytes = 0;
volatile uint8_t bytesToSend[8];


void sendToArduino() {
  if((Serial.available() > 0) || (numberCollectedBytes == 8)) {
    if (numberCollectedBytes < 8) {
      uint8_t receivedData = Serial.read();
      bytesToSend[numberCollectedBytes] = receivedData;
      numberCollectedBytes++;
  } else {
    numberCollectedBytes = 0;
    for (uint8_t i = 0; i < 8; i++) {
      PORTC = bytesToSend[i];
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
    }
  }
  }
}

ISR(PCINT0_vect) {
  sendToPCQueue.enqueue(PINB);
}

void setup() {
  Serial.begin(9600);
  DDRC = 0x0F;
  DDRB = 0x00;
  PORTB = 0x00;
  PCMSK0 = 0x04;
  PCICR = 0x01;
  pinMode(2, OUTPUT);
  sei();
}

void loop() {
  //uint8_t byte = 255;
  //Serial.write(byte);
  //Serial.flush();
  
  sendToArduino();
  sendToPCQueue.dequeue();
  sendToPCQueue.dequeue();
  sendToPCQueue.dequeue();
  sendToPCQueue.dequeue();  
  sendToPCQueue.dequeue();
  sendToPCQueue.dequeue();
  sendToPCQueue.dequeue();
  sendToPCQueue.dequeue();
  // Add other logic here if needed

}