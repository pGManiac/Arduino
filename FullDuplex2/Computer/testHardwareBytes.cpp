#include <iostream>
#include "Frame.hpp"

const char* portName = "/dev/ttyUSB0";

int main() {
            uint8_t i = 13;
            Frame frame1(i);
            std::cout << "Sent number: " << +frame1.data << " | ";
            std::cout << "Sent State: " << +frame1.frameState << " | ";
            Frame frame2(frame1.hardWareBytes);
            std::cout << "Hardware bytes: "
                      << static_cast<int>(frame1.hardWareBytes[0]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[1]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[2]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[3]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[4]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[5]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[6]) << ", "
                      << static_cast<int>(frame1.hardWareBytes[7]) << " | ";

            uint8_t zahl = frame2.data;

            std::cout << "Received number: " << static_cast<int>(zahl) << " | ";
            std::cout << "Received State: " << +frame2.frameState << " | ";
            std::cout << "Hardware bytes: "
                      << static_cast<int>(frame2.hardWareBytes[0]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[1]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[2]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[3]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[4]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[5]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[6]) << ", "
                      << static_cast<int>(frame2.hardWareBytes[7]) << "\n";
}

    //wenn ich das direkt gebe, printed er die 3, das passt
    //wenn ich es mit input mache, liest er es als character und für die 3 ist der numerische ascii wert 51
    //diese landet dann als byte im uint8_t data und wird weiter verarbeitet
    //die berechnung vor dem senden funktioniert erstmal wie erwartet
    //bei beiden kommt dasselbe falsche ergebnis raus
    //ist das zusammensetzen nach dem Empfangen das Problem?

