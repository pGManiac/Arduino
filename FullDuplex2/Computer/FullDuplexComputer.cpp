#include <iostream>

#include "Queue.hpp"
#include "SerialPort.hpp"
#include <string>
#include <iostream>

const char* portName = "/dev/ttyUSB0";
const char* inputFileName = "input.txt";
const char* outputFileName = "output.txt";


int main() {
    Queues queues(portName);

    //queues.openInputFile(inputFileName);

    usleep(5000000);

    std::string line;
    uint8_t character;

    // Read input from standard input (stdin)
    while (std::getline(std::cin, line)) {
        for (char i : line) {
            character = i;
            queues.sendByte(character);
        }
    }
    queues.sendFin("fin");

    while((queues.isReceivedFIN() == 0) || (queues.isSentFIN() == 0) || (queues.isSendingQueueReadyToSend() == 0)) {
        queues.send();

        queues.receive();

        queues.processReceive();
    }
    return 0;
}