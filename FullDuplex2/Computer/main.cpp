#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    const char* portName = "/dev/ttyUSB0";
    const speed_t baudRate = B9600; // Adjust baud rate based on your configuration

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

    // Read and print data from the serial port
    char buffer[256];
    ssize_t bytesRead;

    while (true) {
        bytesRead = read(serialPort, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            // Process the received data as needed
            std::cout.write(buffer, bytesRead);
        }
    }

    // Close the serial port
    close(serialPort);

    return 0;
}