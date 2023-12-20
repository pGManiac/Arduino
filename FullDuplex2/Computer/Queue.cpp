#include "Queue.hpp"

/**
     * @brief Default constructor.
     *
     * Initializes both head and tail pointers to nullptr.
     */
Queue::Queue() : head(nullptr), tail(nullptr) {}

/**
     * @brief Enqueues a Frame at the back of the queue.
     *
     * Creates a new node with the provided Frame and adds it to the back
     * of the queue.
     *
     * @param framePtr The Frame to be enqueued.
     */
void Queue::enqueue(Frame* framePtr) {
    Node* newNode = new Node(framePtr, nullptr);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

/**
     * @brief Enqueues a Frame at the front of the queue.
     *
     * Creates a new node with the provided Frame and adds it to the front
     * of the queue.
     *
     * @param framePtr The Frame to be enqueued.
     */
void Queue::enqueueAtFront(Frame* framePtr) {
    Node* newNode = new Node(framePtr,nullptr);

    if(head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

/**
     * @brief Dequeues the front node from the queue.
     *
     * Removes the front node from the queue and updates the head pointer.
     * If the queue becomes empty, updates the tail pointer as well.
     */
void Queue::dequeue() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;

        // If the queue becomes empty, update the tail pointer as well
        if (head == nullptr) {
            tail = nullptr;
        }
    }
}

/**
     * @brief Default constructor for Queues.
     *
     * Initializes the serial port with the specified port name and configures it.
     */
Queues::Queues(const char* _portName) : serialPort(_portName), inputFile(), outputFile() {
    serialPort.configure();
}

/**
     * @brief Opens the input file.
     * 
     * Opens the input file in binary mode. If the input file can not be opened an error message is printed.
     * 
     * @param inputFileName The name of the input file to be opened.
    */
void Queues::openInputFile(const char* inputFileName) {
    inputFile.open(inputFileName, std::ios::in | std::ios::binary);
    if(!inputFile.is_open()) {
        std::cerr << "Error opening input file.\n";
    }
}

/**
     * @brief Opens the output file.
     * 
     * Opens the output file in binary mode. If the input file can not be opened an error message is printed.
     * 
     * @param outputFileName The name of the output file to be opened.
    */
void Queues::openOutputFile(const char* outputFileName) {
    outputFile.open(outputFileName, std::ios::out | std::ios::binary);
    if(!outputFile.is_open()){
        std::cerr << "Error opening output file.\n";
    }
}

/**
     * @brief Closes the input file.
    */
void Queues::closeInputFile() {
    if(inputFile.is_open()) {
        inputFile.close();
    }
}

/**
     * @brief Closes the output file.
    */
void Queues::closeOutputFile() {
    if(outputFile.is_open()) {
        outputFile.close();
    }
}

/**
     * @brief Reads a byte from the input file.
     * 
     * Attempts to read a byte from the input file associated with this Queues instance.
     * 
     * @param byte A reference to a char variable where the read byte will be stored.
     * @return Returns true if a byte was successfully read, false otherwise.
    */
bool Queues::readByteFromFile(char& byte) {
    return static_cast<bool>(inputFile.get(byte));
}

/**
     * @brief Sends the front frame from the sending queue.
     *
     * If the sending queue is ready to send and has frames, sends the front frame
     * using the serial port and updates the sending queue accordingly.
     */
void Queues::send() {
    if (!sendingQueue.readyToSend) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "not ready to send\n";
    } else {
        if (sendingQueue.head != nullptr) {
            serialPort.sendBytes(sendingQueue.head->frame->hardWareBytes,
                                 sizeof(sendingQueue.head->frame->hardWareBytes));
            sendingQueue.readyToSend = false;
            removeIfACK();
        }
    }
}

/**
     * @brief Removes the front frame from the sending queue if it is an ACK frame.
     *
     * If the front frame in the sending queue is an ACK frame, removes it from the queue.
     * Sets the sentACK flag accordingly.
     */
void Queues::removeIfACK() {
    if (sendingQueue.head != nullptr && sendingQueue.head->frame->frameState == 1) {
        sendingQueue.dequeue();
        sendingQueue.sentACK = true;
    } else {
        sendingQueue.sentACK = false;
    }
}

/**
     * @brief Receives frame from the serial port and enqueues it in the received queue.
     */
void Queues::receive() {
    serialPort.receive8Bytes();
    if(serialPort.getBufferAvailability()) {
        Frame *newFrame = new Frame(serialPort.getReadBuffer());
        serialPort.makeBufferNotAvailable();
        receivedQueue.enqueue(newFrame);  // Enqueue the pointer
    }
}

/**
     * @brief Processes the front frame in the received queue based on its frame state.
     *
     * Depending on the frame state of the front frame in the received queue, performs
     * different actions, such as sending frames, dequeuing frames, and initiating
     * the sending process.
     */
void Queues::processReceive() {
    Frame* frame;
    if(receivedQueue.head != nullptr) {
        std::cout << static_cast<int>(receivedQueue.head->frame->frameState);
        std::cout << "I received something";
        switch(receivedQueue.head->frame->frameState) {
            case 0: //data
                // Send to file
                std::cout << receivedQueue.head->frame->data; //print on terminal for test
                outputFile.write(reinterpret_cast<const char*>(receivedQueue.head->frame->data), sizeof(uint8_t));
                frame = new Frame(true);
                sendingQueue.enqueueAtFront(frame);
                sendingQueue.readyToSend = true;

                receivedQueue.dequeue();
                break;

            case 1: //ACK
                std::cout << "Processing ACK frame\n";
                sendingQueue.dequeue();
                sendingQueue.readyToSend = true;
                break;

            case 2: //Error
                if(sendingQueue.sentACK) {
                    frame = new Frame(true);
                    sendingQueue.enqueueAtFront(frame);
                }
                sendingQueue.readyToSend = true;
                std::cout << "error\n";
                send();  // Potential recursive call?
                break;

            default: //Fail
                frame = new Frame(false);
                sendingQueue.enqueueAtFront(frame);
                std::cout << "fail\n";
                break;
        }
    }

}

void Queues::sendByte(uint8_t number) {
    Frame* frame = new Frame(number);
    sendingQueue.enqueue(frame);
}