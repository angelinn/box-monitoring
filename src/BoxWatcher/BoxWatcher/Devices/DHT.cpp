#include "DHT.h"

DHT::DHT(int pin) : pin(pin)
{   }

DHTMeasurement DHT::GetMeasurements()
{
	int read = dht.read(pin);
	return DHTMeasurement { dht.temperature, dht.humidity };
}
