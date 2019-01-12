#include "Engine.h"

#include "Devices\LCD.h"
#include "Devices\DHT.h"
#include "Devices\PIR.h"
#include "Devices\Reed.h"

#include <Arduino.h>

Engine::Engine() : lcd(nullptr), weather(nullptr), pir(nullptr), reed(nullptr), lastPirState(false), updateRequested(false), lastMeasurement({ 0 })
{   }

void Engine::Setup()
{
	pinMode(REED_PIN, INPUT);

	Serial.begin(9600);
	lcd = new LCDDevice(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
	lcd->Write("u plebs");

	weather = new DHT(DHT_PIN);
	pir = new PIR(PIR_PIN);
	reed = new Reed(REED_PIN);
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


	delay(100);
}

void Engine::RaiseAlarm(AlarmType type)
{
	switch (type)
	{
	case AlarmType::Movement:
		lcd->Write("neshto shava");
		break;
	case AlarmType::Door:
		lcd->Write("vratata");
		break;
	}
}