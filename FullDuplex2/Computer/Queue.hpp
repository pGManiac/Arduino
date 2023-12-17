#pragma once

#include <fstream>
#include <thread>
#include <chrono>


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

    Queue();

    void enqueue(Frame*);

    void enqueueAtFront(Frame*);

    void dequeue();
};

/**
 * @brief Represents a sending queue with additional attributes.
 *
 * The SendingQueue struct extends the Queue and includes additional attributes
 * related to the sending process.
 */
struct SendingQueue : public Queue {
    bool readyToSend;
    bool sentACK;

    SendingQueue() : readyToSend(true), sentACK(false){}
};

/**
 * @brief Represents a received queue.
 *
 * The ReceivedQueue struct extends the Queue and is specialized for received frames.
 */
struct ReceivedQueue : public Queue {

};

/**
 * @brief Represents a set of queues and a SerialPort for communication.
 *
 * The Queues class encapsulates SendingQueue, ReceivedQueue, and SerialPort,
 * providing methods for sending, receiving, and processing frames.
 */
class Queues {
private:
    SendingQueue sendingQueue;
    ReceivedQueue receivedQueue;
    SerialPort serialPort;

    std::ifstream inputFile;
    std::ofstream outputFile;

public:
    Queues(const char*);

    void openInputFile(const char*);

    void openOutputFile(const char*);

    void closeInputFile();

    void closeOutputFile();

    bool readByteFromFile(char&);

    void send();

    void removeIfACK();

    void receive();

    void processReceive(std::ofstream& of);

    void sendByte(uint8_t);
};