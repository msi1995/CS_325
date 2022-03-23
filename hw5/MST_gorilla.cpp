#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;



struct Point {
	int x, y;
	bool Visited = false;
};

void FindMST(vector<Point> coordinates) {

	vector<Point> MSTset;
	float pathWeight = 0, pathWeightMin = 6000000;
	float totalWeight = 0;
	int lastVisited = 0;
	int lastVisited2 = 0;
	bool unvisited = false;
	MSTset.push_back(coordinates[0]);
	coordinates[0].Visited = true;


	while (unvisited == false)
	{
		unvisited = true;
		for (int k = 0; k < MSTset.size(); k++) {
			for (int j = 0; j < coordinates.size(); j++) {
				if (coordinates[j].Visited == false) 
				{
					unvisited = false;
					pathWeight = sqrt(pow(MSTset[k].x - coordinates[j].x, 2) + pow(MSTset[k].y - coordinates[j].y, 2));
					if (pathWeight < pathWeightMin) {
						pathWeightMin = pathWeight;
						lastVisited2 = j;
					}
				}
			}
		}
		

		if (unvisited)
			break;

		coordinates[lastVisited2].Visited = true;
		MSTset.push_back(coordinates[lastVisited2]);
		cout << "(" << coordinates[lastVisited].x << "," << coordinates[lastVisited].y << ") to " << "(" << coordinates[lastVisited2].x << "," << coordinates[lastVisited2].y << ") distance = " << round(pathWeightMin) << endl;
		lastVisited = lastVisited2;
		totalWeight += round(pathWeightMin);
		pathWeightMin = 50000;
	}


	cout << "Total path weight: " << totalWeight << endl << endl;
}


int main() {

	vector<Point> CoordsInGraph;
	Point point1;
	fstream input;
	input.open("graph.txt");
	int inp, testCases, numPoints;
	int testNumber = 0;

	while (input >> inp) {
		testCases = inp;
		for (int i = 0; i < testCases; i++) {
			testNumber++;
			input >> numPoints;
			cout << "Test case " << testNumber << ":" << endl;
			for (int j = 0; j < numPoints; j++) {
				input >> point1.x;
				input >> point1.y;
				CoordsInGraph.push_back(point1);
			}
				cout << endl;
				FindMST(CoordsInGraph);
				CoordsInGraph.clear();
		}
	}
	
}