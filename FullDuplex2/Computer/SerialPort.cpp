#include "SerialPort.hpp"
#include "Queue.hpp"
#include "Frame.hpp"

SerialPort::SerialPort(const char* _portName) {
    // Open the serial port
    fd = open(_portName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        // Handle the error
    }
    bytesAvailable = 0;
    bytesAvailableLast = 0;
    availableBuffer = false;
}

SerialPort::~SerialPort() {
    // Close the serial port
    close(fd);
}

void SerialPort::configure() {
    struct termios serialConfig;

    // Get the current serial port configuration
    if (tcgetattr(fd, &serialConfig) != 0) {
        std::cerr << "Error getting current serial port configuration.,\n";
        return;
    }

    // Set the input and output baud rate to 9600
    cfsetispeed(&serialConfig, B9600);
    cfsetospeed(&serialConfig, B9600);

    // Set data bits to 8
    serialConfig.c_cflag &= ~CSIZE; //clears existing CSIZE bits
    serialConfig.c_cflag |= CS8;

    // Disable hardware flow control, aka RTS/CTS
    serialConfig.c_cflag &= ~CRTSCTS;

    // Set parity to no parity
    serialConfig.c_cflag &= ~PARENB;
    serialConfig.c_cflag &= ~CSTOPB;

    // Disable software flow control
    serialConfig.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Set raw input
    serialConfig.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Set raw output
    serialConfig.c_oflag &= ~OPOST;

    // Apply the configuration
    if (tcsetattr(fd, TCSAFLUSH, &serialConfig) != 0) {
        std::cerr << "Error configuring serial port.\n";
    }
}


void SerialPort::sendBytes(const uint8_t* data , size_t size) {
    if (write(fd, data, size) == -1) {
        std::cerr << "Error writing to serial port.\n";
    }
}

void SerialPort::receive8Bytes() {
    bytesAvailable = ioctl(fd, FIONREAD, &bytesAvailable);
    switch(bytesAvailable) {
        case -1:
            std::cerr << "Error checking bytes available in serial port.\n";
            break;
        case 0:
            break;
        default:
            if(bytesAvailable >= 8) {
                read(fd, &buffByte, 8);
                bytesAvailable = 0;
                bytesAvailableLast = 0;
                availableBuffer = true;
                break;
            } else if (bytesAvailable > bytesAvailableLast){
                bytesAvailableLast = bytesAvailable;
                receive8Bytes();
            } else {
                for (uint8_t & i : buffByte) {
                    i = 0;
                }
                fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
                char buffer[8];
                read(fd, buffer, sizeof(buffer));
                availableBuffer = true;
                bytesAvailable = 0;
                bytesAvailableLast = 0;
                fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);
                break;
            }
    }

}

void SerialPort::makeBufferNotAvailable() {
    availableBuffer = false;
}