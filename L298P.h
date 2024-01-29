#ifndef L298P_h
#define L298P_h

#include <Arduino.h>

class L298P
{
public:
    L298P(int _MotorA_speed, int _MotorA_direction, int _MotorB_speed, int _MotorB_direction,
          int _pin_echo, int _pin_trigger, int _pin_buzzer);

    void seguidor(int Left, int Center, int Right, int velocidad);
    void adelante(int velocidad);
    void atras(int velocidad);
    void girar_derecha(int velocidad);
    void girar_izquierda(int velocidad);
    void parar();
    void pitar();
    float detectar_obstaculo();
    void obstaculos(int MaximaDistancia, int velocidad);

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
