#include <iostream>
#include "Frame.hpp"

const char* portName = "/dev/ttyUSB0";

int main() {

    uint8_t number = 0x03;
    /*std::cout << "Enter a number to be sent\n";
    std::cin >> number;*/

    Frame frame1(number);
    std::cout << "Sent number" << +frame1.data << "\n";
    Frame frame2(frame1.hardWareBytes);
    uint8_t zahl = frame2.data;

    std::cout << "Received number" << zahl << "\n";

    //wenn ich das direkt gebe, printed er die 3, das passt
    //wenn ich es mit input mache, liest er es als character und für die 3 ist der numerische ascii wert 51
    //diese landet dann als byte im uint8_t data und wird weiter verarbeitet
    //die berechnung vor dem senden funktioniert erstmal wie erwartet
    //bei beiden kommt dasselbe falsche ergebnis raus
    //ist das zusammensetzen nach dem Empfangen das Problem?
}
