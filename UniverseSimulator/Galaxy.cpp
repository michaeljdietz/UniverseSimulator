#include "Galaxy.h"

Galaxy::Galaxy(Game* game)
	: AstronomicalObject(game)
{
	_objectType = "galaxy";
	_childType = "solarsystem";
}

std::vector<float> Galaxy::getChildPosition(long refId) {
	return {
		floor((float)refId / pow(_axisCoordinateCount, 2.0f)),
		fmod(floor((float)refId / _axisCoordinateCount), _axisCoordinateCount),
		fmod((float)refId, _axisCoordinateCount)
	};
}