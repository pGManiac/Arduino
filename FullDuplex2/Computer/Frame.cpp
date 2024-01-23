#include "Frame.hpp"

/**
      * @brief Default constructor.
      *
      * Initializes all bits to 0;
      */
Frame::Frame() {
}

/**
       * @brief Parameterized constructor.
       *
       * Creates a data Frame based on the provided data byte.
       *
       * @param data The data byte used to construct the frame.
       */
Frame::Frame(const uint8_t _data) : data(_data) {
        //Fill index 8-15 with bits from checksum, highest significant bit comes first
        checksum = _data ^ xorChecksum;
        frameState = 0x00;
        calcBytesToBeSent();
}

/**
     * @brief Parameterized constructor for a received frame.
     *
     * Creates a frame based on an array of received bytes (hardware from Arduino)
     *
     * @param _receivedBytes Array of received bytes.
     */
Frame::Frame(const uint8_t* _receivedBytes) {
        for(uint8_t i = 0; i < 8; i++) {
            hardWareBytes[i] = _receivedBytes[i];
        }
    //std::cout << "HARDWARE constructor\n";

    calcData();
}

/**
     * @brief Constructor for ACK or Error frames.
     *
     * Creates an ACK or Error frame based on the acknowledge parameter.
     *
     * @param acknowledge Boolean indicating if it's an ACK frame (true) or Error frame (false).
     */
Frame::Frame(bool acknowledge) {
    //std::cout << "BOOLEAN constructor\n";

    if(acknowledge) {
        std::cout << "created ack frame\n";
        data = 0b10011001;
        checksum = data ^ xorChecksum;
        frameState = 1;
        calcBytesToBeSent();
    } else {
        std::cout << "created an error frame\n";
        data = 0b01100110;
        checksum = data ^ xorChecksum;
        frameState = 2;
        calcBytesToBeSent();
    }
}

Frame::Frame(const std::string fin) {
    if(fin == "fin") {
        std::cout << "created fin frame\n";
        data = 0b01010101;
        checksum = data ^ xorChecksum;
        frameState = 3;
        calcBytesToBeSent();
    } else {
        std::cerr << "Illegal frame in fin constructor\n";
    }
}

/**
     * @brief Calculate the hardware bytes to be sent based on the current frame state.
     *
     * This function calculates the hardware bytes to be sent based on the current frame state,
     * data, and checksum. The resulting hardware bytes are stored in the hardWareBytes array.
     * It uses a number of different bit operations: extracting bits to be sent, shifting them
     * to the least significant position and combining them with clock and frame bit to a byte.
     */
void Frame::calcBytesToBeSent() {
    //highest significant bits first
    //std::cout << "Sent this data: " << static_cast<int>(data) << "\n";
    switch (frameState) {
        case 0:
            hardWareBytes[0] = 0x0C | ((data & 0xC0) >> 6);
            hardWareBytes[1] = 0x00 | ((data & 0x30) >> 4);
            hardWareBytes[2] = 0x04 | ((data & 0x0C) >> 2);
            hardWareBytes[3] = 0x00 | ((data & 0x03));

            hardWareBytes[4] = 0x04 | ((checksum & 0xC0) >> 6);
            hardWareBytes[5] = 0x00 | ((checksum & 0x30) >> 4);
            hardWareBytes[6] = 0x04 | ((checksum & 0x0C) >> 2);
            hardWareBytes[7] = 0x00 | ((checksum & 0x03));
            break;
        default:
            hardWareBytes[0] = 0x04 | ((data & 0xC0) >> 6);
            hardWareBytes[1] = 0x08 | ((data & 0x30) >> 4);
            hardWareBytes[2] = 0x0C | ((data & 0x0C) >> 2);
            hardWareBytes[3] = 0x08 | ((data & 0x03));

            hardWareBytes[4] = 0x0C | ((checksum & 0xC0) >> 6);
            hardWareBytes[5] = 0x08 | ((checksum & 0x30) >> 4);
            hardWareBytes[6] = 0x0C | ((checksum & 0x0C) >> 2);
            hardWareBytes[7] = 0x08 | ((checksum & 0x03));
            break;
    }
}


/**
     * @brief Reconstruct data, checksum, and frame state from the hardware byte array.
     *
     * This function reconstructs data, checksum, and frame state from the provided hardware byte array.
     * It uses a number of different bit operations: extracting the least significant bits, shifting
     * them to their respective position in the final byte and setting them in data or checksum, while
     * leaving the previously set bits untouched.
     */
void Frame::calcData() {
    //reconstruct data, checksum and frameState from byteArray
    data = 0x00;
    checksum = 0x00;
    for (uint8_t i = 0; i < 4; i++) {
        data |= ((hardWareBytes[i] & 0x03) << (6-(i*2)));
        checksum |= ((hardWareBytes[i+4] & 0x03) << (6-(i*2)));
    }
    if ((data ^ xorChecksum) != checksum) {
        frameState = 0x04;
    } else {
        switch (hardWareBytes[0] & 0x0C) {
            case 0x0C:
                frameState = 0x00;
                break;
            case 0x04:
                if (data == 0x99) {
                    frameState = 0x01;
                    //std::cout << "Ich habe einen ACK erstellt\n";
                } else if (data == 0x66) {
                    frameState = 0x02;
                    std::cout << "Ich habe einen Error erstellt\n";
                } else {
                    frameState = 0x03;
                    std::cout << "Ich habe einen Fin erstellt\n";
                }
                break;
        }
    }
}