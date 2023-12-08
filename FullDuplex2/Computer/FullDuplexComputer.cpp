#include <iostream>

#include "Queue.hpp"



#include "SerialPort.hpp"

int main() {
    const char* portName = "/dev/ttyUSB0";

    SerialPort serial(portName);

    // Configure the serial port
    serial.configure();
    usleep(5000000);

    // Test sending data to Arduino
    const uint8_t sendData = 0xFF;
    serial.sendByte(&sendData, sizeof(sendData));

    // Wait for a moment to ensure Arduino has processed the data
    usleep(1000000);  // Sleep for 1 second

    return 0;
}
