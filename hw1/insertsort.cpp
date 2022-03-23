#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "insertionSortAlgo.cpp"

using namespace std;

int main() {

	vector<int> vec1;

	vec1.reserve(10);


	ifstream inputFile("data.txt");

	if (inputFile) {
		double intval;
		inputFile >> intval; // use this line to skip the first value
		
		while (inputFile >> intval)
			vec1.push_back(intval);

	}

	vec1 = insertion_sort(vec1);

	for (int i = 0; i < vec1.size(); i++) {
		cout << vec1[i] << endl;
	}


	return 0;
}