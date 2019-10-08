#pragma once
#include "AstronomicalObject.h"
#include "Cluster.h"
#include "SuperclusterFactory.h"

// 10^-5 rich clusters/Mpc^3

class Supercluster : public AstronomicalObject {
public:
	static constexpr float cellRadius = 50;

	Supercluster(Game*);
	std::vector<float> getChildPosition(long refId);
	Cluster* createChild(const long refId);

protected:
	long _richClusterCount;
	float _richMass;
	float _richLuminosity;
	float _richMajorRadius;
	float _richMinorRadius;
	float _richTemperature;
	friend class SuperclusterFactory;
};