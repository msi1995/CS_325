#include <vector>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <array>
#include "mergeSortAlgo.cpp"

using namespace std;


int main() {
	srand(time(NULL));

	int numValues[10] = { 50000, 100000, 250000, 500000, 750000, 1000000, 1500000, 2000000, 3000000, 5000000 };
	int randInt;
	clock_t start, end;

	vector<int> vec1;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < numValues[i]; j++) {
			randInt = rand() % 10001;
			vec1.push_back(randInt);
		}
		start = clock();
		vec1 = mergeSort(vec1);
		end = clock();
		// Calculating total time taken by the program. 
		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "Array size is: " << numValues[i] << " values \t Merge sort processing time: " << time_taken;
		cout << " sec " << endl;
		vec1.clear();
	}

	return 0;

}