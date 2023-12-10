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
Frame::Frame(uint8_t _data) : data(_data) {
        //Fill index 8-15 with bits from checksum, highest significant bit comes first
        checksum = _data ^ xorChecksum;
        0 << frameState;
        calcBytesToBeSent();
}

/**
     * @brief Parameterized constructor for a received frame.
     *
     * Creates a frame based on an array of received bytes (hardware from Arduino)
     *
     * @param _receivedBytes Array of received bytes.
     */
Frame::Frame(uint8_t _receivedBytes[8]) {
        for(uint8_t i = 0; i < 8; i++) {
            hardWareBytes[i] = _receivedBytes[i];
        }
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
    if(acknowledge) {
        data = 0b10011001;
        checksum = data ^ xorChecksum;
        frameState = 1;
        calcBytesToBeSent();
    } else {
        data = 0b01100110;
        checksum = data ^ xorChecksum;
        frameState = 2;
        calcBytesToBeSent();
    }
}

/**
     * @brief Calculate the hardware bytes to be sent based on the current frame state.
     *
     * This function calculates the hardware bytes to be sent based on the current frame state,
     * data, and checksum. The resulting hardware bytes are stored in the hardWareBytes array.
     */
void Frame::calcBytesToBeSent() {
    //highest significant bits first
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
        case 1:
            hardWareBytes[0] = 0x04 | ((data & 0xC0) >> 6);
            hardWareBytes[1] = 0x08 | ((data & 0x30) >> 4);
            hardWareBytes[2] = 0x0C | ((data & 0x0C) >> 2);
            hardWareBytes[3] = 0x08 | ((data & 0x03));

            hardWareBytes[4] = 0x0C | ((checksum & 0xC0) >> 6);
            hardWareBytes[5] = 0x08 | ((checksum & 0x30) >> 4);
            hardWareBytes[6] = 0x0C | ((checksum & 0x0C) >> 2);
            hardWareBytes[7] = 0x08 | ((checksum & 0x03));
            break;
            /*case 2: //case for error technically redundant
                hardWareBytes[0] = (data & 0xC0) >> 6;
                hardWareBytes[1] = (data & 0x30) >> 4;
                hardWareBytes[2] = (data & 0x0C) >> 2;
                hardWareBytes[3] = (data & 0x03);

                hardWareBytes[4] = (checksum & 0xC0) >> 6;
                hardWareBytes[5] = (checksum & 0x30) >> 4;
                hardWareBytes[6] = (checksum & 0x0C) >> 2;
                hardWareBytes[7] = (checksum & 0x03);*/
    }
}


/**
     * @brief Reconstruct data, checksum, and frame state from the hardware byte array.
     *
     * This function reconstructs data, checksum, and frame state from the provided hardware byte array.
     */
void Frame::calcData() {
    //reconstruct data, checksum and frameState from byteArray
    for (uint8_t i = 0; i < 4; ++i) {
        data |= ((hardWareBytes[i] & 0x03) << (6-(i*2)));
        checksum |= ((hardWareBytes[i+4] & 0x03) << (6-(i*2)));
    }
    if ((data ^ xorChecksum) != checksum) {
        frameState = 0x03;
    } else {
        switch (hardWareBytes[0] & 0x0C) {
            case 0x0C:
                frameState = 0x00;
            case 0x04:
                if (data == 0x99) {
                    frameState = 0x01;
                } else {
                    frameState = 0x02;
                }
        }
    }
}