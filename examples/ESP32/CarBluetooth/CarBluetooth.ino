#include <Bigbot.h>
#include "Bluetooth.h"

BT bluetooth; 
Bot bot(BIGBOT_ESP32);

void setup()
{
 bluetooth.init();
}

void loop()
{
   bluetooth.car(bot, Velocidad);
}