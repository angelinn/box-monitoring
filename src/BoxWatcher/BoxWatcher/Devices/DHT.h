#pragma once

#include <dht11.h>

struct DHTMeasurement
{
	float temperature;
	float humidity;
};

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
