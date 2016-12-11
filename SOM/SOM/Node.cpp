#include "Node.h"
#include "RandomGenerator.h"

Node::Node(int x, int y, int weightsNum)
	: x(x),
	  y(y)
{
	for (int i = 0; i < weightsNum; ++i)
	{
		this->weights.push_back(RandomGenerator::getRandomNumber());
	}
}


double Node::getDistance(const std::vector<double> & inputVector)
{
	double dist = 0;

	for (int i = 0; i < weights.size(); ++i)
	{
		dist += std::pow((inputVector[i] - weights[i]), 2);
	}

	return std::sqrt(dist);
}

void Node::adjustWeights(const std::vector<double> & target,
					     const double learningRate,
						 const double influence)
{
	for (int i = 0; i < target.size(); ++i)
	{
		weights[i] += learningRate * influence * (target[i] - weights[i]);
	}
}