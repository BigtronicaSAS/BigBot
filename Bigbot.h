/*
  Curiosity.h - Librería de plataforma curiosity con control play 2.
  Creado por Juan Camilo Alvarez.
  Version: 1.0V
*/
#ifndef Bigbot_h
#define Bigbot_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <L298P.h>

class Bot : public L298P
{
public:
	Bot(int _MotorA_speed, int _MotorA_direction, int _MotorB_speed, int _MotorB_direction,
		int _pin_echo, int _pin_trigger, int _pin_buzzer);
};

#endif