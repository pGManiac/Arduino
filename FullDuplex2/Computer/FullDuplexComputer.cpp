#include <iostream>

#include "Queue.hpp"
#include "SerialPort.hpp"

const char* portName = "/dev/ttyUSB0";
const char* inputFileName = "input.txt";
const char* outputFileName = "output.txt";

int main() {
    Queues queues(portName);

    queues.openInputFile(inputFileName);
    queues.openOutputFile(outputFileName);

    usleep(5000000);

    char byteFromFile;
    while (queues.readByteFromFile(byteFromFile)) {
        queues.sendByte(static_cast<uint8_t>(byteFromFile));
    }
    queues.closeInputFile();
    queues.flush();

    while(true) {
        queues.send();

        queues.receive();

        queues.processReceive();
    }
}