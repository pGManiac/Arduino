#include <iostream>

#include "Queue.hpp"



#include "SerialPort.hpp"

int main() {
    const char* portName = "/dev/ttyUSB0";
    uint8_t number;

    SerialPort serial(portName);
    serial.configure();
    usleep(5000000);

    Queues queues;

    std::cout << "Enter a number to be sent\n";
    std::cin >> number;

    queues.sendByte(number);

    while(true) {
        queues.send();
        queues.receive();
        queues.processReceive();

    }
}
