#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <chrono>

using namespace std;


//recursion
int Knapsack(int items, int capacity, vector<int>& weight, vector<int>& value) {

	// If the bag has no capacity or there are no items, return 0. There can be no value.
	if (capacity < 1 || items == 0)
		return 0;

	//check if capacity can support more items
	if (capacity >= weight[items - 1])
		return max(Knapsack(items - 1, capacity, weight, value), // max selects max between these two calls
			Knapsack(items - 1, capacity - weight[items - 1], weight, value) + value[items - 1]); //if item is included, decrement items by 1 since that item is removed
		return Knapsack(items - 1, capacity, weight, value);
}



// dynamic option
int Knapsack_dynamic(int capacity, vector<int>& weight, vector<int>& value) {

	int items_bagged = weight.size();
	int max_value[items_bagged + 1][capacity + 1];



	// if either i or j in the [i][j] array is 0, the value must be zero, since
	// a bag of capacity zero can have no value and an N size of 0 can also have
	// no value.

	for (int cap = 0; cap <= capacity; cap++)
		max_value[0][cap] = 0;
	for (int item = 0; item <= items_bagged; item++)
		max_value[item][0] = 0;

	for (int item = 1; item <= items_bagged; item++) {
		for (int cap = 1; cap <= capacity; cap++) {

			if (cap >= weight[item - 1]) {
				max_value[item][cap] = max(max_value[item - 1][cap], 
					max_value[item - 1][cap - weight[item - 1]] + value[item - 1]); //if item is included, decrement items by 1 since that item is removed
			}
			else
				max_value[item][cap] = max_value[item - 1][cap];
		}
	}
	return max_value[items_bagged][capacity];
}




int main() {
	srand(time(NULL));

	//num values array used to set N
	int numValues[7] = {10, 15, 20, 30, 40, 60, 80 };

	//used to set knapsack capacity
	int knapCapacity[7] = { 50, 75, 100, 125, 150, 200, 250 };
	int randWeight;
	int randVal;
	int capacity;

	vector<int> weight;
	vector<int> value;


	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < numValues[i]; j++) {
			randWeight = (rand() % 100) + 1;
			randVal = (rand() % 200) + 1;
			weight.push_back(randWeight);
			value.push_back(randVal);
		}

		capacity = 100;

		//track in microseconds
		auto start = std::chrono::high_resolution_clock::now();
		int Knapsackval = Knapsack(weight.size(), capacity, weight, value);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;

		long long microseconds_recursive = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

		start = std::chrono::high_resolution_clock::now();
		int DPKnapsackval = Knapsack_dynamic(capacity, weight, value);
		elapsed = std::chrono::high_resolution_clock::now() - start;

		long long int microseconds_DP = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();


		cout << "N = " << numValues[i] << " W = " << capacity << "   Recursive Time: " << microseconds_recursive << "\tDP Time: " << microseconds_DP;
		cout << "\tMax Val Recur: " << Knapsackval << " \tMax Val DP: " << DPKnapsackval << endl;


		weight.clear();
		value.clear();

	}

	cout << endl;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 50; j++) {
			randWeight = (rand() % 100) + 1;
			randVal = (rand() % 200) + 1;
			capacity = knapCapacity[i];
			weight.push_back(randWeight);
			value.push_back(randVal);
		}

		//track in microseconds
		auto start = std::chrono::high_resolution_clock::now();
		int Knapsackval = Knapsack(weight.size(), capacity, weight, value);
		auto elapsed = std::chrono::high_resolution_clock::now() - start;

		long long microseconds_recursive = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

		start = std::chrono::high_resolution_clock::now();
		int DPKnapsackval = Knapsack_dynamic(capacity, weight, value);
		elapsed = std::chrono::high_resolution_clock::now() - start;

		long long int microseconds_DP = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();


		cout << "N = " << 50 << " W = " << capacity << "   Recursive Time: " << microseconds_recursive << "\tDP Time: " << microseconds_DP;
		cout << "\tMax Val Recur: " << Knapsackval << " \tMax Val DP: " << DPKnapsackval << endl;


		weight.clear();
		value.clear();

	}

	return 0;
}