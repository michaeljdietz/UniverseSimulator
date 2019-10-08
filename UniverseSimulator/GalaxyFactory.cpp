#include "GalaxyFactory.h"
#include "Random.h"
#include "Game.h"
#include "Galaxy.h"
#include "Cluster.h"

GalaxyFactory* GalaxyFactory::_instance;

GalaxyFactory::GalaxyFactory(Game* game) {
	_game = game;
}

GalaxyFactory* GalaxyFactory::getInstance() {
	if (_instance) {
		return _instance;
	}

	return _instance = new GalaxyFactory(Game::getInstance());
}

Galaxy* GalaxyFactory::create(Cluster* parent, std::vector<float> origin) {
	// TODO: Anything remaining after all children have been generated is extrastellar -- but when do we generate THAT stuff
	Galaxy* _galaxy = new Galaxy(_game);
	_galaxy->_parent = parent;

	_galaxy->_childCount = generateChildCount();
	_galaxy->_axisCoordinateCount = floor(cbrt((float)_galaxy->_childCount)) + 1;

	_galaxy->_mass = generateMass();
	_galaxy->_luminosity = generateLuminosity();
	_galaxy->_majorRadius = generateMajorRadius();
	_galaxy->_minorRadius = generateMinorRadius();
	_galaxy->_temperature = generateTemperature();

	return _galaxy;
}

long GalaxyFactory::generateChildCount() {
	return 0;
}

float GalaxyFactory::generateMass() {
	return 0.0f;
}

float GalaxyFactory::generateLuminosity() {
	return 0.0f;
}

float GalaxyFactory::generateMajorRadius() {
	return 0.0f;
}

float GalaxyFactory::generateMinorRadius() {
	return 0.0f;
}

float GalaxyFactory::generateTemperature() {
	return 0.0f;
}