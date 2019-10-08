#pragma once

#define _USE_MATH_DEFINES

#include "AstronomicalObject.h"
#include "Supercluster.h"
#include <cmath>
#include <vector>
#include "stdafx.h"

#define BIG_BANG_SPIN_X 0.07f
#define BIG_BANG_SPIN_Y 0.00f
#define BIG_BANG_SPIN_Z 0.00f

#define INVERSE_OF_BIG_BANG_SPIN_X_ADJUSTMENT 1.0f / ((1.0f - BIG_BANG_SPIN_X) * 3.0f)
#define INVERSE_OF_BIG_BANG_SPIN_Y_ADJUSTMENT 1.0f / ((1.0f - BIG_BANG_SPIN_Y) * 3.0f)
#define INVERSE_OF_BIG_BANG_SPIN_Z_ADJUSTMENT 1.0f / ((1.0f - BIG_BANG_SPIN_Z) * 3.0f)

#define SINGLE_COORDINATE_PERMUTATIONS ceil(cbrt((float) _childCount))

#define X_COORDINATE_OFFSET 1.0f / pow(SINGLE_COORDINATE_PERMUTATIONS, 2.0f)
#define Y_COORDINATE_OFFSET 1.0f / SINGLE_COORDINATE_PERMUTATIONS

// TODO: These should reflect baryonic acoustic oscillations!!!!
// TODO: The alternative is that the actual CHILDCOUNT for each cell should reflect BAOs.

#define CHILD_POSITION_BY_REFID_X -1 * SINGLE_COORDINATE_PERMUTATIONS / 2 + floor((float)refId * X_COORDINATE_OFFSET)
#define CHILD_POSITION_BY_REFID_Y -1 * SINGLE_COORDINATE_PERMUTATIONS / 2 + fmod(floor((float)refId * Y_COORDINATE_OFFSET), SINGLE_COORDINATE_PERMUTATIONS)
#define CHILD_POSITION_BY_REFID_Z -1 * SINGLE_COORDINATE_PERMUTATIONS / 2 + fmod((float)refId, SINGLE_COORDINATE_PERMUTATIONS)
// #define CHILD_POSITION_BY_REFID_X floor((3.0f * sin((float)refId * INVERSE_OF_BIG_BANG_SPIN_X_ADJUSTMENT) + (float)refId - ((float)_childCount / 2.0f)) * X_COORDINATE_OFFSET)
// #define CHILD_POSITION_BY_REFID_Y fmod(floor((3.0f * sin((float)refId * INVERSE_OF_BIG_BANG_SPIN_Y_ADJUSTMENT) + (float)refId - ((float)_childCount / 2.0f)) * Y_COORDINATE_OFFSET), SINGLE_COORDINATE_PERMUTATIONS)
// #define CHILD_POSITION_BY_REFID_Z fmod(3.0f * sin((float)refId * INVERSE_OF_BIG_BANG_SPIN_Z_ADJUSTMENT) + (float)refId - ((float)_childCount / 2.0f), SINGLE_COORDINATE_PERMUTATIONS)

class Universe : public AstronomicalObject {
public:
	static constexpr float cellRadius = 14321; // Mpc

	Universe(Game*);
	std::vector<float> getChildPosition(const long);
	std::vector<float> getNextPosition(long);
	std::vector<float> getPreviousPosition(long);
	Supercluster* createChild(const long);
};