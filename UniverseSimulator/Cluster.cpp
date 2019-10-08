#include "Cluster.h"

Cluster::Cluster(Game* game)
	: AstronomicalObject(game)
{
	_objectType = "cluster";
	_childType = "galaxy";
}

std::vector<float> Cluster::getChildPosition(long refId) {
	return {
		floor((float)refId / pow(_axisCoordinateCount, 2.0f)),
		fmod(floor((float)refId / _axisCoordinateCount), _axisCoordinateCount),
		fmod((float)refId, _axisCoordinateCount)
	};
}
