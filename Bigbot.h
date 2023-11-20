/*
  Curiosity.h - Librería de plataforma curiosity con control play 2.
  Creado por Juan Camilo Alvarez.
  Version: 1.0V
*/
#ifndef Bigbot_h
#define Bigbot_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PS2X_lib.h"


class Bot : public PS2X {
  public:
    Bot();
	void seguidor(int Left, int Center, int Right, int velocidad);
	void adelante(int velocidad);
	void atras(int velocidad);
	void girar_derecha(int velocidad);
	void girar_izquierda(int velocidad);
	void parar();
	void pitar();
	float detectar_obstaculo();
	void obstaculos(int MaximaDistancia, int velocidad);
	void controlPS2(int pin_clock , int pin_command, int pin_attention, int pin_data);
	void carPS2(int velocidad);
	
  private:
	int MotorA_speed;
    int MotorA_direction;
    int MotorB_speed;
    int MotorB_direction;
	int pin_echo;
	int pin_trigger;
	int pin_buzzer;
};

#endif