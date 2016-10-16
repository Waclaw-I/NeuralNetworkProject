#include <iostream>
#include <fstream>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Neuron.h"
#include "NetworkManager.h"
#include "RandomEngine.h"

using namespace std;

void loadTrainingData(string path, vector<vector<double>> & trainingData);


int main()
{
    RandomEngine randomEngine(-1.0, 1.0);

	vector<int> networkStructure{ 2, 2, 5, 1 };
	vector<double> data{ 1, 1 }; // input
	vector<double> target{ 1 }; // our target, ie: 1&1 = 1
	NetworkManager networkManager(networkStructure);

	networkManager.printNetwork();
	networkManager.insertData(data, target);

	networkManager.feedForward();
	networkManager.updateWeights();
	for(int i = 0; i < networkManager.getNetwork().size(); ++i)
    {
        for (int j = 0; j < networkManager.getNetwork()[i].size(); ++j)
        {
			cout << "Neuron sum:           " << networkManager.getNetwork()[i][j].calculateSum() << endl;
			cout << "Neuron output:        " << networkManager.getNetwork()[i][j].getOutputValue() << endl;
			cout << "Neuron signal error:  " << networkManager.getNetwork()[i][j].getSignalError() << endl;
			cout << "\n";
            for (int k = 0; k < networkManager.getNetwork()[i][j].getInputs().size(); ++k)
            {
                cout << "\tInput nr: "<< k+1 << " weight: " << networkManager.getNetwork()[i][j].getInputs()[k].getWeight() << endl;
            } 
        }
        cout << endl;
    }

	


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
