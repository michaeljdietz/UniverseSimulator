#pragma once
#include "stdafx.h"
#include <vector>

#define PERCENT_VOID 0.97f
#define PERCENT_CLUSTER 0.03f

#define PERCENT_SINGLE_CLUSTER_SUPERCLUSTER 0.46f
#define MAX_CLUSTERS_PER_SUPERCLUSTER 15

class Supercluster;
class Universe;
class Game;

class SuperclusterFactory {
public:
	static SuperclusterFactory* getInstance();
	Supercluster* create(Universe*, const std::vector<float>);

private:
	static SuperclusterFactory* _instance;
	Supercluster* _supercluster;
	Game* _game;
	float _richMassRatio;
	float _poorMassRatio;

	SuperclusterFactory(Game* game);
	long generateChildCount();
	long generateRichClusterCount();
	float generateRichMass();
	float generatePoorMass();
	float generateRichLuminosity();
	float generatePoorLuminosity();
	float generateRichMajorRadius();
	float generatePoorMajorRadius();
	float generateRichMinorRadius();
	float generatePoorMinorRadius();
	float generateRichTemperature();
	float generatePoorTemperature();
};