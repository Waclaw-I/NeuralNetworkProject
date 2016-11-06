#include "Neuron.h"


Neuron::Neuron(int entriesAmount)
{
	for (int i = 0; i < entriesAmount; ++i)
	{
		entries.push_back(Input());
	}
}
Neuron::Neuron(int entriesAmount, bool isInInputLayer)
{
	for (int i = 0; i < entriesAmount; ++i)
	{
		if (isInInputLayer) entries.push_back(Input(true)); // weights are now equal 1
		else entries.push_back(Input());
	}
}

std::vector<Input> & Neuron::getEntries() { return this->entries; }
double Neuron::getOutputValue() const { return this->outputValue; }
double Neuron::getTargetValue() const { return this->targetValue; }
int Neuron::getEntriesAmount() const { return this->entries.size(); }
void Neuron::setTargetValue(double targetValue) { this->targetValue = targetValue; }
void Neuron::calculateSignalError() { this->signalError = this->targetValue - this->outputValue; }
double Neuron::getSignalError() { return this->signalError; }
void Neuron::setSignalError(double error) { this->signalError = error; }
double Neuron::calculateSum() 
{
	this->entriesSumValue = 0;
	for (auto entry : entries)
		this->entriesSumValue += entry.getReturnValue();
	return this->entriesSumValue;
}

double Neuron::derivativeFunc()
{
	return 1; // wont affect anything if not overriden
}

void Neuron::setOutput(double value) { this->outputValue = value; }