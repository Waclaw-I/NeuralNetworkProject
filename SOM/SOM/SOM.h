#pragma once
#include "Node.h"
#include "constants.h"

#include <SFML/Graphics.hpp>

class SOM
{
public:
	SOM();
	bool EpochWTM(const dataSet & data, sf::RenderWindow & window);
	bool EpochWTA(const dataSet & data, sf::RenderWindow & window);
	int findBestMatchingUnit(std::vector<double>);
	void showDesiredNode(std::vector<double> color);

	void printNodes();

	void updateNodesGraphs();
	std::vector<sf::RectangleShape> & getNodesGraphs();


private:

	double cellWidth;
	double cellHeight;
	int iterationsAmount;
	double mapRadius;
	double neighbourhoodRadius;
	double timeConstant;
	double learningRate;

	Nodes nodes;
	std::vector<sf::RectangleShape> nodesGraphs;
};