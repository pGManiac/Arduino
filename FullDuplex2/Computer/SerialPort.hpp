#pragma once

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>
#include <sys/ioctl.h>
#include <vector>


class SerialPort {
private:
    int fd;  // File descriptor for the serial port
    std::vector<uint8_t> read_buf;
    uint8_t buffByte;

public:
    SerialPort(const char* portName);
    ~SerialPort();

    void configure();
    void sendBytes(const uint8_t*, size_t);
    void receive8Bytes();
    [[nodiscard]] const std::vector<uint8_t>& getReadBuffer() const {return read_buf;}
};