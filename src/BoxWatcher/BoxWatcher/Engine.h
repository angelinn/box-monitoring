#pragma once

#include "Devices/DHT.h"
#include "Models/AlarmType.h"
#include "External/QueueArray.h"

#define SERIAL_FREQ 9600
#define SLEEP_MS 1000

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

#define DOOR_LED 30
#define MOVEMENT_LED 31
#define SMOKE_LED 32

#define BUZZER_PIN 7
#define BUZZER_ALARM_FREQUENCY 600

#define GAS_MAX_VALUE 400

class LCDDevice;
class DHT;
class PIR;
class Reed;
class Gas;


class Engine
{
	typedef void(Engine::*Function)();

public:
	Engine();

public:
	void Setup();
	void Loop();
	void RaiseAlarm(AlarmType);
	void CheckWeather();
	void CheckDoor();
	void CheckMovement();
	void CheckAir();

private:
	void StopAlarm();
	void ExecutePostLoopSteps();

private:
	QueueArray<Function> functions;
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
