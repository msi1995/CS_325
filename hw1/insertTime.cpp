#include <vector>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "insertionSortAlgo.cpp"

using namespace std;

int main() {
	srand(time(NULL));

	int numValues[10] = { 2500, 5000, 7500, 10000, 15000, 20000, 30000, 50000, 75000, 100000 };
	int randInt;
	clock_t start, end;

	vector<int> vec1;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < numValues[i]; j++) {
			randInt = rand() % 10001;
			vec1.push_back(randInt);
		}
		start = clock();
		vec1 = insertion_sort(vec1);
		end = clock();
		// Calculating total time taken by the program. 
		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "Array size is: " << numValues[i] << " values \t insertion sort processing time: " << time_taken;
		cout << " sec " << endl;
		vec1.clear();
	}


	return 0;
}
