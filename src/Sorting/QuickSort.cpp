#include "QuickSort.h"

int Partition(std::vector<int>& v, int p, int r)
{
	int i = p;

	for (int j = p; j < r - 1; ++j)
	{
		if (v[j] <= v[r - 1])
		{
			std::swap(v[i], v[j]);
			++i;
		}
	}

	std::swap(v[i], v[r - 1]);
	return i;
}

void QuickSortImpl(std::vector<int>& v, int p, int r)
{
	if (r - p > 1)
	{
		int q = Partition(v, p, r);
		QuickSortImpl(v, p, q);
		QuickSortImpl(v, q + 1, r);
	}
}

void QuickSort(std::vector<int>& unsortedVec)
{
	QuickSortImpl(unsortedVec, 0, unsortedVec.size());
}
