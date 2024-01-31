#include <Bigbot.h>
#include "PS2.h"
#define Velocidad 255

Command PS2;
Bot bot(BIGBOT_ARDUINO);

void setup() {
  PS2.init();
}

void loop() {
PS2.car(bot,Velocidad); 
}