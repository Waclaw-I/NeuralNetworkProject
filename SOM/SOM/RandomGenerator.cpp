#include "RandomGenerator.h"
#include <random>
#include "time.h"

std::mt19937 * RandomGenerator::generator = new std::mt19937(time(0));
double RandomGenerator::minWeightValue = 0;
double RandomGenerator::maxWeightValue = 1;

RandomGenerator::RandomGenerator(double minWeightValue, double maxWeightValue)
{
	minWeightValue = minWeightValue;
	maxWeightValue = maxWeightValue;
}

double RandomGenerator::getRandomNumber()
{
	std::uniform_real_distribution<> dis(minWeightValue, maxWeightValue);
	return dis(*generator);
}

