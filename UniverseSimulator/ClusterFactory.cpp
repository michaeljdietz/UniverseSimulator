#include "ClusterFactory.h"
#include "Random.h"
#include "Game.h"
#include "Cluster.h"
#include "Supercluster.h"
#include "Utility.h"

ClusterFactory* ClusterFactory::_instance;

ClusterFactory::ClusterFactory(Game* game) {
	_game = game;
}

ClusterFactory* ClusterFactory::getInstance() {
	if (_instance) {
		return _instance;
	}

	return _instance = new ClusterFactory(Game::getInstance());
}

Cluster* ClusterFactory::create(Supercluster* parent, std::vector<float> origin) {
	// TODO: Anything remaining after all children have been generated is extragalactic -- but when do we generate THAT stuff
	Cluster* _cluster = new Cluster(_game);
	_cluster->_parent = parent;

	_cluster->_childCount = generateChildCount(origin);
	_cluster->_axisCoordinateCount = floor(cbrt((float)_cluster->_childCount)) + 1;

	bool isRich = generateIsRich();
	_cluster->_mass = generateMass(isRich, origin);
	
	float massRatio;
	if (isRich) {
		massRatio = _cluster->_mass / RICH_CLUSTER_MASS_MAX;
	}
	else {
		massRatio = _cluster->_mass / POOR_CLUSTER_MASS_MAX;
	}

	_cluster->_luminosity = generateLuminosity(isRich, origin, massRatio);
	_cluster->_majorRadius = generateMajorRadius(isRich, origin, massRatio);
	_cluster->_minorRadius = generateMinorRadius(isRich, origin, massRatio);
	_cluster->_temperature = generateTemperature(isRich, origin, massRatio);

	return _cluster;
}

long ClusterFactory::generateChildCount(const std::vector<float> origin) {
	// TODO: how do we calculate total # of cells?  fixed size for clusters?  fixed size for superclusters?

	float probability = Random::getInstance()->getRandomNumber(origin, Random::getInstance()->getNextSeed());
	float distance = Utility::distance(origin, { 0.0f, 0.0f, 0.0f });

	// decrease probabiliy as distance increases (offset by 1 to avoid fractional effects)
	probability *= 1 / (1 + distance / Cluster::cellRadius);	

	if (probability) {
		// rich
		return Random::getInstance()->getRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			RICH_CLUSTER_GALAXY_MIN,
			RICH_CLUSTER_GALAXY_MAX
		);
	}
	else if (true) {
		// poor
		return Random::getInstance()->getRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			POOR_CLUSTER_GALAXY_MIN,
			POOR_CLUSTER_GALAXY_MAX
		);
	}

	return 0;
}

bool ClusterFactory::generateIsRich() {
	// TODO: Needs to be most probable nearest center of cluster
	// TODO: Only exactly as many as are in the parent supercluster should generate
	// TODO: Based on parent origin random number

	return Random::getInstance()->getRandomNumber(_cluster->_origin, Random::getInstance()->getNextSeed()) <= RICH_CLUSTER_PERCENTAGE * _cluster->_childCount;
}

float ClusterFactory::generateMass(const bool isRich, const std::vector<float> origin) {
	// see https://ned.ipac.caltech.edu/level5/Sept01/Bahcall2/Bahcall7.html
	// TODO: all of these calculations are the result of a uniform distribution over an acceptable range -- there should be more precise distribution functions available
	// TODO: currently this only allows for a SINGLE rich cluster -- this is most likely wrong, as rich clusters themselves tend to cluster
	if (isRich) {
		return Random::getInstance()->getRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			RICH_CLUSTER_MASS_MIN,
			RICH_CLUSTER_MASS_MAX
		);
	}

	// TODO: this should be a normal distribution, not a uniform distribution (chance of every poor cluster being huge not as much as every poor cluster being average)
	// TODO: perhaps there is a relationship between number of sub-clusters and total mass of the supercluster...
	return Random::getInstance()->getRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			POOR_CLUSTER_MASS_MIN,
			POOR_CLUSTER_MASS_MAX
		);
}

float ClusterFactory::generateMajorRadius(const bool isRich, const std::vector<float> origin, const float massRatio) {
	if (isRich) {
		return Random::getInstance()->getWeightedRandomNumber(
				origin,
				Random::getInstance()->getNextSeed(),
				RICH_CLUSTER_MAJOR_RADIUS_MIN,
				RICH_CLUSTER_MAJOR_RADIUS_MAX,
				RICH_CLUSTER_MAJOR_RADIUS_MASS_FACTOR,
				massRatio
			);
	}
	
	return Random::getInstance()->getWeightedRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			POOR_CLUSTER_MAJOR_RADIUS_MIN,
			POOR_CLUSTER_MAJOR_RADIUS_MAX,
			POOR_CLUSTER_MAJOR_RADIUS_MASS_FACTOR,
			massRatio
		);
}

float ClusterFactory::generateLuminosity(const bool isRich, const std::vector<float> origin, const float massRatio) {
	if (isRich) {
		return Random::getInstance()->getWeightedRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			RICH_CLUSTER_LUMINOSITY_MIN,
			RICH_CLUSTER_LUMINOSITY_MAX,
			RICH_CLUSTER_LUMINOSITY_MASS_FACTOR,
			massRatio
		);
	}

	return Random::getInstance()->getWeightedRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			POOR_CLUSTER_LUMINOSITY_MIN,
			POOR_CLUSTER_LUMINOSITY_MAX,
			POOR_CLUSTER_LUMINOSITY_MASS_FACTOR,
			massRatio
		);	
}

float ClusterFactory::generateMinorRadius(const bool isRich, const std::vector<float> origin, const float massRatio) {
	return generateMajorRadius(isRich, origin, massRatio);
}

float ClusterFactory::generateTemperature(const bool isRich, const std::vector<float> origin, const float massRatio) {
	if (isRich) {
		return Random::getInstance()->getWeightedRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			RICH_CLUSTER_TEMPERATURE_MIN,
			RICH_CLUSTER_TEMPERATURE_MAX,
			RICH_CLUSTER_TEMPERATURE_MASS_FACTOR,
			massRatio
		);
	}

	return Random::getInstance()->getWeightedRandomNumber(
			origin,
			Random::getInstance()->getNextSeed(),
			POOR_CLUSTER_TEMPERATURE_MIN,
			POOR_CLUSTER_TEMPERATURE_MAX,
			POOR_CLUSTER_TEMPERATURE_MASS_FACTOR,
			massRatio
		);
}