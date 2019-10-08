#include "SuperclusterFactory.h"
#include "ClusterFactory.h"
#include "Supercluster.h"
#include "Universe.h"
#include "Random.h"
#include "Game.h"

// TODO: This file uses alot of similar logic to the methods in ClusterFactory (multiplies those values by child counts)
// TODO: We should unify the logic somehow so we don't have to make our changes in multiple places going forward

SuperclusterFactory* SuperclusterFactory::_instance;

SuperclusterFactory::SuperclusterFactory(Game* game) {
	_game = game;
}

SuperclusterFactory* SuperclusterFactory::getInstance()
{
	if (_instance) {
		return _instance;
	}

	return _instance = new SuperclusterFactory(Game::getInstance());
}

Supercluster* SuperclusterFactory::create(Universe* parent, const std::vector<float> origin)
{
	// inverse relationship between mass and radius??? not necessarily?  density instead?
	// frequent correlation between mass and luminosity
	// correlation between luminosity and temperature

	// bao length is about 490 million ly

	// voids have radius up to 50 Mpc
	// voids have a mean density less than a tenth of the average density of the universe
	// density = mass / pi*r^2

	// galaxies are 1000000 times more dense than average density of the universe

	// Supercluster number density =  10^-6*h^3/Mpc^3
	// Supercluster separation = 100/h Mpc

	// Largest supercluster is 150/h Mpc
	// 3% by volume of Universe
	// 97% voids!!!!
	// 54% of clusters are in a supercluster
	// that means 46% of superclusters are a single cluster (44.62% of all super-x objects)
	// supercluster size: 0.97 void, 0.46 * 0.03 single, 0.54 * 0.03 (2-15 clusters)
	Random::getInstance()->resetSeed();

	_supercluster = new Supercluster(Game::getInstance());
	_supercluster->setParent(parent);
	_supercluster->setOrigin(origin);

	_supercluster->_childCount = generateChildCount();
	_supercluster->_richClusterCount = generateRichClusterCount();
	_supercluster->_axisCoordinateCount = floor(cbrt((float)_supercluster->_childCount)) + 1;

	_supercluster->_richMass = generateRichMass();
	_supercluster->_mass = _supercluster->_richMass + generatePoorMass();

	_richMassRatio = 0;
	if (_supercluster->_richClusterCount > 0) {
		_richMassRatio = _supercluster->_richMass / _supercluster->_richClusterCount / RICH_CLUSTER_MASS_MAX;
	}

	_poorMassRatio = 0;
	if (_supercluster->_childCount - _supercluster->_richClusterCount > 0) {
		_poorMassRatio = (_supercluster->_mass - _supercluster->_richMass) / (_supercluster->_childCount - _supercluster->_richClusterCount) / POOR_CLUSTER_MASS_MAX;
	}

	_supercluster->_richMajorRadius = generateRichMajorRadius();
	_supercluster->_majorRadius = _supercluster->_richMajorRadius + generatePoorMajorRadius();

	_supercluster->_richLuminosity = generateRichLuminosity();
	_supercluster->_luminosity = _supercluster->_richLuminosity + generatePoorLuminosity();

	_supercluster->_richMinorRadius = generateRichMinorRadius();
	_supercluster->_minorRadius = _supercluster->_richMinorRadius + generatePoorMinorRadius();

	_supercluster->_richTemperature = generateRichTemperature();
	_supercluster->_temperature = _supercluster->_richTemperature + generatePoorTemperature();

	return _supercluster;
}

