#include <Bigbot.h>
#define MotorA_speed 10
#define MotorA_direction 12
#define MotorB_speed 11
#define MotorB_direction 13
#define pin_echo 8
#define pin_trigger 7
#define pin_buzzer 4
Bot bot(MotorA_speed, MotorA_direction, MotorB_speed, MotorB_direction,
        pin_echo, pin_trigger, pin_buzzer);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        bt_data = Serial.read();
        Serial.println(bt_data);
    }
    if (bt_data == 1)
    {
        bot.adelante(255);
    }
    else if (bt_data == 2)
    {
        bot.atras(255);
    }
    else if (bt_data == 3)
    {
        bot.girar_izquierda(255);
    }
    else if (bt_data == 4)
    {
        bot.girar_derecha(255);
    }
    else if (bt_data == 5)
    {
        bot.parar();
    }
}