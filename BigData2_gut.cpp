#include <iostream>
#include <b15f/b15f.h>
#include <string>
#include <cstring>

void uint8_t_to_binary(uint8_t intToBinary);

std::string uint8_t_to_binary_re(uint8_t intToBinary);

int createChecksum(std::string inputStr);

int main(){

    B15F& drv = B15F::getInstance();
    drv.setRegister(&DDRA, 0xFF);
    drv.setRegister(&PORTA, 0x00);
    drv.setRegister(&DDRA, 0x0F);

    // Input
    std::string input;
    std::string file;
    //std::getline(std::cin, input);
    while(std::getline(std::cin, input))
    {
      file += input;
      file.push_back('\n');
    }

    std::cerr << "Input string: " << file << std::endl;

    // input to char
    std::vector<char> inputChar(file.begin(), file.end());

    // char to uint8
    uint8_t inputU8;
    uint8_t inputTop;
    uint8_t inputBottom;
    uint8_t outputU8;
    uint8_t outputTop;
    uint8_t outputBottom;
    uint8_t message = 0x00;
    int counter = 0;
    int rest;
    bool readToggle = true;
    bool setToggle;
    uint8_t start;
    int element = 0;
    int rest2 = 0;
    int run = 1;

    int rest3;
    bool switchToCheck = false;

    int dataCounter = 0;

    uint8_t checksumU8;
    std::vector<uint8_t> buffer;


    while(run == 1)
    {
    try{
      rest3 = (counter + 1) % 10;
      rest2 = counter % 40;
      rest = counter % 2;
      start = 0x00;
      element = dataCounter / 2;

      if(rest3 == 9)
      {
        switchToCheck = true;
      }

      if(element <= inputChar.size())
      {
        inputU8 = inputChar[element];
      }else
      {
        inputU8 = 0x03;
      }

      if(rest2 == 0)
      {

          do{
              start = drv.getRegister(&PINA) & 0xF0;
              drv.delay_ms(20);
              std::cerr << std::endl;
              std::cerr << uint8_t_to_binary_re(start) << std::endl;
              if(start == 0xF0)
              {
                drv.setRegister(&PORTA, 0x0F);
                //drv.delay_ms();
              }
            }while(start != 0xF0);
        }

      drv.delay_ms(50);
      //Senden
      if(switchToCheck == false)
      {
          dataCounter++;
          if(rest == 0)
          {
              inputTop = (inputU8 & 0xF0) >> 4;
              drv.setRegister(&PORTA, inputTop);
              //std::cout << "SeTop: " << uint8_t_to_binary_re(inputTop) << std::endl;
              //uint8_t_to_binary(inputTop);
          }else if(rest == 1)
          {
              inputBottom = (inputU8 & 0x0F);
              drv.setRegister(&PORTA, inputBottom);
              //std::cout << "SeBot:" << uint8_t_to_binary_re(inputBottom) << std::endl;
          }
      }else if(switchToCheck == true)
      {
        std::string last4ElementsToCheck = "";
        for(int i = element - 4; i <= element - 1; i++)
        {
            //std::cout << i << " " << element << std::endl;
           last4ElementsToCheck += inputChar[i];
        }
        //std::cout << "String: " << last4ElementsToCheck << std::endl;
        checksumU8 = createChecksum(last4ElementsToCheck);

        checksumU8 = (checksumU8 & 0x0F);
        drv.setRegister(&PORTA, checksumU8);

        std::cerr << std::endl;
        std::cerr << "SendChecksum: " << uint8_t_to_binary_re(checksumU8) << std::endl;
      }

      //Lesen
      drv.delay_ms(50);
      message = drv.getRegister(&PINA) & 0xF0;
      //std::cout << "Message: " << uint8_t_to_binary_re(message) << std::endl;

      if(switchToCheck == false)
      {
          if(rest == 0)
          {
              outputTop = message;
              //uint8_t_to_binary(outputTop);
              //std::cout << "ReTop: " << uint8_t_to_binary_re(outputTop) << std::endl;
              message = 0x00;

          }else if(rest == 1)
          {
              outputBottom = message;
              outputU8 = outputTop | (outputBottom >> 4);

              /*if(outputU8 != 0x03){
               std::cout << outputU8 << std::flush;
             }*/
             buffer.push_back(outputU8);
              //std::cout << "ReBot:" << uint8_t_to_binary_re(outputBottom) << std::endl;
              //std::cout << outputU8 << std::endl;
              //uint8_t_to_binary(outputU8);
              message = 0x00;
              outputBottom = 0x00;
              outputTop = 0x00;
          }
      }else if(switchToCheck == true)
      {
        uint8_t sentChecksum = 0x00;
        std::string checkBuffer = "";
        uint8_t checksumBuffer = 0x00;

        sentChecksum = message;// drv.getRegister(&PINA) & 0x0F;

        for(int i = 0; i < buffer.size(); i++)
        {
          char tempChar = buffer[i];
          checkBuffer += tempChar;
        }

        checksumBuffer = createChecksum(checkBuffer);
        std::cerr << "ReadChecksum: " << uint8_t_to_binary_re((sentChecksum >> 4)) << std::endl;
        std::cerr << "Buffer: " << uint8_t_to_binary_re(checksumBuffer) << std::endl;
        std::cerr << "ReceivedBlock: " << std::flush;
        //std::cout << "ReceivedBlock: " << std::flush;
        if((sentChecksum >> 4) == checksumBuffer)
        {
          for(int i = 0; i < buffer.size(); i++)
          {
            std::cout << buffer[i] << std::flush;
          }
        }else if((sentChecksum >> 4) != checksumBuffer)
        {
          std::cerr << "Fehler!" << std::endl;
        }

        buffer.clear();
        switchToCheck = false;
        message = 0x00;
        counter = counter + 1;
      }

      if((outputU8 == 0x03) && (element > inputChar.size()))
      {
          std::cerr << " Programm beendet!" << std::endl;
          run = 0;
      }

      //std::cout << std::endl;
      drv.delay_ms(40);
      //drv.setRegister(&PORTA, 0x00);
      outputU8 = 0x00;
    }
    catch(...)
    {
      std::cerr << " Bf15 hat Probleme. " << std::endl;
    }

    counter++;
    }

    drv.setRegister(&PORTA, 0);
    return 0;
}

