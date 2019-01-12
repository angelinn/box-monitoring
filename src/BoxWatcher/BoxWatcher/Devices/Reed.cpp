#include "Reed.h"
#include <Arduino.h>

Reed::Reed(int pin) : pin(pin)
{   }

bool Reed::IsClosed()
{
	int signal = digitalRead(pin);
	return signal == HIGH;
}
