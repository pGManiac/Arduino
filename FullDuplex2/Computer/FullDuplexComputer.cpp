#include <iostream>

#include "Queue.hpp"
#include "SerialPort.hpp"
#include <iterator>

const char* portName = "/dev/ttyUSB0";
const char* inputFileName = "input.txt";
const char* outputFileName = "output.txt";


int main() {
    Queues queues(portName);

    usleep(5000000);

    // Record the start time
    auto startTime = std::chrono::high_resolution_clock::now();

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

    // Record the end time
    auto endTime = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    // Open a file for writing
    std::ofstream outputFile("execution_time.txt");

    // Check if the file is open before writing
    if (outputFile.is_open()) {
        // Write the execution time to the file
        outputFile << "Execution time: " << duration.count() << " milliseconds" << std::endl;

        // Close the file
        outputFile.close();
    } else {
        // Handle the case where the file couldn't be opened
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
        return 1;  // Return an error code
    }





    //std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;


    return 0;
}