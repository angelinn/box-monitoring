#include "LCD.h"
#include <Arduino.h>

LCDDevice::LCDDevice(int rs, int en, int d4, int d5, int d6, int d7) : lcd(rs, en, d4, d5, d6, d7)
{
	lcd.begin(LCD_COLUMNS, LCD_ROWS);
}

void LCDDevice::Write(const String& message)
{
	lcd.clear();
	Append(message);
}

void LCDDevice::WriteRow(const String& message, int row)
{
	lcd.setCursor(0, row);
	Append(message);
}

void LCDDevice::Clear()
{
	lcd.clear();
}

void LCDDevice::Append(const String& message)
{
	lcd.write(message.c_str());
}

void LCDDevice::DisplayOn()
{
	lcd.display();
}

void LCDDevice::DisplayOff()
{
	lcd.noDisplay();
}
