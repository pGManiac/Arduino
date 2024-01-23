#pragma once

#include <cstdint>
#include <iostream>

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
                         - 11: Fin
                         - 100: Fail State
                     */
    uint8_t hardWareBytes[8];

    Frame();

    Frame(uint8_t);

    Frame(const uint8_t*);

    Frame(bool);

    Frame(char);

    void calcBytesToBeSent();

    void calcData();
};