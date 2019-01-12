#pragma once

#include <dht11.h>

struct DHTMeasurement
{
	int temperature;
	int humidity; 

	bool operator==(const DHTMeasurement& rhs)
	{
		return temperature == rhs.temperature && humidity == rhs.humidity;
	}

	bool operator!=(const DHTMeasurement& rhs)
	{
		return !(*this == rhs);
	}
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
