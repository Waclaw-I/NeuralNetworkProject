#include "RandomEngine.h"
#include <random>
#include "time.h"

std::mt19937 * RandomEngine::generator = new std::mt19937(time(0));
double RandomEngine::minWeightValue = -1;
double RandomEngine::maxWeightValue = 1;

RandomEngine::RandomEngine(double minWeightValue, double maxWeightValue)
{
    minWeightValue = minWeightValue;
    maxWeightValue = maxWeightValue;
}

double RandomEngine::getRandomNumber()
{
    std::uniform_real_distribution<> dis(minWeightValue, maxWeightValue);
    return dis(*generator);
}

