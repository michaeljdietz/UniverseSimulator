#pragma once
#include <vector>

class PerlinNoise;
class SimplexNoise;

class Random {
public:
	enum Distribution {
		uniform,		// Evenly distributed between 0 and 1 (or between range values)
		squared,		// Distributed with decreasing density as the value approaches 1 (or the range max)
		inverseSquared  // Distributed with increasing density as the value approaches 1 (or the range max)
	};

	static Random* getInstance();
	PerlinNoise* getPerlinNoise();
	SimplexNoise* getSimplexNoise();
	float getRandomNumber(const std::vector<float>, const int);
	float getRandomNumber(const std::vector<float>, const int, Distribution);
	float getRandomNumber(const std::vector<float>, const int, const float, const float);
	float getRandomNumber(const std::vector<float>, const int, const float, const float, Distribution);
	float getWeightedRandomNumber(const std::vector<float>, const int, const float, const float, const float, const float);
	float getWeightedRandomNumber(const std::vector<float>, const int, const float, const float, const float, const float, Distribution);
	int getNextSeed();
	void resetSeed();

protected:
	Random();
	static Random* _instance;
	std::vector<float> seed{ 12.9898f, 78.233f, 294.2876f };
	PerlinNoise* _perlinNoise;
	SimplexNoise* _simplexNoise;
	int _seed;
};