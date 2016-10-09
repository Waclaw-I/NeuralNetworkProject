#include "Entry.h"

#include <iostream>
using namespace std;

#include <random>

Entry::Entry(double minimumWeightValue, double maximumWeightValue)
{
	this->weight = randomizeWeight(minimumWeightValue, maximumWeightValue);
}

double Entry::getWeight() { return this->weight; }
double Entry::getInput() { return this->input; } 
void Entry::setInput(double input) { this->input = input; }
void Entry::setWeight(double weight) { this->weight = weight; }
void Entry::updateWeight(double weight) { this->weight += weight; }
double Entry::getValue() { return (this->input * this->weight); }

double Entry::randomizeWeight(double minimumWeightValue, double maximumWeightValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(minimumWeightValue, maximumWeightValue);

	return dis(gen);
}