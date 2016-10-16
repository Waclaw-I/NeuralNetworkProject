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
	void setSignalError(double signalError);
	double calculateSum();

	vector<Input> & getInputs();
	double getOutputValue();
	double getTargetValue();
	double getSignalError();
	void setTargetValue(double targetValue);


private:

	vector<Input> inputs;
	double outputValue;
	double targetValue;
	double signalError;
	bool isFirst;

	static double const eta; // learning rate
	//static double const alpha; // momentum
};
