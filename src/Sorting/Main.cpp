#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "ParseArgs.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#ifdef _WIN32
	#include "Windows.h"
#else 
// LINUX
	#include <unistd.h>
	#include <limits.h>
	#include <sys/times.h>
	#include <cstring>
	#include <chrono>
#endif

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
	auto toConvertStart = input.begin();
	auto toConvertEnd = std::find(input.begin(), input.end(), ' ');

	// didn't really care about the speed with which this thing is run
	while (toConvertEnd != input.end())
	{
		int converted = INT_MIN;

		try {
			converted=stoi(input.substr(toConvertStart - input.begin(), toConvertEnd - toConvertStart));
			outVec.push_back(converted);
		} catch (std::invalid_argument e) {
			// no special exception handling
			std::cout << "Invalid argument passed to string to int conversion function " << e.what() << std::endl;
		} catch (std::out_of_range e) {
			std::cout << "Out of range argument passed to string to int conversion function " << e.what() << std::endl;
		}	

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

void PrintErrnoStr() 
{
	std::cerr << "Error: " << strerror(errno) << std::endl;
	errno = 0;
}

class SpeedTest
{
public:
	SpeedTest()
	{
		std::cout << "Starting performance analysis." << std::endl;
#ifdef _WIN32
		QueryPerformanceCounter(&startTime);
#else
		startTime = std::chrono::high_resolution_clock::now();
#endif
	}

	~SpeedTest()
	{
#ifdef _WIN32
		LARGE_INTEGER endTime;
		LARGE_INTEGER freq;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&endTime);

		std::cout << "Elapsed time (microseconds): " << ((endTime.QuadPart - startTime.QuadPart) * 1000000) / freq.QuadPart << std::endl;
#else
		std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed =  (endTime - startTime);
		std::cout << "Elapsed time (microseconds): " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << std::endl;
#endif
	}

private:
#ifdef _WIN32
	LARGE_INTEGER startTime;
#else
	std::chrono::high_resolution_clock::time_point startTime;
#endif
};

int main(int argc, char *argv[])
{
	ArgMap mappedArgs;
	std::string usageStr = "USAGE: ";
	std::vector<int> intVec;
	std::string appName = argv[0];
	size_t last_slash = appName.find_last_of('\\');
	if (last_slash != std::string::npos) {
		appName.erase(appName.cbegin(), appName.cbegin() + last_slash + 1);
	}

	if (appName.find(".") != std::string::npos) {	
		appName.erase(appName.cbegin() + appName.find_first_of('.'), appName.cend());
	}
	usageStr += appName;
	usageStr += " [OPTIONS] INPUT_VEC\n\n";
	usageStr += "OPTIONS:\n\n";
	usageStr += "\t-i --insertion-sort\tSort input vector by insertion sort\n";
	usageStr += "\t-m --merge-sort\t\tSort input vector by merge sort\n";
	usageStr += "\t-q --quick-sort\t\tSort input vector by quick sort\n";
	usageStr += "\t-h --help\t\tThis screen\n\n";
	usageStr += "INPUT_VEC: Space separated list of integers to sort.\n";

	if (false == ParseArgs(argc, argv, "h[help]i[insertion-sort]m[merge-sort]q[quick-sort]", mappedArgs, usageStr)) {
		return -1;
	}

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
#ifdef _WIN32
			system("PAUSE");
#endif
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

	if (globalConfig.mergeSort)
	{
		std::vector<int> dirtyCopy = intVec;
		SpeedTest perfTest;
		std::cout << "Sorted through mergeSort: ";
		MergeSort(dirtyCopy);		
		PrintVec(dirtyCopy);
		std::cout << std::endl;
	}

#ifdef _WIN32
	system("Pause");
#endif
	return 0;
}
