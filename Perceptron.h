#pragma once

#include "Neuron.h"

class Perceptron : public Neuron
{
public:
	Perceptron(int entriesAmount);
	void calculateOutput() override;
	void updateWeights() override;

private:
	double bias;
};