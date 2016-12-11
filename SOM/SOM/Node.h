#pragma once

#include <vector>

class Node
{
public:
	Node(int x, int y, int weightsNum);

	double getDistance(const std::vector<double> & inputVector);

	void adjustWeights(const std::vector<double> & target,
					   const double learningRate,
					   const double influence);

	std::vector<double> weights;

	// position
	double x;
	double y;
};