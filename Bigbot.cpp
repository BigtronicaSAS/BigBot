#include <Arduino.h>
#include "Bigbot.h"

Pinout BIGBOT_ARDUINO = {10, 12, 11, 13, 8, 7, 4};
Pinout BIGBOT_ESP32 = {5, 19, 23, 18, 12, 14, 17};

Bot::Bot(const Pinout &pinout)
    : L298P(pinout.MotorA_speed, pinout.MotorA_direction, pinout.MotorB_speed,
            pinout.MotorB_direction, pinout.pin_echo, pinout.pin_trigger, pinout.pin_buzzer)
{
}
