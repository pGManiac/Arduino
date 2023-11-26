const byte xorChecksum = 0b01010101;


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

  Frame(bool response) {

  }
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
 * @param s The transmission mode:
 *          - 0: Send data and checksum from highest to lowest bits.
 *          - 1: Send an acknowledgment frame.
 *          - 2: Send an error frame.
 * @param framePtr Pointer to the Frame to be transmitted.
 */
void sendFrame(byte s, Frame* framePtr) {

  byte quarter = 0x00;

  switch (s) {
    case 0:
      //send data from highest to lowest
      quarter = (framePtr.data & 0xC0) >> 6;
      PORTC = 0x08 | quarter;
      quarter = (framePtr.data & 0x30) >> 4;
      PORTC = 0x04 | quarter;
      quarter = (framePtr.data & 0x0C) >> 2;
      PORTC = 0x00 | quarter;
      quarter = framePtr.data & 0x03;
      PORTC = 0x04 | quarter;

      //send checksum from highest to lowest
      quarter = (framePtr.checksum & 0xC0) >> 6;
      PORTC = 0x00 | quarter;
      quarter = (framePtr.checksum & 0x30) >> 4;
      PORTC = 0x04 | quarter;
      quarter = (framePtr.checksum & 0x0C) >> 2;
      PORTC = 0x00 | quarter;
      quarter = framePtr.checksum & 0x03;
      PORTC = 0x04 | quarter;

      break;
    case 1:
      //send acknowledge
      quarter = framePtr.data & 0x03;
      PORTC = 0x0C | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      break;
    case 2:
      //send error
      quarter = framePtr.data & 0x03;
      PORTC = 0x0C | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      break;
    case 3:
      //send handshake request
      quarter = framePtr.data & 0x03;
      PORTC = 0x0C | quarter;
      PORTC = 0x00 | quarter;
      PORTC = 0x04 | quarter;
      PORTC = 0x00 | quarter;
      break;
  }
}

void setup() {
  
  Serial.begin(9600);
  //set PORTC for output and PORTB for input
  DDRC = 0x0F;
  DDRB = 0x00;
  //enable PCINT for PB0-PB3
  PCICR = 0x01;
  PCMSK0 = 0x0F;
}

void loop() {
  // put your main code here, to run repeatedly:

}
