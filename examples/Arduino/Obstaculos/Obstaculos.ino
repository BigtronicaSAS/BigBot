#include <Bigbot.h>
#define MaximaDistancia 30

/*Velocidad Bigbot Magic: 255*/
#define Velocidad 255

/*Velocidad Bigbot 4WD: 180*/
// #define Velocidad 180 

Pinout BotARDUINO = {10, 12, 11, 13, 8, 7, 4};
//Pinout BotESP32 = {5, 19, 23, 18, 12, 14, 17};

Bot bot(BotARDUINO);
void setup() {
}

void loop() {
bot.obstaculos(MaximaDistancia, Velocidad); 
}