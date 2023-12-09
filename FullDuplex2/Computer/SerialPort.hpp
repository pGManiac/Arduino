#pragma once

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>
#include <sys/ioctl.h>


class SerialPort {
private:
    int fd;  // File descriptor for the serial port
    uint8_t read_buf[8];
public:
    SerialPort(const char* portName);
    ~SerialPort();

    void configure();
    void sendBytes(const uint8_t*, size_t);
    void receive8Bytes();
};