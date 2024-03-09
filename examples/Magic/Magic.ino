#include <Bigbot.h>
#define Right    A0
#define Center   A1
#define Left     A2
#define Switch   A4
#define Velocidad 100

Bot bot(MAGIC);


void setup() {
  Serial.begin(9600);
  pinMode(Right, INPUT);
  pinMode(Center, INPUT);
  pinMode(Left, INPUT);
  pinMode(Switch , INPUT_PULLUP);
}

void loop() {
  bool state = bot.toggle(Switch);

  if (!state) {
    Serial.println("Modo Ultrasonido");
    bot.obstaculos(30, Velocidad);


  } else {
    Serial.println("Modo seguidor de linea");
    bot.seguidor(Left ,Center ,Right ,Velocidad);
  }
}