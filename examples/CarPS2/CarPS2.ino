#include <Bigbot.h>
#define pin_clock     A3
#define pin_command   A1
#define pin_attention A0
#define pin_data      A2
#define Velocidad 120
Bot bot(SOCCER);

void setup() {
  bot.controlPS2(pin_clock , pin_command, pin_attention, pin_data);
}

void loop() {
bot.carPS2(Velocidad); 
}