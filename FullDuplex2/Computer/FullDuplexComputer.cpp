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
        for (int i = 0; i < line.length(); i++) {
            character = line.at(i);
            queues.sendByte(character);
        }
    }
    
    /*
    std::cout << "Eingabe: ";
    std::getline(std::cin, eingabe);

    for (int i = 0; i < eingabe.length(); i++) {
        zeichen = eingabe.at(i);
        queues.sendByte(zeichen);
    }*/

    /**

    char byteFromFile;
    while (queues.readByteFromFile(byteFromFile)) {
        queues.sendByte(static_cast<uint8_t>(byteFromFile));
    }
    queues.closeInputFile();
    queues.flush();

     **/

    while(true) {
        queues.send();

        queues.receive();

        queues.processReceive();
    }
}