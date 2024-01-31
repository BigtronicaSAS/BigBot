#ifndef PS2_h
#define PS2_h

#include <PS2X_lib.h>

class Command : public PS2X {
public:
    Command();
    void init();
	void car(Bot &bot, int velocidad);

private:
  int pin_clock;
  int pin_command;
  int pin_attention;
  int pin_data
};

#endif