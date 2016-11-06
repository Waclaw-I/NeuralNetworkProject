#include "McCullohPitts.h"

McCullohPitts::McCullohPitts(int entriesAmount):Neuron(entriesAmount) {}
McCullohPitts::McCullohPitts(int entriesAmount, bool isInInputLayer) : Neuron(entriesAmount, isInInputLayer) {}

void McCullohPitts::calculateOutput()
{
	double mian = 1 + exp(-calculateSum());
	//this->outputValue = tanh(calculateSum());
	this->outputValue = (1 / mian);
}

double McCullohPitts::derivativeFunc()
{
	return (1.0 - this->outputValue) * (this->outputValue);
}

void McCullohPitts::updateWeights()
{
	for (auto &entry : entries)
	{
		double newWeight = entry.getWeight() + 0.15 * (this->targetValue - this->outputValue) * derivativeFunc() * entry.getEntryValue();
		entry.setWeight(newWeight);
	}
}