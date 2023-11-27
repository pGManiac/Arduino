const byte xorChecksum = 0b01010101;


  volatile byte defragData = 0x00;
  volatile byte defragCheck = 0x00;
  volatile byte readCounter = 0;


/**
 * @brief Represents a frame with bit vector and state information.
 *
 * The Frame struct encapsulates a data frame with a byte for data, a byte for checksum and a byte for Data/Ack/Error
 */
struct Frame {
  byte data;
  byte checksum;
  byte frameState; /**< Frame state indicating data, ACK, or Error. 
                         - 00: Data
                         - 01: ACK
                         - 10: Error
                         - 11: handshake request
                     */

   /**
     * @brief Default constructor.
     *
     * Initializes all bits to 0;
     */
  Frame() {
    0 << data;
    0 << checksum;
    0 << frameState;
  }

  /**
     * @brief Parameterized constructor.
     *
     * Creates a data Frame based on the provided data byte.
     *
     * @param data The data byte used to construct the frame.
     */
  Frame(byte _data) : data(_data) {
    //Fill index 8-15 with bits from checksum, highest significant bit comes first
    checksum = _data ^ xorChecksum;
    0 << frameState;
  }

  Frame(byte _data, byte _frameState) {
    data = _data;
    checksum = _data ^xorChecksum;
    frameState = _frameState;
  }

  Frame(byte _data, byte _checksum, byte _frameState) : data(_data), checksum(_checksum), frameState(_frameState) {}
};

/**
 * @brief Represents a node in a linked list with Frame data.
 *
 * The Node struct is a basic building block for a linked list, containing
 * a Frame data member and a pointer to the next node in the sequence.
 */
struct Node {
    Frame* frame;
    Node* next;

    Node(Frame* framePtr, Node* nextNode) : frame(framePtr), next(nextNode) {}
};


/**
 * @brief Represents a queue of Frame elements using a linked list.
 *
 * The Queue struct is an implementation of a queue data structure using a
 * linked list. It maintains pointers to the head and tail nodes.
 */
struct Queue {
    Node* head; /**< Pointer to the first node in the queue. */
    Node* tail; /**< Pointer to the last node in the queue. */

    /**
     * @brief Default constructor.
     *
     * Initializes both head and tail pointers to nullptr.
     */
    Queue() : head(nullptr), tail(nullptr) {}


    /**
     * @brief Enqueues a Frame at the back of the queue.
     *
     * Creates a new node with the provided Frame and adds it to the back
     * of the queue.
     *
     * @param frame The Frame to be enqueued.
     */
    void enqueue(Frame* framePtr) {
        Node* newNode = new Node{framePtr, nullptr};
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
      }

    void enqueueAtFront(Frame* framePtr) {
        Node* newNode = new Node(framePtr,nullptr);

        if(head == nullptr) {
          head = tail = newNode;
        } else {
          newNode->next = head;
          head = newNode;
        }
      }
    
    void dequeue() {

    }
};

void send() {

}

/**
 * @brief Sends a Frame using a specified transmission mode.
 *
 * This function sends the data and checksum from the provided Frame using the
 * specified transmission mode. The transmission mode determines the format and
 * sequence in which the data and checksum are sent.
 *
 * @param framePtr Pointer to the Frame to be transmitted.
 */
void sendFrame(Frame* framePtr) {

  byte quarter = 0x00;

  switch (framePtr->frameState) {
    case 0:
      //send data from highest to lowest
      quarter = (framePtr->data & 0xC0) >> 6;
      PORTC = 0x08 | quarter;
      quarter = (framePtr->data & 0x30) >> 4;
      PORTC = 0x04 | quarter;
      quarter = (framePtr->data & 0x0C) >> 2;
      PORTC = 0x00 | quarter;
      quarter = framePtr->data & 0x03;
      PORTC = 0x04 | quarter;

      //send checksum from highest to lowest
      quarter = (framePtr->checksum & 0xC0) >> 6;
      PORTC = 0x00 | quarter;
      quarter = (framePtr->checksum & 0x30) >> 4;
      PORTC = 0x04 | quarter;
      quarter = (framePtr->checksum & 0x0C) >> 2;
      PORTC = 0x00 | quarter;
      quarter = framePtr->checksum & 0x03;
      PORTC = 0x04 | quarter;

      break;
    case 1:
      //send acknowledge
      quarter = framePtr->data & 0x03;
      PORTC = 0x0C | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      break;
    case 2:
      //send error
      quarter = framePtr->data & 0x03;
      PORTC = 0x0C | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      break;
    case 3:
      //send handshake request
      quarter = framePtr->data & 0x03;
      PORTC = 0x0C | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      break;
  }
}

void readQuarter() {
  Serial.println(11);
  if (bitRead(PINB, 3) == 1) {
    defragData = 0x00;
    defragCheck = 0x00;
    readCounter = 0;
  }
  
  if (readCounter < 4) {
    for (uint8_t i = 1; i >= 0; --i) {
      defragData << (bitRead(PINB, i));
    }
    readCounter++;
  } else if ((4 <= readCounter) && (readCounter < 8)){
    for (uint8_t i = 1; i >= 0; --i) {
      defragCheck << (bitRead(PINB, i));
    }
    readCounter++;
  } else {
    Frame received = Frame(defragData, calcState(defragData, defragCheck));
    Serial.println(received.data);
  }
  
  //Bedenken: welche Kabel zieht Ulbricht raus?
  //ist die Abarbeitung des if schnell genug oder ändert sich der Input währenddessen wieder?
  //Queue?  
}

byte calcState(byte _defragData, byte _defragCheck) {
  byte state = 0x00;
  if ((_defragData ^ xorChecksum) == _defragCheck) {
    state = 0x01;
  } else {
    state = 0x02;
  }
  return state;
}

void setup() {
  
  Serial.begin(9600);
  //set PORTC for output and PORTB for input
  DDRC = 0x0F;
  DDRB = 0x00;
  //enable PCINT for PB0-PB3
  PCICR = 0x01;
  //PCMSK0 = 0x0B;
  attachInterrupt(digitalPinToInterrupt(10), readQuarter, CHANGE);

  //set up queues
  Queue sending = Queue();
  Queue receiving = Queue();

}

void loop() {
  // put your main code here, to run repeatedly:

  
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    Frame frame(input, 0x00);

    sendFrame(&frame);
    Serial.println(frame.data);
  }
 

  
}
