#include "Random.h"
#include "PerlinNoise.h"
#include "SimplexNoise.h"
#include <numeric>
#include <vector>

Random* Random::_instance = nullptr;

Random* Random::getInstance() {
	if (_instance) {
		return _instance;
	}

	return _instance = new Random();
}

Random::Random() {
	_perlinNoise = new PerlinNoise();
	_simplexNoise = new SimplexNoise();
}

PerlinNoise* Random::getPerlinNoise()
{
	return _perlinNoise;
}

SimplexNoise* Random::getSimplexNoise()
{
	return _simplexNoise;
}

float Random::getRandomNumber(std::vector<float> coordinate, int mutation)
{
	double number = sin(std::inner_product(coordinate.begin(), coordinate.end(), this->seed.begin(), 0.0)) * (43758.5453123f + (float)mutation * 100.0f);
	return abs(modf(number, new double()));
}

float Random::getRandomNumber(const std::vector<float>, const int, Distribution)
{
	return 0.0f;
}

float Random::getRandomNumber(std::vector<float> coordinate, int mutation, float floor, float ceiling) {
	return getRandomNumber(coordinate, mutation, floor, ceiling, Distribution::uniform);
}

float Random::getRandomNumber(const std::vector<float> coordinate, const int mutation, const float floor, const float ceiling, Distribution distribution)
{
	float result = getRandomNumber(coordinate, mutation);
	if (distribution == Distribution::uniform) {
		return floor + (ceiling - floor) * result;
	}

	if (distribution == Distribution::squared) {
		return floor + (ceiling - floor) * pow(result, 2);
	}

	if (distribution == Distribution::inverseSquared) {
		return floor + (ceiling - floor) * (1 - pow(result, 2));
	}
}

float Random::getWeightedRandomNumber(const std::vector<float> coordinate, const int mutation, const float floor, const float ceiling, const float randomWeight, const float externalFactor) {
	return getWeightedRandomNumber(coordinate, mutation, floor, ceiling, randomWeight, externalFactor, Distribution::uniform);
}

float Random::getWeightedRandomNumber(const std::vector<float> coordinate, const int mutation, const float floor, const float ceiling, const float randomWeight, const float externalFactor, Distribution distribution)
{
	return floor + (ceiling - floor) * (getRandomNumber(coordinate, mutation) * randomWeight + (1 - randomWeight) * externalFactor, distribution);
}

int Random::getNextSeed()
{
	return ++_seed;
}

void Random::resetSeed()
{
	_seed = 0;
}
