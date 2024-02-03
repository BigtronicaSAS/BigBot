#include <Bigbot.h>
#include "PS3.h"
#define Velocidad 255

Bot bot(BIGBOT_ARDUINO);
void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

void setup()
{
  setUpPinModes();
  Serial.begin(115200);
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisConnect);
  Ps3.begin();
  Serial.println("Ready.");
}

void loop()
{
  PS3.car(bot, Velocidad);
}