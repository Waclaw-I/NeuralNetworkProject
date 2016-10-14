#include <iostream>
#include <fstream>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Neuron.h"
#include "NetworkManager.h"

using namespace std;

void loadTrainingData(string path, vector<vector<double>> & trainingData);


int main()
{
	vector<int> networkStructure{ 12,5,5,5, 12, 3 };
	vector<double> data{ 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5 };
	NetworkManager networkManager(networkStructure);

	networkManager.printNetwork();
	networkManager.insertData(data);
	
	cin.get();
	/*srand(time(NULL));
	vector<vector<double>> trainingData;
	loadTrainingData("ORdata.txt", trainingData);


	Neuron neuron(2);

	for (int i = 0; i < trainingData.size(); i++)
	{
		for (int j = 0; j < neuron.getEntries().size(); j++)
		{
			neuron.getEntries()[j].setInput(trainingData[i][j]);
		}
		neuron.setTargetValue(trainingData[i][2]);
		neuron.activationFunction();

		cout << "\n######## Epoch number: " << i + 1 << " ########\n" << endl;
		cout << "Input: " << neuron.getEntries()[0].getInput() << " " << neuron.getEntries()[1].getInput() << endl;
		cout << "Output: " << neuron.getOutputValue() << endl;
		cout << "Target: " << neuron.getTargetValue() << endl;
		cout << "Error: " << (trainingData[i][2] - neuron.getOutputValue()) << endl;
		cout << "Wages: " << neuron.getEntries()[0].getWeight() << "  " << neuron.getEntries()[1].getWeight() << endl;
		neuron.updateWeights();*/

	//}

	/*Neuron neuron(1);
	double delta = 1;
	int i = 0;
	while ( delta > 0.01)
	{
		i++;
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int t = !n1;

		neuron.getEntries()[0].setInput(n1);
		neuron.setTargetValue(t);
		neuron.activationFunction();

		delta = abs(neuron.getOutputValue() - neuron.getTargetValue());

		cout << "\n######## Epoch number: " << i + 1 << " ########\n" << endl;
		cout << "Input: " << neuron.getEntries()[0].getInput() << endl;
		cout << "Output: " << neuron.getOutputValue() << endl;
		cout << "Target: " << neuron.getTargetValue() << endl;
		cout << "Error: " << delta << endl;
		neuron.updateWeights();
	}*/
	



	//cin.get();

}

void loadTrainingData(string path, vector<vector<double>> & trainingData)
{
	fstream data;
	data.open(path, ios::in);

	if (data.good())
	{
		vector<double> row;
		double temp;

		while (!data.eof())
		{
			
			data >> temp;
			if (temp != 32)
			{
				row.push_back(temp);
			}

			if (row.size() == 3)
			{
				trainingData.push_back(row);
				row.clear();
			}
		}
	}
	else
	{
		cout << "Nie mozna otworzyc pliku!" << endl;
	}
}