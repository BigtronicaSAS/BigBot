#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Bigbot.h"

Bigbot SOCCER = {
    .Derecha = {.MotorA = true, .MotorB = false},
    .Izquierda = {.MotorA = false, .MotorB = true},
    .Adelante = {.MotorA = true, .MotorB = true},
    .Atras = {.MotorA = false, .MotorB = false}
    };

Bigbot MAGIC = {
    .Derecha = {.MotorA = false, .MotorB = true},
    .Izquierda = {.MotorA = true, .MotorB = false},
    .Adelante = {.MotorA = false, .MotorB = false},
    .Atras = {.MotorA = true, .MotorB = true}
    };

Bigbot MAGIC_4WD = SOCCER;

Bot::Bot(Bigbot &bigbot = MAGIC)
    : 
      Derecha(bigbot.Derecha),
      Izquierda(bigbot.Izquierda),
      Adelante(bigbot.Adelante),
      Atras(bigbot.Atras)
{
  pin_echo = 8;
  pin_trigger = 7;
  pin_buzzer = 4;
  MotorA_speed = 10;
  MotorA_direction = 12;
  MotorB_speed = 11;
  MotorB_direction = 13;
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
    {
      Serial.print("Rutina de Obstaculo, MaximaDistancia: ");
      Serial.println(MaximaDistancia);
      parar();
      delay(500);
      atras(velocidad);
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
    BothButtons(PSB_PAD_UP, PSB_L1) ? atras(255) : adelante(255);
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
    BothButtons(PSB_PAD_DOWN, PSB_L1) ? adelante(255) : atras(255);
    Serial.print("TurboAtras");
  }
  else if (BothButtons(PSB_PAD_UP, PSB_R1))
  {
    BothButtons(PSB_PAD_UP, PSB_L1) ? atras(180) : adelante(180);
    Serial.print("VmediaAdelante");
  }
  else if (BothButtons(PSB_PAD_DOWN, PSB_R1))
  {
    BothButtons(PSB_PAD_DOWN, PSB_L1) ? adelante(180) : atras(180);
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
    BothButtons(PSB_PAD_UP, PSB_L1) ? atras(velocidad) : adelante(velocidad);
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
    BothButtons(PSB_PAD_DOWN, PSB_L1) ? adelante(velocidad) : atras(velocidad);
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

bool Bot::toggle(int switchPin)
{
  static bool toggleState = false;
  static bool lastToggleState = false;
  static long toggleTimer = millis();

  bool currentToggleState = digitalRead(switchPin);

  if (millis() - toggleTimer > 100)
  {
    if (currentToggleState && !lastToggleState)
    {
      toggleState = !toggleState;
      toggleTimer = millis();
    }
  }
  lastToggleState = currentToggleState;
  return toggleState;
}

void Start(Bot &bot, int minVelocidad=100, int Distancia = 30) {
  const int Right = A0;
  const int Center = A1;
  const int Left = A2;
  const int Switch = A4;
 
  Serial.begin(9600);
  pinMode(Right, INPUT);
  pinMode(Center, INPUT);
  pinMode(Left, INPUT);
  pinMode(Switch, INPUT_PULLUP);

  do {
    bool state = bot.toggle(Switch);

    if (!state) {
      Serial.println("Modo Ultrasonido");
      bot.obstaculos(Distancia, minVelocidad);
    } else {
      Serial.println("Modo seguidor de linea");
      bot.seguidor(Left, Center, Right, minVelocidad);
    }

  } while (true);
}
void Obstaculo(Bot &bot, int minVelocidad = 100, int Distancia = 30)
{
  Serial.begin(9600);
  do
  { Serial.println("Modo Ultrasonido");
    bot.obstaculos(Distancia, minVelocidad);
  } while (true);
}

void Seguidor(Bot &bot, int minVelocidad = 100)
{
  const int Right = A0;
  const int Center = A1;
  const int Left = A2;

  Serial.begin(9600);
  pinMode(Right, INPUT);
  pinMode(Center, INPUT);
  pinMode(Left, INPUT);

  do
  {
    bot.seguidor(Left, Center, Right, minVelocidad);

  } while (true);
}

void PS2(Bot &bot, int minVelocidad=100) {
  int pin_clock = A3;
  int pin_command = A1;
  int pin_attention = A0;
  int pin_data = A2;
  int MaximaDistancia = 30;
  bot.controlPS2(pin_clock , pin_command, pin_attention, pin_data);

  do {
      Serial.println("Modo PS2");
      bot.carPS2(minVelocidad);
  } while (true);

}

void PS2_Toggle(Bot &bot, int minVelocidad=100) {
  int pin_clock = A3;
  int pin_command = A1;
  int pin_attention = A0;
  int pin_data = A2;
  int MaximaDistancia = 30;
  const int Switch = A4;
  bot.controlPS2(pin_clock , pin_command, pin_attention, pin_data);
  

  do {
    bool state = bot.toggle(Switch);

    if (state==0) {
      Serial.println("Modo PS2");
      bot.carPS2(minVelocidad);
      
    } else {
      Serial.println("Modo Obstaculos");
      bot.obstaculos(MaximaDistancia, minVelocidad);
    }

  } while (true);
}