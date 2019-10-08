#include "Game.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include "Console.h"
#include "Universe.h"
#include "AstronomicalObject.h"
#include <Windows.h>

Game* Game::_instance;

Game::Game() {
	_console = new Console(this);
	_universe = new Universe(this);
	_currentObject = _universe;
}

Game* Game::getInstance()
{
	if (_instance) {
		return _instance;
	}

	return _instance = new Game();
}

void Game::start() {
	_console->start();
}

AstronomicalObject* Game::getCurrentObject()
{
	return _currentObject;
}

void Game::setCurrentObject(AstronomicalObject* object)
{
	_currentObject = object;
}

Universe* Game::getUniverse()
{
	return _universe;
}