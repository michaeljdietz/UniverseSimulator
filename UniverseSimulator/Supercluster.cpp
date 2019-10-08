#include "Supercluster.h"
#include "Cluster.h"
#include "Game.h"
#include "ClusterFactory.h"
#include <cmath>

Supercluster::Supercluster(Game* game)
	: AstronomicalObject(game)
{
	_objectType = "supercluster";
	_childType = "cluster";
}

std::vector<float> Supercluster::getChildPosition(long refId) {
	return {
		floor((float) refId / pow(_axisCoordinateCount, 2.0f)),
		fmod(floor((float) refId / _axisCoordinateCount), _axisCoordinateCount),
		fmod((float)refId, _axisCoordinateCount)
	};
}

Cluster* Supercluster::createChild(const long refId)
{
	return ClusterFactory::getInstance()->create(this, getChildPosition(refId));
}