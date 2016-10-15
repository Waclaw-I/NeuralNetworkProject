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

private:
	double value;
	double weight;
};
