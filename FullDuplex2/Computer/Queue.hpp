#pragma once

#include <fstream>


#include "Frame.hpp"
#include "SerialPort.hpp"

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
};


struct SendingQueue : public Queue {
    bool acknowledgementReceived;

    SendingQueue() : acknowledgementReceived(false) {}
};

struct ReceivedQueue : public Queue {

};

const char* portName = "/dev/ttyUSB0";

class Queues {
private:
    SendingQueue sendingQueue;
    ReceivedQueue receivedQueue;
    SerialPort serialPort;

public:
    Queues() : serialPort(portName) {
        serialPort.configure();
    }

    void send() {
        if (!sendingQueue.acknowledgementReceived) {
            // Do something when acknowledgement is not received
        } else {
            if (sendingQueue.head != nullptr) {
                serialPort.sendBytes(sendingQueue.head->frame->hardWareBytes,
                                     sizeof(sendingQueue.head->frame->hardWareBytes));
            }
        }
    }


    void receive() {

    }
};