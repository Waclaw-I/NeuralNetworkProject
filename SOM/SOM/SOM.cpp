#include "SOM.h"
#include "constants.h"
#include <algorithm>
#include <cstdlib>

#include <iostream>

SOM::SOM()
{
	this->cellWidth = static_cast<double>(mapWidth) / static_cast<double>(cellsAcross);
	this->cellHeight = static_cast<double>(mapHeight) / static_cast<double>(cellsDown);

	this->mapRadius = std::max(mapWidth, mapHeight) / 2;
	this->timeConstant = iterations / std::log(mapRadius);
	this->learningRate = startLearningRate;

	for (int row = 0; row < cellsDown; ++row)
	{
		for (int col = 0; col < cellsAcross; ++col)
		{
			nodes.push_back(Node(col*cellWidth, row*cellWidth, sizeOfInputVector));

			nodesGraphs.push_back(sf::RectangleShape(sf::Vector2f(cellWidth, cellHeight)));
			nodesGraphs.back().setPosition(nodes.back().x, nodes.back().y);
			nodesGraphs.back().setFillColor(sf::Color(nodes.back().weights[0] * 255, // red
													  nodes.back().weights[1] * 255, // green
													  nodes.back().weights[2] * 255, // blue
													  255)); // transparency
		}
	}


}


bool SOM::EpochWTM(const dataSet & data, sf::RenderWindow & window)
{
	if (data[0].size() != sizeOfInputVector) return false;
	window.clear();

	for (int i = 0; i < iterations; ++i)
	{
		int thisVector = rand() % (data.size());

		Node BMU(nodes[findBestMatchingUnit(data[thisVector])]);

		neighbourhoodRadius = mapRadius * exp(-static_cast<double>(i / timeConstant));

		// calculate distance for each node to the BMU
		for (int n = 0; n < nodes.size(); ++n)
		{
			double distToNodeSquared = std::pow(BMU.x - nodes[n].x, 2)
									 + std::pow(BMU.y - nodes[n].y, 2);

			double widthSquared = std::pow(neighbourhoodRadius, 2);

			if (distToNodeSquared < (widthSquared))
			{
				double influence = exp(-(distToNodeSquared) / (2*widthSquared));
				nodes[n].adjustWeights(data[thisVector], learningRate, influence);
			}
		}

		learningRate = startLearningRate * exp(-static_cast<double>(i / iterations));

		updateNodesGraphs();
		for (auto & node : getNodesGraphs())
		{
			window.draw(node);
		}
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	std::cout << "Epoch completed" << std::endl;
	return true;
}

bool SOM::EpochWTA(const dataSet & data, sf::RenderWindow & window)
{
	if (data[0].size() != sizeOfInputVector) return false;
	window.clear();

	for (int i = 0; i < iterations; ++i)
	{
		int thisVector = rand() % (data.size());
		int BMU = findBestMatchingUnit(data[thisVector]);

		for (int i = 0; i < nodes.size(); ++i)
		{
			if (i == BMU) nodes[BMU].adjustWeights(data[thisVector], learningRate, 0.9);
			// no need for influence so it is set to 1
			else
			{
				nodes[i].adjustWeights({ 1,1,1 }, learningRate, 0.01);
			}
		}

		learningRate = startLearningRate * exp(-static_cast<double>(i / iterations));

		updateNodesGraphs();
		for (auto & node : getNodesGraphs())
		{
			window.draw(node);
		}
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	std::cout << "Epoch completed" << std::endl;
	return true;
}




int SOM::findBestMatchingUnit(std::vector<double> vec)
{
	double lowestDistance = INT_MAX;
	int winner;

	for (int i = 0; i < nodes.size(); ++i)
	{
		double dist = nodes[i].getDistance(vec);

		if (dist < lowestDistance)
		{
			lowestDistance = dist;
			winner = i;
		}
	}
	return winner;
}

void SOM::printNodes()
{

	for (int i = 0; i < nodes.size(); ++i)
	{
		std::cout << "R: " << nodes[i].weights[0]
			      << " G: " << nodes[i].weights[1]
			      << " B: " << nodes[i].weights[2] << std::endl;
	}
}

void SOM::updateNodesGraphs()
{
	for (int i = 0; i < nodesGraphs.size(); ++i)
	{
		nodesGraphs[i].setFillColor(sf::Color(nodes[i].weights[0] * 255, // red
			nodes[i].weights[1] * 255, // green
			nodes[i].weights[2] * 255, // blue
			255)); // transparency

	}
}
std::vector<sf::RectangleShape> & SOM::getNodesGraphs()
{
	return this->nodesGraphs;
}