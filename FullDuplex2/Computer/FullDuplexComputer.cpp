#include <iostream>
#include <fstream>

#include "Frame.hpp"

int main() {
    std::ofstream arduino("/dev/ttyUSB0");
    if(!arduino.is_open()) {
        std::cout << "Error: Couldn´t open the serial port. \n";
        return -1;
    }

}