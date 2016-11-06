#pragma once
#include "Neuron.h"

class McCullohPitts : public Neuron
{
public:
	McCullohPitts(int entriesAmount);
	McCullohPitts(int entriesAmount, bool isInInputLayer);
	void calculateOutput() override;
	void updateWeights() override;
	double derivativeFunc() override;
private:

};