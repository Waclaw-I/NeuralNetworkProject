#pragma once

class Input
{
public:
	Input();
	Input(bool isFirst);

	double getWeight();
	double getValue();

	void setValue(double value);
	void setWeight(double weight);

	double getResult();

private:
	double value;
	double weight;
};
