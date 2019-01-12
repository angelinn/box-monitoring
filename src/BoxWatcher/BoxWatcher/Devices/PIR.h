#pragma once

class PIR
{
public:
	PIR(int);

public:
	bool IsMovementDetected();

private:
	int pin;
};