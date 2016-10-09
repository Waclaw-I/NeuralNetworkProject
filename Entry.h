#pragma once

class Entry
{
public:
	Entry(double minimumWeightValue, double maximumWeightValue);

	double getWeight();
	double getInput();

	void setInput(double input);
	void setWeight(double weight);
	void updateWeight(double weight);

	double randomizeWeight(double minimumWeightValue, double maximumWeightValue);

	double getValue();

private:
	double input;
	double weight;
};