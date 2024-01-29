#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PS2_Control.h"

PS2C::PS2C(int _pin_clock, int _pin_command, int _pin_attention, int _pin_data){
    pin_clock = _pin_clock;
    pin_command= _pin_command;
    pin_attention = _pin_attention;
    pin_data = _pin_data;
};

void PS2C::begin(){
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
