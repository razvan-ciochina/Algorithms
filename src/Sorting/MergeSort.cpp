#include "MergeSort.h"
#include <limits.h>
#include <vector>
#include <iostream>
typedef std::vector<int>::iterator it;

void print_vec(std::vector<int> &vec)
{
	std::cout << "vec: ";
	for (auto& each: vec) {
		std::cout << each << " ";
	}
	std::cout << std::endl;
}

void merge(it p, it q, it r, std::vector<int> &A)
{
	std::vector<int> left(p, q + 1);
	std::vector<int> right(q + 1, r + 1);
	left.push_back(INT_MAX);
	right.push_back(INT_MAX);
	for (it i = p, il = left.begin(), ir = right.begin(); i <= r; i++) {
		if (*il <= *ir) {
			*i = *il++;
		} else {
			*i = *ir++;
		}
	}
}

void sort(it p, it r, std::vector<int> &A)
{
	if (p < r) {
		int middle_offset = (r - p)/2;
		it q = p + middle_offset;
		sort(p, q, A);
		sort(q + 1, r, A);
		merge(p, q, r, A);
	}
}


void MergeSort(std::vector<int>& unsortedVec)
{
	sort(unsortedVec.begin(), unsortedVec.end() - 1, unsortedVec);
}
