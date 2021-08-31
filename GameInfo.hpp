#ifndef GAME_INFO
#define GAME_INFO

class Context;
struct GameInfo {
	const char* title;
	const char* description;
	const uint16_t* icon;
	Context* (*launch)(Display& display);
};
#endif

#include <Arduino.h>
#include <Display/Display.h>
#include <SPIFFS.h>
#include "src/bitmaps/bonk_icon.hpp"
#include "src/Bonk.h"

const GameInfo BonkInfo {
		"Bonk",
		"Bonk! the ball back and forth.",
		[]() -> fs::File { return SPIFFS.open("/bonk.raw"); },
		[](Display& display) -> Context* { return new Bonk::Bonk(display); }
};