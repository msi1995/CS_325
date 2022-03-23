#include <vector>
using namespace std;

vector<int> insertion_sort(vector<int>& vec)
{
	for (int j = 1; j < vec.size(); j++)
	{
		int key_val = vec[j];
		int i = j - 1;


		while (i >= 0 && vec[i] > key_val)
		{
			vec[i + 1] = vec[i];
			i--;
		}
		vec[i + 1] = key_val;
	}
	return vec;
}