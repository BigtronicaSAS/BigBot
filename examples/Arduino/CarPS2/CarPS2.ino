#include <Bigbot.h>
#include "PS2.h"
#define Velocidad 255

Command PS2;
Bot bot(BIGBOT_ESP32);

void setup() {
  PS2.init();
}

void loop() {
PS2.car(bot,Velocidad); 
}