#include "SerialPort.hpp"
#include "Queue.hpp"
#include "Frame.hpp"

SerialPort::SerialPort(const char* portName) {
    // Open the serial port
    fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cerr << "Error opening serial port." << std::endl;
        // Handle the error
    }
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


void SerialPort::receiveByte() {
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);
    struct timeval timeout;
    timeout.tv_sec = 5; // 5 millisecs and...
    timeout.tv_usec = 0; // 0 microsecs
    //maybe put these first few lines somewhere more global...?
    int bytesAvailable = select(fd +1, &readSet, nullptr, nullptr, &timeout);
    /*
    if (ioctl(fd, FIONREAD, &bytesAvailable) == -1) {
        std::cerr << "Error checking bytes available in serial port.\n";
        return;
    }*/

    if (bytesAvailable == -1) {
        std::cerr << "error in select\n";
        return;
    } else if (bytesAvailable == 0) {
        if (bytesCounted >= 8) {
            bytesCounted = 0;
            std::cerr << "timeout, eight bytes were read\n";
        } else {
            //create and queue error frame, requesting resend
            clearBuffer();
            Frame errorFrame = Frame(false);
            //enqueue errorFrame
            std::cerr << "timeout, not enough bytes were read\n";
        }
    } else {
        ssize_t bytesRead = read(fd, &buffByte, 1);
        if(bytesRead == -1) {
            std::cerr << "Error reading from serial port.\n";
        } else {
            this->read_buf.push_back(buffByte);
            bytesCounted++;
        }
    }
}

void SerialPort::clearBuffer() {
    read_buf.clear();
}