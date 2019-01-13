#include "Engine.h"

#include "Devices\LCD.h"
#include "Devices\DHT.h"
#include "Devices\PIR.h"
#include "Devices\Reed.h"
#include "Devices\Gas.h"

#include "External/QueueArray.h"

#include <Arduino.h>

Engine::Engine() : lcd(nullptr), weather(nullptr), pir(nullptr), reed(nullptr), lastPirState(false), updateRequested(false), lastMeasurement({ 0 })
{   }

void Engine::Setup()
{
	pinMode(BUZZER_PIN, OUTPUT);
	pinMode(MOVEMENT_LED, OUTPUT);
	pinMode(DOOR_LED, OUTPUT);
	pinMode(SMOKE_LED, OUTPUT);

	Serial.begin(SERIAL_FREQ);
	lcd = new LCDDevice(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
	lcd->Write("Initializing...");

	weather = new DHT(DHT_PIN);
	pir = new PIR(PIR_PIN);
	reed = new Reed(REED_PIN);
	gas = new Gas(GAS_ANALOG_PIN);
}

void Engine::Loop()
{
	CheckWeather();
	CheckMovement();
	CheckDoor();
	CheckAir();

	delay(SLEEP_MS);
	ExecutePostLoopSteps();
}

void Engine::CheckWeather()
{
	DHTMeasurement weatherMeasurements = weather->GetMeasurements();
	if (weatherMeasurements != lastMeasurement)
		updateRequested = true;

	if (updateRequested)
	{
		lcd->Clear();
		lcd->WriteRow(String("Temp: ") + (int)weatherMeasurements.temperature + "C", 0);
		lcd->WriteRow(String("RH: ") + (int)weatherMeasurements.humidity + "%", 1);

		lastMeasurement = weatherMeasurements;
	}
}

void Engine::CheckMovement()
{
	bool movement = pir->IsMovementDetected();
	if (movement)
	{
		RaiseAlarm(AlarmType::Movement);
	}
	else if (movement != lastPirState)
	{
		lastPirState = movement;
		updateRequested = true;
	}
}

void Engine::CheckDoor()
{
	bool isDoorClosed = reed->IsClosed();
	if (!isDoorClosed)
		RaiseAlarm(AlarmType::Door);
}

void Engine::CheckAir()
{
	int gasMeasurement = gas->ReadGas();

	if (gasMeasurement > GAS_MAX_VALUE)
		RaiseAlarm(AlarmType::Fumes);
}

void StopAlarm()
{
	digitalWrite(DOOR_LED, LOW);
	digitalWrite(MOVEMENT_LED, LOW);
	digitalWrite(SMOKE_LED, LOW);

	noTone(BUZZER_PIN);
}

void Engine::ExecutePostLoopSteps()
{
	while (!functions.isEmpty())
	{
		Function function = functions.dequeue();
		function();
	}
}

void Engine::RaiseAlarm(AlarmType type)
{
	switch (type)
	{
	case AlarmType::Movement:
		lcd->Write("Movement");
		lcd->WriteRow("Detected.", 1);
		digitalWrite(MOVEMENT_LED, HIGH);
		break;
	case AlarmType::Door:
		lcd->Write("Door is open.");
		digitalWrite(DOOR_LED, HIGH);
		break;
	case AlarmType::Fumes:
		lcd->Write("Fumes alert!");
		digitalWrite(SMOKE_LED, HIGH);
		tone(BUZZER_PIN, BUZZER_ALARM_FREQUENCY);
		break;
	}

	functions.enqueue(StopAlarm);
}
