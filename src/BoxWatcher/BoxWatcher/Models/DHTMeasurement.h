#pragma once

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