// convert uint8_t to binary string
void uint8_t_to_binary(uint8_t intToBinary)
{
    int tempInt = intToBinary;
    std::string tempStr = std::bitset<8>(tempInt).to_string();
    //std::cout << tempStr << std::endl;
    std::cout << tempStr << std::endl;
}

std::string uint8_t_to_binary_re(uint8_t intToBinary)
{
    int tempInt = intToBinary;
    std::string tempStr = std::bitset<8>(tempInt).to_string();
    //std::cout << tempStr << std::endl;
    return tempStr;
}

int createChecksum(std::string inputStr)
{
    std::vector<std::string> achtBit1;
    std::string crcFrame = "";
    std::string generatorpolynom = "10101";
    int intChecksum;
    int index = 0;

    //String in 8 bit umwandeln und Vektor erstellen
    for(int i = 0; i < inputStr.length(); i++) {
        std::bitset<8> bsLineInput(inputStr[i]);
        std::string zeichen = bsLineInput.to_string();
        achtBit1.push_back(zeichen);
    }

    //8 bit Vektor zu einem langen Frame zusammenfügen
    for(int i = 0; i < achtBit1.size(); i++) {
        crcFrame += achtBit1[i];
    }

    //Ergänzung des Frames mit n = 4 Nullen
    for(int i = 0; i < generatorpolynom.length() -1; i++) {
        crcFrame += "0";
    }

    //führende Nullen löschen
    crcFrame.erase(0, crcFrame.find_first_not_of('0'));

    //CRC-Prüfsumme generieren durch XOR mit Generatorpolynom
    while(crcFrame.length() >= generatorpolynom.length()) {
        if(crcFrame[index] == generatorpolynom[index]) {
            crcFrame.replace(index, 1, "0");
            index++;
        } else {
            crcFrame.replace(index, 1, "1");
            index++;
        }
    //Löschen der führenden Nullen, sobald letztes Bit des Generatorpolynoms erreicht wurde
        if(index == generatorpolynom.length()) {
            crcFrame.erase(0, crcFrame.find_first_not_of('0'));
            index = 0;
        }
    }
    //CRC Prüfsumme mit Nullen aufstocken, wenn n < 5
    while(crcFrame.length() < generatorpolynom.length() - 1) {
        int i = 0;
        crcFrame.insert(i, "0");
        i++;
    }
    //convert binary checksum to int checksum
    intChecksum = std::stoi(crcFrame, nullptr, 2);
    return intChecksum;
}


        /*cout << "Schreibe 0" << endl;
        drv.setRegister(&PORTA, 0);
        cout << "Schreibe " << zahl << endl; //uint8_t würde fehlerhaft wiedergegeben
        drv.setRegister(&PORTA, intToU8);

        cout << (((int)drv.getRegister(&PINA) & 0xF0) >> 4) << endl;
        drv.delay_ms(300);*/
