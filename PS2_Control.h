#ifndef PS2_Control_h
#define PS2_Control_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PS2X_lib.h"

class PS2C : public PS2X
{
public:
    PS2C(int _pin_clock, int _pin_command, int _pin_attention, int _pin_data);
    void begin();
}

#endif
