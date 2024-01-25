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

    usleep(5000000);

    std::vector<uint8_t> binaryData;
    uint8_t character;

    // Read binary input from standard input (stdin)
    std::cin >> std::noskipws;  // Prevent skipping white spaces, treat everything as input
    std::istream_iterator<uint8_t> begin(std::cin);
    std::istream_iterator<uint8_t> end;
    binaryData.assign(begin, end);

    for (const auto& i : binaryData) {
        character = i;
        queues.sendByte(character);
    }

    /*std::string line;
    uint8_t character;

    // Read input from standard input (stdin)
    while (std::getline(std::cin, line)) {
        for (char i : line) {
            character = i;
            queues.sendByte(character);
        }
    }*/

    queues.sendFin("fin");

    while((queues.isReceivedFIN() == 0) || (queues.isSentFIN() == 0) || (queues.isSendingQueueReadyToSend() == 0)) {
        queues.send();

        queues.receive();

        queues.processReceive();
    }
    return 0;
}