#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>

int main() {
    const char *portName = "/dev/ttyUSB0";
    const speed_t baudRate = B9600;

    // Open the serial port
    int serialPort = open(portName, O_RDWR | O_NOCTTY);
    if (serialPort == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        return 1;
    }

    // Configure the serial port
    struct termios serialConfig;
    tcgetattr(serialPort, &serialConfig);
    cfsetospeed(&serialConfig, baudRate);
    cfsetispeed(&serialConfig, baudRate);
    serialConfig.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(serialPort, TCSANOW, &serialConfig);

    while (true) {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(serialPort, &readSet);

        // Set a timeout (1 second in this case)
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        // Wait for data to be available using select
        int result = select(serialPort + 1, &readSet, NULL, NULL, &timeout);

        if (result == -1) {
            std::cerr << "Error in select." << std::endl;
            break;
        } else if (result == 0) {
            // No data available within the timeout
            std::cout << "Nothing" << std::endl;
        } else {
            // Data is available, proceed to read
            char receivedByte;
            ssize_t bytesRead = read(serialPort, &receivedByte, 1);

            if (bytesRead == -1) {
                std::cerr << "Error reading from serial port." << std::endl;
                break;
            } else if (bytesRead == 0) {
                // This branch should not be reached with the select-based approach
                std::cerr << "Read nothing unexpectedly." << std::endl;
            } else {
                // Print the received byte
                std::cout << "Received: " << receivedByte << std::endl;
            }
        }

        // Add a delay if needed to avoid busy waiting
        // usleep(100000); // Sleep for 100 milliseconds
    }

    // Close the serial port
    close(serialPort);

    return 0;
}
