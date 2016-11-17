#include "DataSetManager.h"

DataSetManager::DataSetManager() :
	inputDataSet(vector<vector<double>>(558)),
	outputDataSet(vector<vector<double>>(558)),
	validationInputDataSet(vector<vector<double>>(239)),
	validationOutputDataSet(vector<vector<double>>(239)),
	learningRecords(this->inputDataSet.size()),
	validationRecords(this->validationInputDataSet.size()),
	inputsAmount(256),
	outputsAmount(10) // temporarly as an value
	{};

void DataSetManager::displayData() // 256 digits - 16x16 matrix
{
	for (int i = 0; i < learningRecords; ++i)
	{
		cout << "\n\n";
		for (int j = 0; j < outputsAmount; ++j)
		{
			cout << outputDataSet[i][j] << " ";
		}
		cout << "\n\n";
		int liner = 0; 
		for (int j = 0; j < inputsAmount; ++j)
		{
			cout << inputDataSet[i][j];
			liner++;
			if (liner == 16)
			{
				liner = 0;
				cout << endl;
			}
		}

		cin.get();
	}
}

void DataSetManager::displayValidationData() // 256 digits - 16x16 matrix
{
	for (int i = 0; i < learningRecords; ++i)
	{
		cout << "\n\n";
		for (int j = 0; j < outputsAmount; ++j)
		{
			cout << validationOutputDataSet[i][j] << " ";
		}
		cout << "\n\n";
		int liner = 0;
		for (int j = 0; j < inputsAmount; ++j)
		{
			cout << validationInputDataSet[i][j];
			liner++;
			if (liner == 16)
			{
				liner = 0;
				cout << endl;
			}
		}

		cin.get();
	}
}

void DataSetManager::displayOneInputRecord(int record) // learning dataset
{
		int liner = 0;
		for (int i = 0; i < inputsAmount; ++i)
		{
			cout << inputDataSet[record][i];
			liner++;
			if (liner == 16)
			{
				liner = 0;
				cout << endl;
			}
		}
}

void DataSetManager::displayOneOutputRecord(int record) // learning dataset
{
	for (int i = 0; i < outputsAmount; ++i)
	{
		cout << outputDataSet[record][i] << " ";
	}
}

void DataSetManager::importData(string path) // 1594 lines = 797 records. 70%(558) for learning, 30%(239) for validation | 256 digits - 16x16 matrix
{
	fstream data;
	data.open(path.c_str(), ios::in);

	double number;

	for (int i = 0; i < learningRecords; ++i)
	{
		for (int j = 0; j < inputsAmount; ++j)
		{
			data >> number;
			inputDataSet[i].push_back(number);
		}
		for (int j = 0; j < outputsAmount; ++j)
		{
			data >> number;
			outputDataSet[i].push_back(number);
		}
	}

	for (int i = 0; i < validationRecords; ++i)
	{
		for (int j = 0; j < inputsAmount; ++j)
		{
			data >> number;
			validationInputDataSet[i].push_back(number);
		}
		for (int j = 0; j < outputsAmount; ++j)
		{
			data >> number;
			validationOutputDataSet[i].push_back(number);
		}
	}

}