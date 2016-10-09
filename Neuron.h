#pragma once
#include <vector>

#include "Entry.h"

using namespace std;

class Neuron
{

public:
	Neuron(int entriesAmount);

	void activationFunction();
	void updateWeights();
	double calculateSum();
	double calculateOutputGradient();

	vector<Entry> & getEntries();
	double getOutputValue();
	double getTargetValue();
	void setTargetValue(double targetValue);

	
	double transferFunctionDerivative(double x);

private:

	vector<Entry> entries;
	double outputValue;
	double targetValue;

	static double const minimumWeightValue;
	static double const maximumWeightValue;
	static double const eta; // learning rate
	static double const alpha; // momentum
};