const int testPin = 12;  // Assuming the LED is connected to digital pin 12


struct Node {
  uint8_t byte;
  Node* next;

  Node(uint8_t _byte, Node* nextNode) : byte(_byte), next(nextNode) {}
};

struct ToBeSentToPC {
  Node* head;
  Node* tail;

  ToBeSentToPC() : head(nullptr), tail(nullptr) {}

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
    } else {
        Serial.println("Error: Queue is empty. Cannot dequeue.");
        // Handle the error if needed
    }
}

};



  void
  setup() {
  pinMode(testPin, OUTPUT);
  Serial.begin(9600);  // Use the same baud rate as in your C code
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
