#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;



//using the same knapsack function as in knapsack.cpp for the most part, except with some slight
//changes. This one returns a vector rather than an int, and has to have functionality for
//saving the items that were placed in the bag.

vector<int> Knapsack_dynamic(int capacity, vector<int>& weight, vector<int>& value) {

	int items = weight.size();
	int max_value[items + 1][capacity + 1];
	int max_val;
	vector<int> transfer;
	vector<int> its;


	// if either i or j in the [i][j] array is 0, the value must be zero, since
	// a bag of capacity zero can have no value and an N size of 0 can also have
	// no value.

	for (int cap = 0; cap <= capacity; cap++)
		max_value[0][cap] = 0;
	for (int item = 0; item <= items; item++)
		max_value[item][0] = 0;



	for (int item = 1; item <= items; item++) {
		for (int cap = 1; cap <= capacity; cap++) {

			if (cap >= weight[item - 1]) {
				max_value[item][cap] = max(max_value[item - 1][cap],
					max_value[item - 1][cap - weight[item - 1]] + value[item - 1]); //if item is included, decrement items by 1 since that item is removed
			}
			else
				max_value[item][cap] = max_value[item - 1][cap];
		}
	}

	max_val = max_value[items][capacity];
	transfer.push_back(max_val);

	for (int i = items; (i > 0) && (max_val > 0); i--)
		if (max_val != max_value[i - 1][capacity]) {
			its.insert(its.begin(), i);
			max_val -= value[i - 1];
			capacity -= weight[i - 1];
		}

	for (int i = 0; i < its.size(); i++)
		transfer.push_back(its[i]);

	return transfer;
}


int main() {

	int num_cases, numFamilyMembers, value, weight, item_amount, weight_limit, totalvalue, j, i;
	vector<int> weightVec;
	vector<int> valueVec;
	vector<int> weight_limitVec;
	vector<int> holdingVec;
	ifstream inputFile;
	ofstream outputFile;

	inputFile.open("shopping.txt");
	outputFile.open("results.txt");


	inputFile >> num_cases;
	i = 0;
	while(i < num_cases){

		inputFile >> item_amount;
		outputFile << "Test Case #:" << i + 1 << endl;

		j = 0;
		while (j < item_amount){
			inputFile >> value;
			inputFile >> weight;
			valueVec.push_back(value);
			weightVec.push_back(weight);
			j++;
		}

		//num family members
		inputFile >> numFamilyMembers;

		j = 0;
		while (j < numFamilyMembers) {
			inputFile >> weight_limit;
			weight_limitVec.push_back(weight_limit);
			j++;
		}

		j = 0;
		while (j < numFamilyMembers) {
			holdingVec = Knapsack_dynamic(weight_limitVec[j], weightVec, valueVec);
			totalvalue += holdingVec[0];
			j++;
		}
		
		outputFile << "Total Value: $" << totalvalue << endl;
		totalvalue = 0;

		//item choices
		j = 0;
		while (j < numFamilyMembers) {
			holdingVec = (Knapsack_dynamic(weight_limitVec[j], weightVec, valueVec));
			outputFile << "Family Member " << j + 1 << " Items: ";
			for (int z = 1; z < holdingVec.size(); z++) {
				if (z < holdingVec.size() - 1)
					outputFile << holdingVec[z] << ", ";
				else
					outputFile << holdingVec[z];
			}
			outputFile << endl;
			j++;
		}
		outputFile << endl;


		//wipe all vectors for next run
		valueVec.clear();
		weightVec.clear();
		weight_limitVec.clear();
		i++;
	}

	outputFile.close();
	inputFile.close();

	return 0;
}