#include "SerialPort.hpp"
#include "Queue.hpp"
#include "Frame.hpp"

SerialPort::SerialPort(const char* _portName) {
    // Open the serial port
    fd = open(_portName, O_RDWR | O_NOCTTY);
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
    tcgetattr(fd, &serialConfig);
    cfsetospeed(&serialConfig, 9600);
    cfsetispeed(&serialConfig, 9600);
    serialConfig.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(fd, TCSANOW, &serialConfig);
}

void SerialPort::flush() const {
    // Flush both input and output buffers
    if (tcflush(fd, TCIOFLUSH) != 0) {
        std::cerr << "Error flushing serial port.\n";
        // Handle the error
    }
}


void SerialPort::sendBytes(const uint8_t* data , size_t size) {
    std::cout << "Sent: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << static_cast<int>(data[i]) << " ";
    }
    std::cout << "\n";
    if (write(fd, data, size) == -1) {
        std::cerr << "Error writing to serial port.\n";
    }
}

void SerialPort::receive8Bytes() {
    ioctl(fd, FIONREAD, &bytesAvailable);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Bytes available:" << bytesAvailable << "\n";
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
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "Bin in else if\n";
                receive8Bytes();
            } else {
                for (uint8_t & i : buffByte) {
                    i = 0   ;
                }
                std::cout << "Nicht genug bytes bekommen -> Fail hardwarebytes erstellen\n";
                fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
                char trashbuffer[8];
                read(fd, trashbuffer, sizeof(trashbuffer));
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