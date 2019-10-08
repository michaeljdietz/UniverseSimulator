#include "Universe.h"
#include "Supercluster.h"
#include "SuperclusterFactory.h"
#include "Game.h"
#include "Random.h"
#include <numeric>
#include <vector>

Universe::Universe(Game* game)
: AstronomicalObject(game)
{
	_objectType = "universe";
	_childType = "supercluster";
	_childCount = 10000000 / 0.03; // 10,000,000 superclusters -- voids make up the other 97%
	_mass = 7.54109899 * pow(10, 22); // solar masses
	_temperature = 2.348635552555e-7; // keV
	_luminosity = pow(10, 86); // electron volts -- TODO: needs to be converted to solar luminosity...
	_majorRadius = 14250; // mpc
	_minorRadius = 14250; // mpc
}

// TODO: Add "random" variability so that coordinates are less precisely quantized
// TODO: Find size of each quantization (distance between each possibile x value)... vary the coordinate by any amount between 0 (min) and quanization (max)
// TODO: Use the original coordinate as the random number seed
std::vector<float> Universe::getChildPosition(const long refId) {
	std::vector<float> current, previous, next;

	current = {
		CHILD_POSITION_BY_REFID_X,
		CHILD_POSITION_BY_REFID_Y,
		CHILD_POSITION_BY_REFID_Z
	};

	previous = getPreviousPosition(refId);
	next = getNextPosition(refId);

	float xAdj = Random::getInstance()->getRandomNumber(current, Random::getInstance()->getNextSeed(), previous.at(0) - current.at(0), next.at(0) - current.at(0));
	float yAdj = Random::getInstance()->getRandomNumber(current, Random::getInstance()->getNextSeed(), previous.at(1) - current.at(1), next.at(1) - current.at(1));
	float zAdj = Random::getInstance()->getRandomNumber(current, Random::getInstance()->getNextSeed(), previous.at(2) - current.at(2), next.at(2) - current.at(2));

	// we divide the adjustments by 4 so that there isn't any overlap between neighboring objects
	// todo: this should actually divide by something related to cell size

	return {
		current.at(0) + xAdj / 4,
		current.at(1) + yAdj / 4,
		current.at(2) + zAdj / 4
	};
}

std::vector<float> Universe::getNextPosition(long refId) {
	long xRefId = refId + SINGLE_COORDINATE_PERMUTATIONS * SINGLE_COORDINATE_PERMUTATIONS,
		yRefId = refId + SINGLE_COORDINATE_PERMUTATIONS,
		zRefId = refId + 1;

	float x, y, z;

	refId = xRefId;
	x = CHILD_POSITION_BY_REFID_X;

	refId = yRefId;
	y = CHILD_POSITION_BY_REFID_Y;

	refId = zRefId;
	z = CHILD_POSITION_BY_REFID_Z;

	return { x, y, z };
}

std::vector<float> Universe::getPreviousPosition(long refId) {
	long xRefId = refId - SINGLE_COORDINATE_PERMUTATIONS * SINGLE_COORDINATE_PERMUTATIONS,
		yRefId = refId - SINGLE_COORDINATE_PERMUTATIONS,
		zRefId = refId - 1;

	if (xRefId < 0) {
		xRefId = refId;
	}

	if (yRefId < 0) {
		yRefId = refId;
	}

	if (zRefId < 0) {
		zRefId = refId;
	}

	float x, y, z;

	refId = xRefId;
	x = CHILD_POSITION_BY_REFID_X;

	refId = yRefId;
	y = CHILD_POSITION_BY_REFID_Y;

	refId = zRefId;
	z = CHILD_POSITION_BY_REFID_Z;

	return { x, y, z };

}

Supercluster* Universe::createChild(const long refId)
{
	SuperclusterFactory* factory = SuperclusterFactory::getInstance();
	return factory->create(this, getChildPosition(refId));
}
