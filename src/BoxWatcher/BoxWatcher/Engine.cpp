#include "Engine.h"

#include "Devices\LCD.h"
#include "Devices\DHT.h"
#include "Devices\PIR.h"
#include "Devices\Reed.h"
#include "Devices\Gas.h"

#include <Arduino.h>
#include "External/QueueArray.h"

typedef void(*Function)(void);
QueueArray<Function> functions;

Engine::Engine() : lcd(nullptr), weather(nullptr), pir(nullptr), reed(nullptr), lastPirState(false), updateRequested(false), lastMeasurement({ 0 })
{   }

void Engine::Setup()
{
	pinMode(7, OUTPUT);
	Serial.begin(9600);
	lcd = new LCDDevice(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
	lcd->Write("u plebs");

	weather = new DHT(DHT_PIN);
	pir = new PIR(PIR_PIN);
	reed = new Reed(REED_PIN);
	gas = new Gas(GAS_ANALOG_PIN);
}

void Engine::Loop()
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

	bool movement = pir->IsMovementDetected();
	if (movement)
		RaiseAlarm(AlarmType::Movement);
	else if (movement != lastPirState)
	{
		lastPirState = movement;
		updateRequested = true;
	}

	bool isDoorClosed = reed->IsClosed();
	if (!isDoorClosed)
		RaiseAlarm(AlarmType::Door);

	int gasMeasurement = gas->ReadGas();
	Serial.println(gasMeasurement);
	if (gasMeasurement > 400)
		RaiseAlarm(AlarmType::Fumes);

	delay(1000);
	ExecutePostLoopSteps();
}

void Engine::StopAlarm()
{
	Serial.println("Stopping alarm");
	noTone(7);
}

void Engine::ExecutePostLoopSteps()
{
	while (!functions.isEmpty())
	{
		Function f = functions.dequeue();
		f();
	}
}

void Engine::RaiseAlarm(AlarmType type)
{
	switch (type)
	{
	case AlarmType::Movement:
		lcd->Write("Movement");
		lcd->WriteRow("Detected.", 1);
		break;
	case AlarmType::Door:
		lcd->Write("Door is open.");
		break;
	case AlarmType::Fumes:
		Serial.println("Raising fumes alarm");
		lcd->Write("Fumes alert!");
		tone(7, 600);
		functions.enqueue(StopAlarm);

		break;
	}
}

