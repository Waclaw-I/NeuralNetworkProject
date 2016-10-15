#pragma once
#include <vector>

#include "Input.h"

using namespace std;

class Neuron
{

public:
	Neuron(int inputsAmount, bool isFirst = false);

	void activationFunction();
	void updateWeights();
	double calculateSum();

	vector<Input> & getInputs();
	double getOutputValue();
	double getTargetValue();
	void setTargetValue(double targetValue);


private:

	vector<Input> inputs;
	double outputValue;
	double targetValue;
	bool isFirst;

	static double const minimumWeightValue;
	static double const maximumWeightValue;
	static double const eta; // learning rate
	static double const alpha; // momentum
};
