#pragma once
#include "AstronomicalObject.h"
#include <vector>

// most are poor (less than 1000 galaxies)
// poor are less than 1 Mpc diameter
// poor contain many spiral galaxies


// rich are 3-10 Mpc in diameter
// rich contain many elliptical galaxies, few spiral
// center of rich usually contains one, two, or three giant elliptical galaxies
// rich contain very hot gas distributed evenly throughout the cluster (upwards of 6x amount of gas -> star mass)

// data from: https://ned.ipac.caltech.edu/level5/Sept01/Bahcall2/Bahcall2.html
// 0.15-2.85 Mpc radius
// 4.5x10^12 - 1.4x10^15

class ClusterFactory;

class Cluster : public AstronomicalObject {
public:
	static constexpr float cellRadius = 10;

	Cluster(Game*);
	
protected:
	bool _isRich;

	std::vector<float> getChildPosition(const long);
	friend class ClusterFactory;
};