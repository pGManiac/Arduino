#include <iostream>

#include "Queue.hpp"



int main()
{
    uint8_t data = 10;

    FILE *file;
    file = fopen("/dev/ttyUSB0", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1; // Exit with an error code
    }
    for(int i = 0; i < 10; i++) {
        fprintf(file, "%d", data);
    }
    fclose(file);
}