#include <iostream>

#include "Queue.hpp"
#include "SerialPort.hpp"

const char* portName = "/dev/ttyUSB0";

int main() {
    uint8_t number;



    Queues queues(portName);

    usleep(5000000);
    std::cout << "Enter a number to be sent\n";
    std::cin >> number;

    queues.sendByte(number);
    std::cout << "Sent number" << number << "\n";

    while(true) {
        queues.send();
        queues.receive();

        queues.receiveByte();
        queues.receiveByte();
        queues.receiveByte();
        queues.receiveByte();
        queues.receiveByte();
        queues.receiveByte();
        queues.receiveByte();
        queues.receiveByte();

        queues.processReceive();
    }
}
