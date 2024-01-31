#ifndef Bluetooth_h
#define Bluetooth_h

#include "BluetoothSerial.h"
#include "Bigbot.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

class BT : public BluetoothSerial
{
public:
    BT();
    void init();
    void car(Bot &bot, int velocidad);

private:
};

#endif