#include "InsertionSort.h"

void InsertionSort(std::vector<int>& unsorted_vec)
{
	int vec_len = unsorted_vec.size();

	for (int i = 1; i < vec_len; ++i)
	{
		int key = unsorted_vec[i];
		int j = i - 1;

		while (j >= 0 && unsorted_vec[j] > key)
		{
			unsorted_vec[j + 1] = unsorted_vec[j];
			j--;
		}

		unsorted_vec[j + 1] = key;
	}
}
