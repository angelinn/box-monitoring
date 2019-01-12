#include "Devices\LCD.h"
#include "Devices\DHT.h"
#include "Devices\PIR.h"

// the setup function runs once when you press reset or power the board

#define LCD_D7_PIN 2
#define LCD_D6_PIN 3
#define LCD_D5_PIN 4
#define LCD_D4_PIN 5
#define LCD_RS_PIN 12
#define LCD_E_PIN 11

#define DHT_PIN 22

#define PIR_PIN 23

LCDDevice* lcd = nullptr;
DHT* weather = nullptr;
PIR* pir = nullptr;

void setup() 
{
	Serial.begin(9600);
	lcd = new LCDDevice(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
	lcd->Write("u plebs");

	weather = new DHT(DHT_PIN);
	pir = new PIR(PIR_PIN);
}

DHTMeasurement lastMeasurement = { 0 };
bool updateRequested = false;

// the loop function runs over and over again until power down or reset
void loop() 
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
		lcd->Write("MOVEMENT!");
	else
		updateRequested = true;


	delay(1000);
}
