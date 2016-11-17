#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DataSetManager
{
public:
	void importData(string path);
	void displayData();
	void displayValidationData();

	void displayOneInputRecord(int record);
	void displayOneOutputRecord(int record);

	DataSetManager();
		
	vector<vector<double>> inputDataSet;
	vector<vector<double>> outputDataSet;

	vector<vector<double>> validationInputDataSet;
	vector<vector<double>> validationOutputDataSet;

	double learningRecords;
	double validationRecords;
	double inputsAmount;
	double outputsAmount;


};