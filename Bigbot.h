/*
  Curiosity.h - Librería de plataforma curiosity con control play 2.
  Creado por Juan Camilo Alvarez.
  Version: 1.0V
*/
#ifndef Bigbot_h
#define Bigbot_h

#include <Arduino.h>
#include <L298P.h>

struct Pinout {
    int MotorA_speed;
    int MotorA_direction;
    int MotorB_speed;
    int MotorB_direction;
    int pin_echo;
    int pin_trigger;
    int pin_buzzer;
};

extern Pinout BIGBOT_ARDUINO;
extern Pinout BIGBOT_ESP32;

class Bot : public L298P {
public:
    Bot(const Pinout& pinout);

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