#pragma once
#include <vector>

class Galaxy;
class Cluster;
class Game;

class GalaxyFactory {
public:
	static GalaxyFactory* getInstance();
	Galaxy* create(Cluster*, std::vector<float>);

protected:
	static GalaxyFactory* _instance;
	Galaxy* _Galaxy;
	Game* _game;

	GalaxyFactory(Game*);
	long generateChildCount();
	float generateMass();
	float generateLuminosity();
	float generateMajorRadius();
	float generateMinorRadius();
	float generateTemperature();
};