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

struct Motion
{
	bool MotorA, MotorB;
};



struct Bigbot
{
    Motion Adelante;
	Motion Atras;
	Motion Derecha;
	Motion Izquierda;
};

extern Bigbot MAGIC;
extern Bigbot SOCCER;
extern Bigbot MAGIC_4WD;

class Bot : public PS2X
{
public:
	Bot(Bigbot &bigbot = MAGIC);
	void seguidor(int Left, int Center, int Right, int velocidad);
	void adelante(int velocidad);
	void atras(int velocidad);
	void girar_derecha(int velocidad);
	void girar_izquierda(int velocidad);
	void parar();
	void pitar();
	float detectar_obstaculo();
	void obstaculos(int MaximaDistancia, int velocidad);
	void controlPS2(int pin_clock, int pin_command, int pin_attention, int pin_data);
	void carPS2(int velocidad);
	bool toggle (int switchPin);

private:
	int MotorA_speed;
	int MotorA_direction;
	int MotorB_speed;
	int MotorB_direction;
	int pin_echo;
	int pin_trigger;
	int pin_buzzer;
	Motion Derecha;
	Motion Izquierda;
	Motion Adelante;
	Motion Atras;
};
void Start(Bot &bot, int minVelocidad=100, int Distancia = 30);
void PS2(Bot &bot, int minVelocidad=100);
void PS2_Toggle(Bot &bot, int minVelocidad=100);
void Obstaculo(Bot &bot, int minVelocidad=100, int Distancia = 30);
void Seguidor(Bot &bot, int minVelocidad=100);

#endif