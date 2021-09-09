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
	ByteBoi.getDisplay()->commit();
	LoopManager::addListener(Input::getInstance());
	game=new Bonk::Bonk(ByteBoi.getDisplay());
	LoopManager::addListener(game);
	game->unpack();
	game->start();
}

void loop() {
	LoopManager::loop();
	yield();
}