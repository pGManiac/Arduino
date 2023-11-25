const byte xorChecksum = 0b01010101;


/**
 * @brief Represents a frame with bit vector and state information.
 *
 * The Frame struct encapsulates a data frame with a 16-bit bit vector
 * and a frame state indicating whether it's data, an acknowledgment (ACK),
 * or an error.
 */
struct Frame {
  bool bitvector[16];
  byte frameState; /**< Frame state indicating data, ACK, or Error. 
                         - 00: Data
                         - 01: ACK
                         - 11: Error
                     */

   /**
     * @brief Default constructor.
     *
     * Initializes the bit vector to all false values.
     */
  Frame() {
    for(int i = 0; i < 16; i++) {
      bitvector[i] = false;
    }
  }

  /**
     * @brief Parameterized constructor.
     *
     * Creates a data Frame based on the provided data byte.
     * Most significant byte comes first for both data and checksum.
     *
     * @param data The data byte used to construct the frame.
     */
  Frame(byte data) {
    //Fill index 0 - 7 with bits from data byte, highest significant bit comes first
    for (int i = 7; i >=0; i--) {
            bitvector[i] = (data & (1 << i)) != 0;
        }
    //Fill index 8-15 with bits from checksum, highest significant bit comes first
    for (int i = 15; i>=8; i--) {
            bitvector[i] = (data ^ xorChecksum) & (1 << (i-8));
        }
    0 << frameState;
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
};

void setup() {
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
