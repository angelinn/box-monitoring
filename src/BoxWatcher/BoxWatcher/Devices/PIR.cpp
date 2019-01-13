#include "PIR.h"
#include <Arduino.h>

PIR::PIR(int pin) : pin(pin)
{   }

bool PIR::IsMovementDetected()
{
	int state = digitalRead(pin);
	return state == HIGH;
}
