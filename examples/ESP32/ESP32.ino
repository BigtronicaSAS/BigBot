#include <Bigbot.h>
#define MotorA_speed A3
#define MotorA_direction A1
#define MotorB_speed A0
#define MotorB_direction A2
#define pin_echo A2
#define pin_trigger A2
#define pin_buzzer A2
Bot bot(MotorA_speed, MotorA_direction, MotorB_speed, MotorB_direction,
        pin_echo, pin_trigger, pin_buzzer);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
}