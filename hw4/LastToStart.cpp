#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */

//Sources used:
// - https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/

using namespace std;


struct Activity {

	int activityNumber, start, finish;
};


//Merge sort algorithm from my HW1
vector<Activity> merge(vector<Activity> left, vector<Activity> right) {
	int int_left = 0, int_right = 0;
	int max;
	vector<Activity> result;
	while (int_left < left.size() && int_right < right.size())
		if (left[int_left].start > right[int_right].start) {
			result.push_back(left[int_left++]);
		}
		else {
			result.push_back(right[int_right++]);
		}


	while (int_left < left.size())
		result.push_back(left[int_left++]);
	while (int_right < right.size())
		result.push_back(right[int_right++]);

	return result;
}

//Merge sort from HW1
vector<Activity> mergeSort(vector<Activity> arr) {
	int length = arr.size() / 2;

	if (arr.size() < 2)
		return arr;

	vector<Activity> left(arr.begin(), arr.begin() + length);
	vector<Activity> right(arr.begin() + length, arr.end());


	return merge(mergeSort(left), mergeSort(right));

}


int main() {

	//vector initialization
	vector<Activity> activities;
	vector<Activity> optimal;


	ifstream inputFile("act.txt");

	if (inputFile) {
		int numActivities;
		int activityData;
		int activitySet = 1;
		
		while(inputFile >> numActivities){ 
			//read each character into the proper member variable of the struct in vector.
			for (int i = 0; i < numActivities; i++) {
				activities.push_back(Activity());
				inputFile >> activityData;
				activities[i].activityNumber = activityData;
				inputFile >> activityData;
				activities[i].start = activityData;
				inputFile >> activityData;
				activities[i].finish = activityData;
			}
			activities = mergeSort(activities);

			//use this if you want to print each activity's info individually
		/*	for (int i = 0; i < numActivities; i++) {
				cout << activities[i].activityNumber << " " << activities[i].start << " " << activities[i].finish << endl;
			}*/

			//always push back the first activity since this is a greedy algorithm
			optimal.push_back(activities[0]);
			int count = 0;

			//if the next activity in the vector has a finish time that is BEFORE the most recent
			//activity in the optimal vector's start time, it can be added, so push_back that activity.
			for (int i = 1; i < activities.size(); i++) {
				if (activities[i].finish <= optimal[count].start) {
					optimal.push_back(activities[i]);
					count++;
				}
			}

			//print
			cout << "Optimal Activities Selected for set #" << activitySet << ": ";
			for (int i = 0; i < optimal.size(); i++) {
				cout << optimal[i].activityNumber << " ";
			}
			cout << endl << optimal.size() << " activities selected in total.";
			cout << endl << endl << endl;

			//clear vecs and increment activitySet int for printing set #.
			activitySet++;
			activities.clear();
			optimal.clear();
		}
	}

}