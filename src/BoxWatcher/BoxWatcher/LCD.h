#pragma once

#include <LiquidCrystal.h>

#define LCD_COLUMNS 16
#define LCD_ROWS 2

class LCDDevice
{
public:
	LCDDevice(int, int, int, int, int, int);

public:
	void Write(const String &);
	void DisplayOn();
	void DisplayOff();

private:
	LiquidCrystal lcd;
};