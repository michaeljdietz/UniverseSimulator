#pragma once
#include <vector>
#include "PhysicalConstants.h"

// i am unsure of this number...
#define RICH_CLUSTER_PERCENTAGE 0.01f

#define RICH_CLUSTER_GALAXY_MIN 30
#define RICH_CLUSTER_GALAXY_MAX 300

#define RICH_CLUSTER_MASS_MIN pow(10, 14) / HUBBLE_CONSTANT
#define RICH_CLUSTER_MASS_MAX pow(20, 15) / HUBBLE_CONSTANT

#define RICH_CLUSTER_MAJOR_RADIUS_MIN 1.0f / HUBBLE_CONSTANT
#define RICH_CLUSTER_MAJOR_RADIUS_MAX 2.0f / HUBBLE_CONSTANT
#define RICH_CLUSTER_MAJOR_RADIUS_MASS_FACTOR 0.5f

#define RICH_CLUSTER_LUMINOSITY_MIN pow(60, 11) / pow(HUBBLE_CONSTANT, 2)
#define RICH_CLUSTER_LUMINOSITY_MAX pow(60, 12) / pow(HUBBLE_CONSTANT, 2)
#define RICH_CLUSTER_LUMINOSITY_MASS_FACTOR 0.5f

#define RICH_CLUSTER_TEMPERATURE_MIN 2.0f * 1000.0f / BOLTZMAN_CONSTANT_EV_K
#define RICH_CLUSTER_TEMPERATURE_MAX 14.0f * 1000.0f / BOLTZMAN_CONSTANT_EV_K
#define RICH_CLUSTER_TEMPERATURE_MASS_FACTOR 0.5f

#define POOR_CLUSTER_GALAXY_MIN 1
#define POOR_CLUSTER_GALAXY_MAX 30

#define POOR_CLUSTER_MASS_MIN pow(10, 10.5) / HUBBLE_CONSTANT
#define POOR_CLUSTER_MASS_MAX pow(10, 14) / HUBBLE_CONSTANT

#define POOR_CLUSTER_MAJOR_RADIUS_MIN 0.1f / HUBBLE_CONSTANT
#define POOR_CLUSTER_MAJOR_RADIUS_MAX 1.0f / HUBBLE_CONSTANT
#define POOR_CLUSTER_MAJOR_RADIUS_MASS_FACTOR 0.5f

#define POOR_CLUSTER_LUMINOSITY_MIN pow(10, 10.5) / pow(HUBBLE_CONSTANT, 2)
#define POOR_CLUSTER_LUMINOSITY_MAX pow(10, 12) / pow(HUBBLE_CONSTANT, 2)
#define POOR_CLUSTER_LUMINOSITY_MASS_FACTOR 0.5f

// TODO: This min value is made up as all I have found so far is that poor clusters are <= 2 kEv
#define POOR_CLUSTER_TEMPERATURE_MIN 1.85f * 1000.0f / BOLTZMAN_CONSTANT_EV_K
#define POOR_CLUSTER_TEMPERATURE_MAX 2.0f * 1000.0f / BOLTZMAN_CONSTANT_EV_K
#define POOR_CLUSTER_TEMPERATURE_MASS_FACTOR 0.5f

class Cluster;
class Supercluster;
class Game;

class ClusterFactory {
public:
	static ClusterFactory* getInstance();
	Cluster* create(Supercluster*, std::vector<float>);
	bool generateIsRich();
	float generateMass(bool, std::vector<float>);
	float generateLuminosity(bool, std::vector<float>, float);
	float generateMajorRadius(bool, std::vector<float>, float);
	float generateMinorRadius(bool, std::vector<float>, float);
	float generateTemperature(bool, std::vector<float>, float);
	long generateChildCount(std::vector<float>);

protected:
	static ClusterFactory* _instance;
	Cluster* _cluster;
	Game* _game;

	ClusterFactory(Game*);
};