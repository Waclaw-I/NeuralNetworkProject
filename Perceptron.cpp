#include "Perceptron.h"
#include "RandomGenerator.h"

Perceptron::Perceptron(int entriesAmount): Neuron(entriesAmount) 
{
	this->bias = RandomGenerator::getRandomNumber();
}

void Perceptron::calculateOutput()
{
	// is this even correct? Is bias the only difference in learning methods between mcCulloh-Pitts and Perceptron?
	calculateSum() + bias >= 0 ? outputValue = 1 : outputValue = 0;
}

// 0.15 is learning rate - todo: move this to some sort of global const
void Perceptron::updateWeights()
{
	for (auto &entry : entries)
	{
		double newWeight = entry.getWeight() + 0.15 * (this->targetValue - this->outputValue) * entry.getEntryValue();
		entry.setWeight(newWeight);
	}
	bias += 0.15 * (this->targetValue - this->outputValue);
}