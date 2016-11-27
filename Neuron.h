#pragma once
#include <vector>

#include "Input.h"


class Neuron
{
public:
	Neuron(int entriesAmount);
	Neuron(int entriesAmount, bool isInInputLayer);
	std::vector<Input> & getEntries();
	int getEntriesAmount() const;
	double getOutputValue() const;
	void setOutput(double value); // for input neurons only. With this, there is no need for setting up weights for the first layer
	double getTargetValue() const;
	void setTargetValue(double targetValue);
	void calculateSignalError();
	void calculateAdalineSignalError();
	void setSignalError(double error);
	void setAdalineSignalError(double error);
	double getAdalineSignalError();
	double getSignalError();
	virtual void calculateOutput() = 0;
	virtual void updateWeights() = 0;
protected:
	std::vector<Input> entries;
	double outputValue;
	double targetValue;
	double signalError;
	double adalineSignalError;
	double entriesSumValue;
	double calculateSum();
	virtual double derivativeFunc();

};