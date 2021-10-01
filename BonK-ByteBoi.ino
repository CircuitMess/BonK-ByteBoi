#include <Arduino.h>
#include "src/Bonk.h"
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <ByteBoi.h>

//#include "Nibble.hpp"
#include <Audio/Piezo.h>

Bonk::Bonk *game;
void setup() {
	Serial.begin(115200);
	ByteBoi.begin();
	game=new Bonk::Bonk(ByteBoi.getDisplay());
	game->unpack();
	ByteBoi.splash();
	game->start();
}

void loop() {
	LoopManager::loop();
}