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


volatile uint8_t numberCollectedBytes = 0;
volatile uint8_t bytesToSend[8];


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
    } else {
        Serial.println("Error: Queue is empty. Cannot dequeue.");
        // Handle the error if needed
    }
}

};

void sendData() {
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



void setup() {
  Serial.begin(9600);  // Use the same baud rate as in your C code
  //set PORTC for output and PORTB for input
  DDRC = 0x0F;
  DDRB = 0x00;
  PORTB = 0x00;
  //enable PCINT for PB0-PB3
  PCICR = 0x0F;
  PCMSK0 = 0x0F;

  
}

void loop() {
  if (Serial.available() > 0) {
    sendData();
  }
  // Add other logic here if needed
}