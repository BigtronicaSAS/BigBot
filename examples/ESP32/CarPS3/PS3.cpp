#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PS2.h"

Command::Command()
{
}

void Command::init()
{
  Serial.begin(9600);
  int error = 0;
  error = config_gamepad(pin_clock, pin_command, pin_attention, pin_data, true, true);
  if (error == 0)
  {
    Serial.println("Controlador encontrado y configurado");
  }
  else
  {
    Serial.println("Error, mando no encontrado");
  }
}

void Command::car(Bot &bot, int velocidad)
{
  if (data.button.up)
  {
    bot.adelante(velocidad);
    Serial.print("adelante");
  }
  else if (data.button.down)
  {
    bot.atras(velocidad);
    Serial.print("atras");
  }
  else if (data.button.right)
  {
    bot.girar_derecha(velocidad);
    Serial.print("derecha");
  }
  else if (data.button.left)
  {
    bot.girar_izquierda(velocidad);
    Serial.print("izquierda");
  }
  else 
  {
    bot.parar();
  }

  delay(10);
};
