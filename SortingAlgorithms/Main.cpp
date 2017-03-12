#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#include "ParseArgs.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "Windows.h"

class GlobalConfig
{
public:
	GlobalConfig() : insertionSort(false), mergeSort(false), quickSort(false) {}

	bool insertionSort;
	bool mergeSort;
	bool quickSort;
} globalConfig;

void StringToVec(const std::string& input, std::vector<int>& outVec)
{
	auto& toConvertStart = input.begin();
	auto& toConvertEnd = std::find(input.begin(), input.end(), ' ');

	// didn't really care about the speed with which this thing is run
	while (toConvertEnd != input.end())
	{
		int converted = INT_MIN;

		if (sscanf_s(input.substr(toConvertStart - input.begin(), toConvertEnd - toConvertStart).c_str(), "%d", &converted) > 0)
			outVec.push_back(converted);

		toConvertStart = toConvertEnd + 1;
		toConvertEnd = std::find(toConvertStart, input.end(), ' ');
	}
}

void PrintVec(const std::vector<int>& vec)
{
	size_t vecSize = vec.size();
	std::cout << "[ ";
	for (size_t i = 0; i < vecSize; ++i)
		std::cout << vec[i] << " ";
	std::cout << "]";
}

class SpeedTest
{
public:
	SpeedTest()
	{
		std::cout << "Starting performance analysis." << std::endl;
		QueryPerformanceCounter(&startTime);
	}

	~SpeedTest()
	{
		LARGE_INTEGER endTime;
		LARGE_INTEGER freq;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&endTime);

		std::cout << "Elapsed time (microseconds): " << ((endTime.QuadPart - startTime.QuadPart) * 1000000) / freq.QuadPart << std::endl;
	}

private:
	LARGE_INTEGER startTime;
};

int main(int argc, char *argv[])
{
	ArgMap mappedArgs;
	std::string usageStr = "USAGE: ";
	std::vector<int> intVec;
	std::string appName = argv[0];
	appName.erase(appName.cbegin(), appName.cbegin() + appName.find_last_of('\\') + 1);
	appName.erase(appName.cbegin() + appName.find_first_of('.'), appName.cend());
	usageStr += appName;
	usageStr += " [OPTIONS] INPUT_VEC\n\n";
	usageStr += "OPTIONS:\n\n";
	usageStr += "\t-i --insertion-sort\t\tSort input vector through insertion sort\n";
	usageStr += "\t-m --merge-sort\t\tSort input vector through merge sort\n";
	usageStr += "\t-q --quick-sort\t\tSort input vector through quick sort\n";
	usageStr += "\t-h --help\t\tThis screen\n\n";
	usageStr += "INPUT_VEC: Space separated list of integers to sort.\n";

	ParseArgs(argc, argv, "h[help]i[insertion-sort]m[merge-sort]q[quick-sort]", mappedArgs, usageStr);

	for (auto &opt : mappedArgs)
	{
		switch (opt.first)
		{
		case 'i':
			globalConfig.insertionSort = true;
			break;
		case 'm':
			globalConfig.mergeSort = true;
			break;
		case 'q':
			globalConfig.quickSort = true;
			break;
		case 'h':
			std::cout << usageStr.c_str() << std::endl;
			system("PAUSE");
			return 0;
		default: // mappedArgs[?]
			StringToVec(opt.second, intVec);
		}
	}

	std::cout << "Input vec: ";
	PrintVec(intVec);
	std::cout << std::endl;
	
	if (globalConfig.insertionSort)
	{
		std::vector<int> dirtyCopy = intVec;
		SpeedTest perfTest;
		std::cout << "Sorted through insertion: ";
		InsertionSort(dirtyCopy);
		PrintVec(dirtyCopy);
		std::cout << std::endl;
	}


	if (globalConfig.quickSort)
	{
		std::vector<int> dirtyCopy = intVec;
		SpeedTest perfTest;
		std::cout << "Sorted through quickSort: ";
		QuickSort(dirtyCopy);
		PrintVec(dirtyCopy);
		std::cout << std::endl;
	}

	system("Pause");
	return 0;
}