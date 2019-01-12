#include "Engine.h"

// the setup function runs once when you press reset or power the board

Engine engine;

void setup() 
{
	engine.Setup();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	engine.Loop();
}
