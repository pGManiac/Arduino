struct Node {
  uint8_t byte;
  Node* next;

  Node(uint8_t _byte, Node* nextNode) : byte(_byte), next(nextNode) {}
};

struct Queue {
  Node* head;
  Node* tail;

  Queue() : head(nullptr), tail(nullptr) {
    
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
      Node* temp = head;
      head = head->next;

      // If the queue becomes empty after dequeue
      if (head == nullptr) {
        tail = nullptr;
      }

      delete temp;
    }
  }
};

struct SendToPCQueue {
  Queue queue;

  void writeAndDequeue() {
    while (queue.head != nullptr) {
      Serial.write(queue.head->byte);
      queue.dequeue();
    }
  }

};

struct SendToArduinoQueue {
  Queue queue;
  int length;

  void readFromPC() {
    if((Serial.available() > 0) && (length < 8) ) {
      uint8_t receivedData = Serial.read();
      queue.enqueue(receivedData);
      length++;
    }
  }
  
  void sendToArduino() {
    if(length == 8) {
      for(int i = 0; i < 8; i++) {
        
        PORTC = queue.head->byte;
        queue.dequeue();
        length--;
        delay(18);
      }
    }
  }
}; 

volatile SendToPCQueue sendToPCQueue;
volatile SendToArduinoQueue sendToArduinoQueue;

ISR(PCINT0_vect) {
  sendToPCQueue.queue.enqueue(PINB);
  }

void setup() {
  Serial.begin(9600);
  DDRC = 0x0F;
  DDRB = 0x00;
  PORTB = 0x00;
  PCMSK0 = 0x04;
  PCICR = 0x01;
  PORTC = 0x00;
  pinMode(2, OUTPUT); 
  sei();
  Serial.flush();
}

void loop() {
  delay(10);
  sendToArduinoQueue.readFromPC();
  sendToArduinoQueue.sendToArduino();
  sendToPCQueue.writeAndDequeue();
  // Add other logic here if needed

}