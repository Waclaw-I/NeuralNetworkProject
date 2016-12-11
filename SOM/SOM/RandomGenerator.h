#pragma once
#include <random>

class RandomGenerator
{
public:
	RandomGenerator(double minWeightValue, double maxWeightValue);

	static std::random_device * rd;
	static std::mt19937 * generator;

	static double getRandomNumber();

private:
	static double minWeightValue;
	static double maxWeightValue;
};
