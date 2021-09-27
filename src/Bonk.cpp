#include "Bonk.h"
#include "State.hpp"
#include "TitleState.h"
#include "GameState.h"
#include "PauseState.h"
#include "State.hpp"

Bonk::Bonk::Bonk(Display* display) : Context(*display), display(display), canvas(screen.getSprite()){
	randomSeed(micros()*millis());
	state = new TitleState(canvas);
}

Bonk::Bonk::~Bonk(){
	delete state;
}

void Bonk::Bonk::draw()
{
	state->draw();
}
void Bonk::Bonk::loop(uint _time)
{
	state->update(_time, *this);
	draw();
	screen.commit();
}
void Bonk::Bonk::start()
{
	state->start(*this);
	LoopManager::addListener(this);
}
void Bonk::Bonk::stop()
{
	state->stop();
	LoopManager::removeListener(this);
}
void Bonk::Bonk::newGame()
{
	state->stop();
	delete state;
	state = new GameState(canvas);
	state->start(*this);
}
void Bonk::Bonk::pauseGame()
{
	state->stop();
	pausedGameState = state;
	state = new PauseState(canvas);
	state->start(*this);
}
void Bonk::Bonk::resumeGame()
{
	state->stop();
	delete state;
	state = pausedGameState;
	pausedGameState = nullptr;
	state->start(*this);
}
void Bonk::Bonk::quitGame()
{
	delete pausedGameState;
	pausedGameState = nullptr;

	state->stop();
	delete state;
	state = new TitleState(canvas);
	state->start(*this);
}
