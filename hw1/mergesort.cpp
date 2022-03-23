#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "mergeSortAlgo.cpp"

using namespace std;


int main() {

	vector<int> vec1;


	ifstream inputFile("data.txt");

	if (inputFile.is_open()) {
		int intval;
		inputFile >> intval; // use this line to skip the first value

		while (inputFile >> intval) {
			vec1.push_back(intval);
		}
	}
	
	vec1 = mergeSort(vec1);

	for (int i = 0; i < vec1.size(); i++) {
		cout << vec1[i] << endl;
	}



	return 0;
}