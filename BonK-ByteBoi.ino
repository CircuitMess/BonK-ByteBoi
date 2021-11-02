#include <Arduino.h>
#include "src/Bonk.h"
#include <CircuitOS.h>
#include <Input/I2cExpander.h>
#include <Input/InputI2C.h>
#include <Loop/LoopManager.h>
#include <ByteBoi.h>

#include <SD.h>

namespace Bonk {
	Sample* menuMusic = nullptr;
	Sample* gameMusic = nullptr;
};

Bonk::Bonk *game;
void setup() {
	Serial.begin(115200);
	ByteBoi.begin();
	ByteBoi.bindMenu();
	BatteryPopup.enablePopups(true);
	ByteBoi.setGameID("Bonk");
	SD.begin(SD_CS, SPI);

	Bonk::menuMusic = new Sample(SD.open(ByteBoi.getSDPath() + "/Music/Menu.aac"));
	Bonk::gameMusic = new Sample(SD.open(ByteBoi.getSDPath() + "/Music/Game.aac"));
	Bonk::menuMusic->setLooping(true);
	Bonk::gameMusic->setLooping(true);

	game=new Bonk::Bonk(ByteBoi.getDisplay());
	game->unpack();
	ByteBoi.splash();
	game->start();
}

void loop() {
	LoopManager::loop();
}