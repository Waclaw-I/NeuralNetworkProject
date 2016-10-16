#include "Neuron.h"

#include "math.h"

double const Neuron::eta = 0.15;
//double const Neuron::alpha = 0.5;

Neuron::Neuron(int inputsAmount, bool isFirst)
{
    this->isFirst = isFirst;
	if (isFirst)
	{
		inputs.push_back(Input(isFirst));
	}
	else
	{
		for (int i = 0; i < inputsAmount; i++)
		{
			inputs.push_back(Input());
		}
	}
}

void Neuron::activationFunction()
{
	this->outputValue = tanh(calculateSum());

	//if (calculateSum() > 0.5) this->outputValue = 1;
	//else this->outputValue = 0;
}

double Neuron::calculateSum()
{
	double sum = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		sum += this->inputs[i].getResult();
	}
	return sum;
}

void Neuron::updateWeights()
{ // TODO: fix this one
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
double Neuron::getOutputValue()
{
    if (!isFirst)
    {
        activationFunction();
        return this->outputValue;
    }
    else return calculateSum();
}

double Neuron::getTargetValue() { return this->targetValue; }
void Neuron::setTargetValue(double targetValue) { this->targetValue = targetValue; }

void Neuron::setSignalError(double signalError) { this->signalError = signalError; }
double Neuron::getSignalError() { return this->signalError; }
