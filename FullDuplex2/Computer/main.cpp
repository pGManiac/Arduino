#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>

int main() {
    const char *portName = "/dev/ttyUSB0";
    const speed_t baudRate = B9600;

    // Open the serial port
    int serialPort = open(portName, O_RDWR | O_NOCTTY);
    if (serialPort == -1) {
        std::cerr << "Error opening serial port: " << std::endl;
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
    char _buffer[256];
    ssize_t bytesRead;

    const char buffer[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    const int bufferSize = sizeof(buffer);

    /**
    while (true) {
        ssize_t bytesWritten = write(serialPort, buffer, bufferSize);

        if (bytesWritten == -1) {
            std::cerr << "Error writing to serial port.\n";
            // Handle the error if needed
        } else {
            std::cout << "Bytes written: " << bytesWritten << "\n";
        }

        // Add a delay if needed
        usleep(1000000); // 1 second delay
    }
    **/

    while (true) {
        // Use ioctl to get the number of bytes available for reading
        int bytesAvailable;
        if (ioctl(serialPort, FIONREAD, &bytesAvailable) == -1) {
            std::cerr << "Error checking bytes available in serial port." << std::endl;
            return 1;
        }

        // Print the number of bytes available
        std::cout << "Bytes available: " << bytesAvailable << "\n";

        // Add a delay to avoid busy-waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}