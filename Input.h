#pragma once

class Input
{
public:
	Input(double minimumWeightValue, double maximumWeightValue);

	double getWeight();
	double getValue();

	void setValue(double value);
	void setWeight(double weight);

	double getResult();
	double randomizeWeight(double minimumWeightValue, double maximumWeightValue);

private:
	double value;
	double weight;
};