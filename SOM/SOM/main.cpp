#include <iostream>

#include <SFML/Graphics.hpp>

#include "RandomGenerator.h"
#include "constants.h"
#include "DataSetManager.h"
#include "SOM.h"



double mapRadius;
double timeConstant;
double neighbourhoodRadius;
bool showed = false;


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

		
		if (!showed)
		{
			double R, G, B;
			std::cout << "Podaj kolor: \nR: ";
			std::cin >> R;
			if (R > 255) R = 255;
			std::cout << "\nG: ";
			std::cin >> G;
			if (G > 255) G = 255;
			std::cout << "\nB: ";
			std::cin >> B;
			if (B > 255) B = 255;
			som.showDesiredNode({ R,G,B });
			showed = true;
		}
		
		for (auto & node : som.getNodesGraphs())
		{
			window.draw(node);
		}
		
		window.display();
		
	}
}