long SuperclusterFactory::generateChildCount() {
	// TODO: This should be changed to use Press–Schechter formalism to calculate object density (which is going to require a lot of complex mathematics and astrophysics theory background)

	// TODO: Shouldn't we allow for these to cluster by proximity to other superclusters
	// TODO: check neighbors seed value.  If greater than .97 then increase chance of one here
	// TODO: check neighbors' neighbors seed value.  If greater than .97 then increase chance of one here (a little less)
	// TODO: check neighbors' neighbors' neighbors' seed value.  If greater than .97 then increase chance of one here (a little less than less)
	// TODO: max increase to probability is an additional 3% (that would make it 100%!!!!??)
	// TODO: max decrease to probability should be the same?
	// TODO: OR should the increases/decreases be an inverse square distribution... meaning 3% increase, 6% decrease?

	float seed = Random::getInstance()->getRandomNumber(_supercluster->_origin, Random::getInstance()->getNextSeed());

	if (seed < 0.97) {
		return 0;
	}
	else if (seed < 0.97 + 0.03 * 0.46) {	// 97% void, 3% not... 46% of the 3% is a single cluster, the rest are clusters of clusters
		return 1;
	}
	else {
		return floor(MAX_CLUSTERS_PER_SUPERCLUSTER * (1.0f - seed)
			/ (1.0f - (PERCENT_VOID + PERCENT_CLUSTER * PERCENT_SINGLE_CLUSTER_SUPERCLUSTER)))
			+ 1.0f;
	}
}

long SuperclusterFactory::generateRichClusterCount() {
	// TODO: This needs to be fixed.  clustering is stronger with rich clusters... so it should be weighted by childCount some...
	// TODO: but without losing the % probability we achieve here.
	return Random::getInstance()->getRandomNumber(_supercluster->_origin, Random::getInstance()->getNextSeed()) <= RICH_CLUSTER_PERCENTAGE * _supercluster->_childCount;
}

float SuperclusterFactory::generateRichMass() {
	return _supercluster->_richClusterCount
		* ClusterFactory::getInstance()->generateMass(true, _supercluster->_origin);
}

float SuperclusterFactory::generatePoorMass() {
	return (_supercluster->_childCount - _supercluster->_richClusterCount)
		* ClusterFactory::getInstance()->generateMass(false, _supercluster->_origin);
}

float SuperclusterFactory::generateRichMajorRadius() {
	// TODO: Need to add space BETWEEN clusters (data needed)
	return _supercluster->_richClusterCount
		* ClusterFactory::getInstance()->generateMajorRadius(true, _supercluster->_origin, _richMassRatio);
}

float SuperclusterFactory::generatePoorMajorRadius() {
	// TODO: Need to add space BETWEEN clusters (data needed)
	return (_supercluster->_childCount - _supercluster->_richClusterCount)
		* ClusterFactory::getInstance()->generateMajorRadius(false, _supercluster->_origin, _poorMassRatio);
}

float SuperclusterFactory::generateRichLuminosity() {
	// TODO: currently this is weighted 50% on cluster mass... this is totally an UNEDUCATED guess and should have some substantiated relationship or mass / luminosity function
	return _supercluster->_richClusterCount
		* ClusterFactory::getInstance()->generateLuminosity(true, _supercluster->_origin, _richMassRatio);
}

float SuperclusterFactory::generatePoorLuminosity() {
	return (_supercluster->_childCount - _supercluster->_richClusterCount)
		* ClusterFactory::getInstance()->generateLuminosity(false, _supercluster->_origin, _poorMassRatio);
}

float SuperclusterFactory::generateRichMinorRadius() {
	return _supercluster->_richClusterCount
		* ClusterFactory::getInstance()->generateMinorRadius(true, _supercluster->_origin, _richMassRatio);
}

float SuperclusterFactory::generatePoorMinorRadius() {
	return (_supercluster->_childCount - _supercluster->_richClusterCount)
		* ClusterFactory::getInstance()->generateMinorRadius(false, _supercluster->_origin, _poorMassRatio);
}

float SuperclusterFactory::generateRichTemperature() {
	return _supercluster->_richClusterCount
		* ClusterFactory::getInstance()->generateTemperature(true, _supercluster->_origin, _richMassRatio);
}

float SuperclusterFactory::generatePoorTemperature() {
	return (_supercluster->_childCount - _supercluster->_richClusterCount)
		* ClusterFactory::getInstance()->generateTemperature(false, _supercluster->_origin, _poorMassRatio);
}