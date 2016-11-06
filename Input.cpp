#include "Input.h"

#include "RandomGenerator.h"

Input::Input(double entryValue): entryValue(entryValue)
{
	this->randomizeWeight();
}
Input::Input(bool isInInputLayer)
{
	if (isInInputLayer) this->weight = 1;
	else this->randomizeWeight();
}
Input::Input() { this->randomizeWeight(); }

double Input::getWeight() const { return this->weight; }
void Input::setWeight(double weight)  { this->weight = weight; }
void Input::updateWeight(double delta) { this->weight += delta; }
void Input::setEntryValue(double entryValue) { this->entryValue = entryValue; }
double Input::getEntryValue() const { return this->entryValue; }
double Input::getReturnValue() const { return (this->weight * this->entryValue); }


void Input::randomizeWeight()
{
	this->weight = RandomGenerator::getRandomNumber();
}