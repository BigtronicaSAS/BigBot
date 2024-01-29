#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Bigbot.h"

Bot::Bot(int _MotorA_speed, int _MotorA_direction, int _MotorB_speed, int _MotorB_direction,
         int _pin_echo, int _pin_trigger, int _pin_buzzer)
    : L298P(_MotorA_speed, _MotorA_direction, _MotorB_speed, _MotorB_direction, _pin_echo, _pin_trigger, _pin_buzzer)
{
}
