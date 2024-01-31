#ifndef Bluetooth_h
#define Bluetooth_h

#include <SoftwareSerial.h>
#include "Bigbot.h" 

class BT : public SoftwareSerial {
public:
    BT(int pin_TX, int pin_RX);
    void init();
    void car(Bot &bot, int velocidad);

private:
    int pin_TX;
    int pin_RX;
};

#endif