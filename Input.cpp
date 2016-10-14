#include "Input.h"

#include <iostream>
using namespace std;

#include <random>

Input::Input(double minimumWeightValue, double maximumWeightValue)
{
	this->weight = randomizeWeight(minimumWeightValue, maximumWeightValue);
}

double Input::getWeight() { return this->weight; }
double Input::getValue() { return this->value; }
void Input::setValue(double input) { this->value = input; }
void Input::setWeight(double weight) { this->weight = weight; }
double Input::getResult() { return (this->value * this->weight); }

double Input::randomizeWeight(double minimumWeightValue, double maximumWeightValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(minimumWeightValue, maximumWeightValue);

	return dis(gen);
}