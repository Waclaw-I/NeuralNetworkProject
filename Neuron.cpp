#include "Neuron.h"

double const Neuron::minimumWeightValue = -1.0;
double const Neuron::maximumWeightValue = 1.0;
double const Neuron::eta = 0.15;
double const Neuron::alpha = 0.5;

Neuron::Neuron(int inputsAmount, bool isFirst)
{
	if (isFirst)
	{
		inputs.push_back(Input(1, 1));
	}
	else
	{
		for (int i = 0; i < inputsAmount; i++)
		{
			inputs.push_back(Input(minimumWeightValue, maximumWeightValue));
		}
	}
}

void Neuron::activationFunction()
{ 
	//this->outputValue = tanh(calculateSum()); 

	if (calculateSum() > 0.5) this->outputValue = 1;
	else this->outputValue = 0;
}

double Neuron::calculateSum() 
{
	double sum = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		sum += this->inputs[i].getValue();
	}
	return sum;
}

void Neuron::updateWeights()
{
	for (int i = 0; i < inputs.size(); i++)
	{
		double newWeight =
			inputs[i].getWeight()
			+ (targetValue - outputValue)
			* eta
			* inputs[i].getValue();

		inputs[i].setWeight(newWeight);
	}
}

vector <Input> & Neuron::getInputs() { return this->inputs; }
double Neuron::getOutputValue() { return this->outputValue; }

double Neuron::getTargetValue() { return this->targetValue; }
void Neuron::setTargetValue(double targetValue) { this->targetValue = targetValue; }
