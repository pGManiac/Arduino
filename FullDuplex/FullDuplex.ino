const byte xorChecksum = 0b01010101;

struct Frame {
private:
  bool bitvector[16];
  byte frameState; //Least significant bits are used to code state: 00 = data 01 = ACK 11 = Error

public:
  Frame() {
    for(int i = 0; i < 16; i++) {
      bitvector[i] = false;
    }
  }
  Frame(byte data) {
    //Fill index 0 - 7 with bits from data byte, highest significant bit comes first
    for (int i = 7; i >=0; i--) {
            bitvector[i] = (data & (1 << i)) != 0;
        }
    //Fill index 8-15 with bits from checksum, highest significant bit comes first
    for (int i = 15; i>=8; i--) {
            bitvector[i] = (data ^ xorChecksum) & (1 << (i-8));
        }
    0 << frameState;
  }
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
