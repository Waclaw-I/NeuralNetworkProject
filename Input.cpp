#include "Input.h"
#include "RandomEngine.h"

#include <iostream>
using namespace std;

#include <random>

Input::Input()
{
	this->weight = RandomEngine::getRandomNumber();
}

Input::Input(bool isFirst)
{
	this->weight = 1;
}

double Input::getWeight() { return this->weight; }
double Input::getValue() { return this->value; }
void Input::setValue(double input) { this->value = input; }
void Input::setWeight(double weight) { this->weight = weight; }
double Input::getResult() { return (this->value * this->weight); }

