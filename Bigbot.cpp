#include <Arduino.h>
#include "Bigbot.h"

Bot::Bot(const Pinout &pinout)
    : L298P(pinout.MotorA_speed, pinout.MotorA_direction, pinout.MotorB_speed,
            pinout.MotorB_direction, pinout.pin_echo, pinout.pin_trigger, pinout.pin_buzzer)
{
}
