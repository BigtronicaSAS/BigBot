#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PS2.h"

Command::Command(){
pin_clock =  A3;
pin_command = A1;
pin_attention = A0;
pin_data = A2;
}


void Command::init(){
  int error = 0;

  error = config_gamepad(pin_clock , pin_command, pin_attention, pin_data, true, true);
  if(error == 0)
  {
    Serial.println("Controlador encontrado y configurado");
  }
  else
  {
    Serial.println("Error, mando no encontrado");
  }
  Serial.begin(9600);
}

void Command::car(Bot &bot, int velocidad){
  byte vibrate = 0;
  read_gamepad(false, vibrate);
  int temp;
  bot.pitar();
  if(Button(PSB_PAD_UP))
  {
    bot.adelante(velocidad);
    Serial.print("adelante");
  }

  else if(Button(PSB_PAD_RIGHT))
  {
    bot.girar_derecha(velocidad);
    Serial.print("derecha");
  }

  else if(Button(PSB_PAD_LEFT))
  {
    bot.girar_izquierda(velocidad);
    Serial.print("izquierda");
  }
  else if(Button(PSB_PAD_DOWN))
  {
    bot.atras(velocidad);
    Serial.print("atras");
  }

  else
  {
   bot.parar();
  }

  delay(15);
};
