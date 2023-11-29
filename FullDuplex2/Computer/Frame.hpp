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
                         - 11: handshake request
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


    void calcBytesToBeSent() {
        if(frameState == 0) {

        } else if(frameState == 1) {

        } else if(frameState == 2) {

        }
    }

    void calcData() {
        //reconstruct data, checksum and frameState from byteArray
    }
};