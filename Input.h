#pragma once

class Input
{
public:
	Input(double entryValue);
	Input(bool isInInputLayer);
	Input();

	double getWeight() const;
	void setWeight(double weight);
	void updateWeight(double delta);
	void setEntryValue(double entryValue);
	double getReturnValue() const;
	double getEntryValue() const;
private:
	double entryValue;
	double weight;

	void randomizeWeight();
};