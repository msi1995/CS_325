
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


//3-Way Merge Sort, using Vectors and reading in from text file

//https://www.geeksforgeeks.org/3-way-merge-sort/ used as reference when creating this code. This user uses arrays to do 3 way merge sort.


/* Merge the sorted ranges back together*/
void merge3(vector<int> &gVec, int low, int middle1,
	int middle2, int high, vector<int> &destVec)
{
	int i = low;
	int j = middle1;
	int k = middle2;
	int l = low;

	// choose smaller of the smallest in the three ranges  
	while ((i < middle1) && (j < middle2) && (k < high))
	{
		if (gVec[i] < gVec[j]){
			if (gVec[i] < gVec[k]){
				destVec[l++] = gVec[i++];
			}
			else
				destVec[l++] = gVec[k++];
		}
		else{
			if (gVec[j] < gVec[k]){
				destVec[l++] = gVec[j++];
			}
			else{
				destVec[l++] = gVec[k++];
			}
		}
	}

	// if there are remaining values in 1st or 2nd range
	while ((i < middle1) && (j < middle2))
	{
		if (gVec[i] < gVec[j]){
			destVec[l++] = gVec[i++];
		}
		else{
			destVec[l++] = gVec[j++];
		}
	}

	// if there are remaining values in 2nd or 3rd range
	while ((j < middle2) && (k < high))
	{
		if (gVec[j] < gVec[k]){
			destVec[l++] = gVec[j++];
		}
		else{
			destVec[l++] = gVec[k++];
		}
	}

	// remaining values in 1st/3rd
	while ((i < middle1) && (k < high))
	{
		if (gVec[i] < gVec[k]){
			destVec[l++] = gVec[i++];
		}
		else{
			destVec[l++] = gVec[k++];
		}
	}

	// copy remaining values from the first range  
	while (i < middle1)
		destVec[l++] = gVec[i++];

	// copy remaining values from the second range  
	while (j < middle2)
		destVec[l++] = gVec[j++];

	// copy remaining values from the third range  
	while (k < high)
		destVec[l++] = gVec[k++];
}


/* Performing the merge sort algorithm on the
given array of values in the rangeof indices
[low, high). low is minimum index, high is
maximum index (exclusive) */
void mergeSort3WayRec(vector<int> &gVec, int low,
	int high, vector<int> &destVec)
{
	// If array size is 1 then do nothing  
	if (high - low < 2)
		return;

	// Splitting array into 3 parts  
	int middle1 = low + ((high - low) / 3);
	int middle2 = low + 2 * ((high - low) / 3) + 1;

	// Sorting 3 arrays recursively  
	mergeSort3WayRec(destVec, low, middle1, gVec);
	mergeSort3WayRec(destVec, middle1, middle2, gVec);
	mergeSort3WayRec(destVec, middle2, high, gVec);

	// Merging the sorted arrays  
	merge3(destVec, low, middle1, middle2, high, gVec);
}

void mergeSort3Way(vector<int> &gVec)
{
	// if array size is zero return null  
	if (gVec.size() == 0)
		return;

	// creating duplicate of given array  
	vector<int> fVec;

	// copying alements of given array into  
	// duplicate array  
	for (int i = 0; i < gVec.size(); i++)
		fVec.push_back(gVec[i]);

	// sort function  
	mergeSort3WayRec(fVec, 0, gVec.size(), gVec);

	// copy back elements of duplicate array  
	// to given array  
	for (int i = 0; i < gVec.size(); i++)
		gVec[i] = fVec[i];

}

// Driver Code 
int main(){

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
		mergeSort3Way(vec1);
		end = clock();


		// Calculating total time taken by the program. 
		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "Array size is: " << numValues[i] << " values \t 3-Way Merge Sort Processing Time: " << time_taken;
		cout << " sec " << endl;
		vec1.clear();
	}

	return 0;
}