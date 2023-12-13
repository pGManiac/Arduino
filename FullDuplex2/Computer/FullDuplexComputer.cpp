#include <iostream>

#include "Queue.hpp"
#include "SerialPort.hpp"

const char* portName = "/dev/ttyUSB0";
const char* inputFileName = "input.txt";
const char* outputFileName = "output.txt";

int main() {
    Queues queues(portName);

    //open input file
    std::ifstream inputFile(inputFileName, std::ios::in | std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // open output file
    std::ofstream outputFile(outputFileName, std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    usleep(5000000);

    char byteFromFile;
    while (inputFile.get(byteFromFile)) {
        queues.sendByte(static_cast<uint8_t>(byteFromFile));
    }
    inputFile.close();

    /*
    uint8_t number;
    std::cout << "Enter a number to be sent\n";
    std::cin >> number;

    queues.sendByte(number);
    std::cout << "Sent number" << number << "\n";
    */

    while(true) {
        queues.send();

        queues.receive();

        queues.processReceive(outputFile);
    }
}
