#pragma once

#include "Devices/DHT.h"

#define LCD_D7_PIN 2
#define LCD_D6_PIN 3
#define LCD_D5_PIN 4
#define LCD_D4_PIN 5
#define LCD_RS_PIN 12
#define LCD_E_PIN 11

#define DHT_PIN 22

#define PIR_PIN 23

#define REED_PIN 8

#define GAS_ANALOG_PIN 0

class LCDDevice;
class DHT;
class PIR;
class Reed;
class Gas;

enum AlarmType
{
	MissingNo = -1,
	None,
	Movement,
	Door,
	Fumes
};

class Engine
{
public:
	Engine();

public:
	void Setup();
	void Loop();
	void RaiseAlarm(AlarmType);

private:
	DHTMeasurement lastMeasurement;
	bool lastPirState;
	bool updateRequested;

private:
	LCDDevice* lcd;
	DHT* weather;
	PIR* pir;
	Reed* reed;
	Gas* gas;
};
