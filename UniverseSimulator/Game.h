#pragma once

#include <vector>

class Universe;
class AstronomicalObject;
class PerlinNoise;
class SimplexNoise;
class Console;

class Game {
public:
	static Game* getInstance();
	void start();
	AstronomicalObject* getCurrentObject();
	void setCurrentObject(AstronomicalObject* object);
	Universe* getUniverse();

private:
	Game();
	static Game* _instance;
	Console* _console;
	Universe* _universe;
	AstronomicalObject* _currentObject;
};