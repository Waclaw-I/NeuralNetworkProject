#include <iostream>

#include <SFML/Graphics.hpp>

#include "RandomGenerator.h"
#include "constants.h"
#include "DataSetManager.h"
#include "SOM.h"



double mapRadius;
double timeConstant;
double neighbourhoodRadius;


int main()
{
	// INITIALIZE
	DataSetManager dataSetManager;
	RandomGenerator(-1, 1);
	SOM som;
	sf::RenderWindow window(sf::VideoMode(mapWidth, mapHeight), "SOM test");


	dataSetManager.createTrainingSet();

	for (int i = 0; i < epochAmount; ++i)
	som.EpochWTM(dataSetManager.getDataSet(), window);
	//som.EpochWTA(dataSetManager.getDataSet(), window);

	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
	}
}

