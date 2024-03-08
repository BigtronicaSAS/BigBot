#include <Bigbot.h>
#define MaximaDistancia 30

/*Velocidad Bigbot Magic: 255*/
#define Velocidad 255

/*Velocidad Bigbot 4WD: 180*/
// #define Velocidad 180 

Bot bot(MAGIC);
void setup() {
}

void loop() {
bot.obstaculos(MaximaDistancia, Velocidad); 
}