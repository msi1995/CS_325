#include <vector>
using namespace std;

vector<int> merge(vector<int> left, vector<int> right) {
	int int_left = 0, int_right = 0;
	vector<int> result;
	while (int_left < left.size() && int_right < right.size())
		if (left[int_left] < right[int_right]) {
			result.push_back(left[int_left++]);
		}
		else {
			result.push_back(right[int_right++]);
		}


	while (int_left < left.size()) result.push_back(left[int_left++]);
	while (int_right < right.size()) result.push_back(right[int_right++]);


	return result;
}

vector<int> mergeSort(vector<int>& arr) {
	int length = arr.size() / 2;

	if (arr.size() < 2)
		return arr;

	vector<int> left(arr.begin(), arr.begin() + length);
	vector<int> right(arr.begin() + length, arr.end());


	return merge(mergeSort(left), mergeSort(right));
}