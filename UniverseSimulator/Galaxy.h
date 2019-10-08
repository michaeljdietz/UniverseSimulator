#pragma once
#include "AstronomicalObject.h"
#include <vector>

#define GALAXY_RADIUS_MIN = 0.5 // Kpc
#define GALAXY_RADIUS_MAX = 100 // Kpc

#define GALAXY_MIN_CHILD_COUNT = 10000000 // 10 million OR LESS
#define GALAXY_MAX_CHILD_COUNT = 1000000000000; // 1 trillion OR MORE

// star temps run from 2500K to 50,000K
// distance between stars is approx 10 million times diameter of a star

class GalaxyFactory;

class Galaxy : public AstronomicalObject {
public:
	Galaxy(Game*);

protected:
	std::vector<float> getChildPosition(const long);
	friend class GalaxyFactory;
};