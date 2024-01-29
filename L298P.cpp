#include <Arduino.h>
#include "L298P.h"

L298P::L298P(int _MotorA_speed, int _MotorA_direction, int _MotorB_speed, int _MotorB_direction,
             int _pin_echo, int _pin_trigger, int _pin_buzzer)
{
    MotorA_speed = _MotorA_speed;
    MotorA_direction = _MotorA_direction;
    MotorB_speed = _MotorB_speed;
    MotorB_direction = _MotorB_direction;
    pin_echo = _pin_echo;
    pin_trigger = _pin_trigger;
    pin_buzzer = _pin_buzzer;

    // Init Driver L298P
    pinMode(pin_echo, INPUT);
    pinMode(pin_trigger, OUTPUT);
    pinMode(pin_buzzer, OUTPUT);
    pinMode(MotorA_direction, OUTPUT);
    pinMode(MotorA_speed, OUTPUT);
    pinMode(MotorB_speed, OUTPUT);
    pinMode(MotorB_direction, OUTPUT);
    digitalWrite(pin_trigger, LOW);
    digitalWrite(pin_buzzer, LOW);
}

void L298P::pitar(){
digitalWrite(pin_buzzer, HIGH);
  delay(1000);
}

void L298P::girar_derecha(int velocidad)
{

    digitalWrite(MotorA_direction, LOW);
    digitalWrite(MotorB_direction, HIGH);
    analogWrite(MotorA_speed, (velocidad));
    analogWrite(MotorB_speed, (velocidad));
}

void L298P::girar_izquierda(int velocidad)
{
    digitalWrite(MotorA_direction, HIGH);
    digitalWrite(MotorB_direction, LOW);
    analogWrite(MotorA_speed, (velocidad));
    analogWrite(MotorB_speed, (velocidad));
}



void L298P::adelante(int velocidad)
{
    digitalWrite(MotorA_direction, LOW);
    digitalWrite(MotorB_direction, LOW);
    analogWrite(MotorA_speed, (velocidad));
    analogWrite(MotorB_speed, (velocidad));
}

void L298P::atras(int velocidad)
{
    digitalWrite(MotorA_direction, HIGH);
    digitalWrite(MotorB_direction, HIGH);
    analogWrite(MotorA_speed, (velocidad));
    analogWrite(MotorB_speed, (velocidad));
}

void L298P::parar()
{
    analogWrite(MotorA_speed, 0);
    analogWrite(MotorB_speed, 0);
}

float L298P::detectar_obstaculo()
{
    digitalWrite(pin_trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pin_trigger, HIGH);
    delayMicroseconds(10);
    float distancia = pulseIn(pin_echo, HIGH) * 0.034 / 2;
    Serial.println(distancia);
    if (distancia == 0)
    {
        Serial.println("Conecte el sensor");
    }
    else
    {
        return distancia;
    }
}

void L298P::obstaculos(int MaximaDistancia, int velocidad)
{
    long randomNumber;
    int distance = detectar_obstaculo();
    if (distance > 0)
    {
        if (distance < MaximaDistancia)
        {
            if (distance > (MaximaDistancia / 2))
            {
                atras(velocidad);
                delay(200);
                parar();
                delay(500);
            }
            else
            {
                // Generar un número aleatorio para decidir la dirección de giro
                randomNumber = random(1, 3);
                if (randomNumber == 1)
                {
                    girar_izquierda(velocidad);
                    delay(400);
                    parar();
                    delay(500);
                }
                else
                {
                    girar_derecha(velocidad);
                    delay(400);
                    parar();
                    delay(500);
                }
            }
        }
        else
        {
            adelante(velocidad);
        }
    }
    else
    {
        adelante(velocidad);
    }
}

void L298P::seguidor(int Left, int Center, int Right, int velocidad)
{
    int blanco = 0;
    int negro = 1;
    bool IR_centro = digitalRead(Center);
    bool IR_izquierda = digitalRead(Left);
    bool IR_derecha = digitalRead(Right);
    Serial.print(IR_izquierda);
    Serial.print(IR_centro);
    Serial.print(IR_derecha);
    Serial.println("");

    if ((IR_izquierda == blanco) && (IR_centro == negro) && (IR_derecha == blanco))
    {
        adelante(velocidad);
        Serial.println("Adelante");
    }
    else if ((IR_izquierda == negro) && (IR_centro == negro) && (IR_derecha == blanco))
    {
        girar_derecha(velocidad);
        Serial.println("derecha");
    }
    else if ((IR_izquierda == negro) && (IR_centro == blanco) && (IR_derecha == blanco))
    {
        girar_derecha(velocidad);
        Serial.println("derecha");
    }

    else if ((IR_izquierda == blanco) && (IR_centro == negro) && (IR_derecha == negro))
    {
        girar_izquierda(velocidad);
        Serial.println("Izquierda");
    }
    else if ((IR_izquierda == blanco) && (IR_centro == blanco) && (IR_derecha == negro))
    {
        girar_izquierda(velocidad);
        Serial.println("Izquierda");
    }
    else if ((IR_izquierda == blanco) && (IR_centro == blanco) && (IR_derecha == blanco))
    {
        parar();
        Serial.println("parar");
    }
    else if ((IR_izquierda == negro) && (IR_centro == negro) && (IR_derecha == negro))
    {
        adelante(velocidad);
        Serial.println("Adelante");
    }
}