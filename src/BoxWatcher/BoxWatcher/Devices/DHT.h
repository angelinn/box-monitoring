#pragma once

#include <dht11.h>
#include "../Models/DHTMeasurement.h"

class DHT
{
public:
	DHT(int);

public:
	DHTMeasurement GetMeasurements();

private:
	dht11 dht;
	int pin;
};
