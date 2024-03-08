#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Bigbot.h"

Bigbot SOCCER = {
    .l298P = {
        .MotorA_speed = 10,
        .MotorA_direction = 12,
        .MotorB_speed = 11,
        .MotorB_direction = 13,
        .pin_echo = 8,
        .pin_trigger = 7,
        .pin_buzzer = 4},

    .Derecha = {.MotorA = true, .MotorB = false},
    .Izquierda = {.MotorA = false, .MotorB = true},
    .Adelante = {.MotorA = true, .MotorB = true},
    .Atras = {.MotorA = false, .MotorB = false}};

 Bigbot MAGIC ={
    .l298P = {
        .MotorA_speed = 10,
        .MotorA_direction = 12,
        .MotorB_speed = 11,
        .MotorB_direction = 13,
        .pin_echo = 8,
        .pin_trigger = 7,
        .pin_buzzer = 4},

    .Derecha = {.MotorA = false, .MotorB = true},
    .Izquierda = {.MotorA = true, .MotorB = false},
    .Adelante = {.MotorA = false, .MotorB = false},
    .Atras = {.MotorA = true, .MotorB = true}};

   Bigbot MAGIC_4WD = SOCCER;   

Bot::Bot(Bigbot &bigbot)
    : MotorA_speed(bigbot.l298P.MotorA_speed),
      MotorA_direction(bigbot.l298P.MotorA_direction),
      MotorB_speed(bigbot.l298P.MotorB_speed),
      MotorB_direction(bigbot.l298P.MotorB_direction),
      pin_echo(bigbot.l298P.pin_echo),
      pin_trigger(bigbot.l298P.pin_trigger),
      pin_buzzer(bigbot.l298P.pin_buzzer),
      Derecha(bigbot.Derecha),
      Izquierda(bigbot.Izquierda),
      Adelante(bigbot.Adelante),
      Atras(bigbot.Atras)
{
  Serial.begin(9600);
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

void Bot::girar_derecha(int velocidad)
{

  digitalWrite(MotorA_direction, Derecha.MotorA);
  digitalWrite(MotorB_direction, Derecha.MotorB);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::girar_izquierda(int velocidad)
{
  digitalWrite(MotorA_direction, Izquierda.MotorA);
  digitalWrite(MotorB_direction, Izquierda.MotorB);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::pitar()
{
  digitalWrite(pin_buzzer, Button(PSB_CIRCLE) ? HIGH : LOW);
}

void Bot::adelante(int velocidad)
{
  digitalWrite(MotorA_direction, Adelante.MotorA);
  digitalWrite(MotorB_direction, Adelante.MotorB);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::atras(int velocidad)
{
  digitalWrite(MotorA_direction, Atras.MotorA);
  digitalWrite(MotorB_direction, Atras.MotorB);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::parar()
{
  analogWrite(MotorA_speed, 0);
  analogWrite(MotorB_speed, 0);
}

float Bot::detectar_obstaculo()
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

void Bot::obstaculos(int MaximaDistancia, int velocidad)
{
  long randomNumber;
  int distance = detectar_obstaculo();
  if (distance > 0)
  {
    if (distance < MaximaDistancia)
    {   parar();
        delay(500);
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

void Bot::controlPS2(int pin_clock, int pin_command, int pin_attention, int pin_data)
{
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
  Serial.begin(9600);
}

void Bot::carPS2(int velocidad)
{
  byte vibrate = 0;
  read_gamepad(false, vibrate);
  int temp;
  pitar();
  if (Turbo(PSB_PAD_UP))
  {
    BothButtons(PSB_PAD_UP, PSB_L1) ? atras(255) :adelante(255);
    Serial.print("TurboAdelante");
  }

  else if (Turbo(PSB_PAD_RIGHT))
  {
    girar_derecha(255);
    Serial.print("TurboDerecha");
  }

  else if (Turbo(PSB_PAD_LEFT))
  {
    girar_izquierda(255);
    Serial.print("TurboIzquierda");
  }

  else if (Turbo(PSB_PAD_DOWN))
  {
    BothButtons(PSB_PAD_DOWN, PSB_L1) ? adelante(255) :atras(255);
    Serial.print("TurboAtras");
  }
  else if (BothButtons(PSB_PAD_UP, PSB_R1))
  {
    BothButtons(PSB_PAD_UP, PSB_L1) ? atras(180) :adelante(180);
    Serial.print("VmediaAdelante");
  }
  else if (BothButtons(PSB_PAD_DOWN, PSB_R1))
  {
    BothButtons(PSB_PAD_DOWN, PSB_L1) ? adelante(180) :atras(180);
    Serial.print("VmediaAtras");
  }
  else if (BothButtons(PSB_PAD_LEFT, PSB_R1))
  {
    girar_izquierda(180);
    Serial.print("VmediaIzquierda");
  }
  else if (BothButtons(PSB_PAD_RIGHT, PSB_R1))
  {
    girar_derecha(180);
    Serial.print("VmediaDerecha");
  }

  else if (Button(PSB_PAD_UP))
  {
    BothButtons(PSB_PAD_UP, PSB_L1) ? atras(velocidad) :adelante(velocidad);
    Serial.print("Adelante");
  }

  else if (Button(PSB_PAD_RIGHT))
  {
    girar_derecha(velocidad);
    Serial.print("derecha");
  }

  else if (Button(PSB_PAD_LEFT))
  {
    girar_izquierda(velocidad);
    Serial.print("izquierda");
  }
  else if (Button(PSB_PAD_DOWN))
  {
    BothButtons(PSB_PAD_DOWN, PSB_L1) ? adelante(velocidad) :atras(velocidad);
    Serial.print("atras");
  }

  else
  {
    parar();
  }

  delay(15);
};

void Bot::seguidor(int Left, int Center, int Right, int velocidad)
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
    girar_izquierda(velocidad);
  }
  else if ((IR_izquierda == negro) && (IR_centro == blanco) && (IR_derecha == blanco))
  {
    girar_izquierda(velocidad);
  }

  else if ((IR_izquierda == blanco) && (IR_centro == blanco) && (IR_derecha == negro))
  {
    girar_derecha(velocidad);
  }
  else if ((IR_izquierda == blanco) && (IR_centro == negro) && (IR_derecha == negro))
  {
     girar_derecha(velocidad);
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
