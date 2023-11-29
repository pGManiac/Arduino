#include <iostream>

#include "Queue.hpp"

Queues queues;


int main() {
    if(!queues.arduino.is_open()) {
        std::cout << "Error: Couldn´t open the serial port. \n";
        return -1;
    }
    while (true) {

    }

}