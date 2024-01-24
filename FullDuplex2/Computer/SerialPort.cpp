#include "SerialPort.hpp"
#include "Queue.hpp"
#include "Frame.hpp"

/**
 * @brief Constructor for the SerialPort class.
 *
 * Opens the specified serial port and initializes member variables.
 *
 * @param _portName The name of the serial port device.
 */
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

/**
 * @brief Destructor for the SerialPort class.
 *
 * Closes the serial port upon object destruction.
 */
SerialPort::~SerialPort() {
    // Close the serial port
    close(fd);
}

/**
 * @brief Configures the serial port settings.
 *
 * Configures the baud rate and other settings for the serial port.
 */
void SerialPort::configure() {
    struct termios serialConfig;
    tcgetattr(fd, &serialConfig);
    cfsetospeed(&serialConfig, 9600);
    cfsetispeed(&serialConfig, 9600);
    serialConfig.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(fd, TCSANOW, &serialConfig);
}

/**
 * @brief Flushes the input and output buffers of the serial port.
 */
void SerialPort::flush() const {
    // Flush both input and output buffers
    if (tcflush(fd, TCIOFLUSH) != 0) {
        std::cerr << "Error flushing serial port.\n";
        // Handle the error
    }
}


/**
 * @brief Sends an array of bytes through the serial port.
 *
 * @param data A pointer to the array of bytes to be sent.
 * @param size The size of the array of bytes.
 */
void SerialPort::sendBytes(const uint8_t* data , size_t size) {
    if (data == nullptr) {
        std::cerr << "Error: Null pointer in SerialPort::sendBytes.\n";
        return;
    }
    if (write(fd, data, size) == -1) {
        std::cerr << "Error writing to serial port.\n";
    }
}

/**
 * @brief Receives 8 bytes from the serial port.
 *
 * Checks for the availability of bytes in the serial port, sleeps for a short duration,
 * then reads 8 bytes if available and updates member variables accordingly.
 */
void SerialPort::receive8Bytes() {
    ioctl(fd, FIONREAD, &bytesAvailable);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //std::cout << "Bytes available:" << bytesAvailable << "\n";
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
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                //std::cout << "Bin in else if\n";
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

/**
 * @brief Marks the buffer as not available.
 *
 * Resets the flag indicating that there are bytes available in the serial port buffer.
 */
void SerialPort::makeBufferNotAvailable() {
    availableBuffer = false;
}