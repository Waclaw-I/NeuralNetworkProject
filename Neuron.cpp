#include "Neuron.h"

double const Neuron::minimumWeightValue = -1.0;
double const Neuron::maximumWeightValue = 1.0;
double const Neuron::eta = 0.15;
double const Neuron::alpha = 0.5;

Neuron::Neuron(int entriesAmount)
{
	for (int i = 0; i < entriesAmount; i++)
	{
		entries.push_back(Entry(minimumWeightValue, maximumWeightValue));
	}
}

void Neuron::activationFunction() { this->outputValue = tanh(calculateSum()); }

double Neuron::calculateSum() 
{
	double sum = 0;
	for (int i = 0; i < entries.size(); i++)
	{
		sum += this->entries[i].getValue();
	}
	return sum;
}

double Neuron::calculateOutputGradient()
{
	double delta = this->targetValue - this->outputValue;
	return delta * transferFunctionDerivative(outputValue);
}

double Neuron::transferFunctionDerivative(double x)
{
	return (1.0 - x*x);
}

void Neuron::updateWeights()
{
	for (int i = 0; i < entries.size(); i++)
	{
		double newWeight =
			entries[i].getWeight()
			+ (targetValue - outputValue)
			* entries[i].getInput();

		entries[i].setWeight(newWeight);
	}
}

vector <Entry> & Neuron::getEntries() { return this->entries; }
double Neuron::getOutputValue() { return this->outputValue; }

double Neuron::getTargetValue() { return this->targetValue; }
void Neuron::setTargetValue(double targetValue) { this->targetValue = targetValue; }
