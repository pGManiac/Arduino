#pragma once

#include <cstdint>

const uint8_t xorChecksum = 0b01010101;

/**
 * @brief Represents a frame with bit vector and state information.
 *
 * The Frame struct encapsulates a data frame with a byte for data, a byte for checksum and a byte for Data/Ack/Error
 */
struct Frame {
    uint8_t data;
    uint8_t checksum;
    uint8_t frameState; /**< Frame state indicating data, ACK, or Error.
                         - 00: Data
                         - 01: ACK
                         - 10: Error
                         - 11: fail state
                     */
    uint8_t hardWareBytes[8];

    /**
      * @brief Default constructor.
      *
      * Initializes all bits to 0;
      */
    Frame() {
    }

    /**
       * @brief Parameterized constructor.
       *
       * Creates a data Frame based on the provided data byte.
       *
       * @param data The data byte used to construct the frame.
       */
    Frame(uint8_t _data) : data(_data) {
        //Fill index 8-15 with bits from checksum, highest significant bit comes first
        checksum = _data ^ xorChecksum;
        0 << frameState;
        calcBytesToBeSent();
    }

    Frame(uint8_t _receivedBytes[8]) {
        for(uint8_t i = 0; i < 8; i++) {
            hardWareBytes[i] = _receivedBytes[i];
        }
        calcData();
    }

    /**
 * @brief Calculate the hardware bytes to be sent based on the current frame state.
 *
 * This function calculates the hardware bytes to be sent based on the current frame state,
 * data, and checksum. The resulting hardware bytes are stored in the hardWareBytes array.
 * For every byte in the array, the respective bits to be sent are filtered and combined to
 * a new byte with the frame and clock bit.
 *
 * The calculation is done with the highest significant bits first.
 */
    void calcBytesToBeSent() {
        //highest significant bits first
        switch(frameState) {
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
 * The reconstructed values are stored in the data, checksum, and frameState variables.
 * Data and checksum are reconstructed by again extracting the data bits from the bytes in the array
 * and shifting them to the correct position before setting them in the respective frame variable.
 */
    void calcData() {
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
};