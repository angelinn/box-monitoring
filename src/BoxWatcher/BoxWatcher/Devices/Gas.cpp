#include "Gas.h"
#include <Arduino.h>

Gas::Gas(int pin) : pin(pin)
{   }

int Gas::ReadGas()
{
	int val = 0;
	int val1;
	int val2;
	int val3;

	val1 = analogRead(pin);
	delay(10);
	val2 = analogRead(pin);
	delay(10);
	val3 = analogRead(pin);

	val = (val1 + val2 + val3) / 3;
	return val;
}
