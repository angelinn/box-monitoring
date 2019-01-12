#include "Devices\LCD.h"
#include "Devices\DHT.h"

// the setup function runs once when you press reset or power the board

#define LCD_D7_PIN 2
#define LCD_D6_PIN 3
#define LCD_D5_PIN 4
#define LCD_D4_PIN 5
#define LCD_RS_PIN 12
#define LCD_E_PIN 11

#define DHT_PIN 22

LCDDevice* lcd = nullptr;
DHT* weather = nullptr;

void setup() 
{
	lcd = new LCDDevice(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
	lcd->Write("u plebs");

	weather = new DHT(DHT_PIN);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	lcd->DisplayOn();
	delay(1000);
	lcd->DisplayOff();
	delay(1000);

	DHTMeasurement weatherMeasurements = weather->GetMeasurements(); 
	lcd->Write(String(weatherMeasurements.temperature) + " " + weatherMeasurements.humidity);
}
