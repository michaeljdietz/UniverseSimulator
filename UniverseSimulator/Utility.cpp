#include "Utility.h"

float Utility::distance(std::vector<float> a, std::vector<float> b)
{
	if (a.size() != b.size()) {
		return INFINITY;
	}

	return sqrt(pow(b.at(0) - a.at(0), 2) + pow(b.at(1) - a.at(1), 2) + pow(b.at(2) - a.at(2), 2));
}
