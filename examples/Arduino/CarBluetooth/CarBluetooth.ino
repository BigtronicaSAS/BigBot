#include <Bigbot.h>
#include "Bluetooth.h"
#define Velocidad 255

BT bluetooth(0, 1);
Bot bot(BIGBOT_ARDUINO);

void setup()
{
  bluetooth.init();
}

void loop()
{
  bluetooth.car(bot, Velocidad);
}