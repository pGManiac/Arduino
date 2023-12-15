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
Queues::Queues(const char* _portName) : serialPort(_portName) {
    serialPort.configure();
}

/**
     * @brief Sends the front frame from the sending queue.
     *
     * If the sending queue is ready to send and has frames, sends the front frame
     * using the serial port and updates the sending queue accordingly.
     */
void Queues::send() {
    if (!sendingQueue.readyToSend) {
        std::cout << "not ready to send";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } else {
        if (sendingQueue.head != nullptr) {
            std::cout << "set ready to send to false";
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
    std::cout << "I am in the receive function";
    if(serialPort.getBufferAvailability()) {
        std::cout << "I received smth";
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
void Queues::processReceive(std::ofstream& of) {
    Frame* frame;
    if(receivedQueue.head != nullptr) {
        switch(receivedQueue.head->frame->frameState) {
            case 0: //data
                // Send to file
                std::cout << "hi";
                std::cout << receivedQueue.head->frame->data; //print on terminal for test
                of.write(reinterpret_cast<const char*>(receivedQueue.head->frame->data), sizeof(uint8_t));
                frame = new Frame(true);
                sendingQueue.enqueueAtFront(frame);
                sendingQueue.readyToSend = true;

                receivedQueue.dequeue();
                break;

            case 1: //ACK
                std::cout << "Processing ACK frame" << std::endl;
                sendingQueue.dequeue();
                sendingQueue.readyToSend = true;
                break;

            case 2: //Error
                if(sendingQueue.sentACK) {
                    frame = new Frame(true);
                    sendingQueue.enqueueAtFront(frame);
                }
                sendingQueue.readyToSend = true;
                std::cout << "error";
                send();  // Potential recursive call?
                break;

            default: //Fail
                frame = new Frame(false);
                sendingQueue.enqueueAtFront(frame);
                std::cout << "fail";
                break;
        }
    }

}

void Queues::sendByte(uint8_t number) {
    Frame* frame = new Frame(number);
    sendingQueue.enqueue(frame);
}