#include <iostream>

#include "Queue.hpp"
#include "SerialPort.hpp"

const char* portName = "/dev/ttyUSB0";

int main() {
    uint8_t number;



    Queues queues(portName);
    queues.configureSerialPort();

    usleep(5000000);
    std::cout << "Enter a number to be sent\n";
    std::cin >> number;

    queues.sendByte(number);

    while(true) {
        queues.send();
        queues.receive();
        queues.processReceive();
    }
}
