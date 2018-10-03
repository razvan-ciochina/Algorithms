#include <cassert>
#include <utility>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "ParseArgs.h"


bool ParseArgs(int argc, char *argv[], const std::string& usageStr, ArgMap& argMap, const std::string& errorMsg)
{
	std::unordered_map<std::string, std::pair<char, bool>> optsToChar;
	std::string currentOptShort;
	std::string currentOptLong;

	// parse the usage format string
	for (auto c = usageStr.begin(); c != usageStr.end(); ++c)
	{
		switch (*c)
		{
		case ':':
			optsToChar[currentOptShort].second = true;
			optsToChar[currentOptLong].second = true;
			break;
		case '[':
		{
			if (currentOptShort.empty())
			{
				assert(false);
#ifdef _DEBUG
				// Error message for programmers - this is not visible in the release build
				std::cerr << "Error: Invalid usage string passed in." << std::endl;
				std::cerr << errorMsg.c_str() << std::endl;
#endif
				return false;
			}

			auto endOfLongOpt = std::find(c, usageStr.end(), ']');
			assert(endOfLongOpt != usageStr.end());
			currentOptLong = std::string(c + 1, endOfLongOpt);
			c = endOfLongOpt;
			optsToChar[currentOptLong] = std::make_pair(currentOptShort[0], false);
		}
		break;
		default:
			currentOptShort = *c;
			currentOptLong.clear();
			assert(!currentOptShort.empty());
			optsToChar[currentOptShort] = std::make_pair(currentOptShort[0], false);
		}
	}

	if (argc < 2) {
		std::cerr << "Error: Too few arguments passed in." << std::endl;
		std::cerr << errorMsg.c_str() << std::endl;
		return false;
	}
	// parse tha arguments of the appplication itself
	for (int i = 1; i < argc; ++i)
	{
		bool optionParam = false;
		std::string currentOpt = argv[i];
		if (currentOpt[0] == '-') {
			optionParam = true;
		}
		// remove all leading -
		auto clArgNameStart = std::find_if_not(currentOpt.cbegin(), currentOpt.cend(), [](const char &c) { return c == '-'; });
		currentOpt.erase(currentOpt.cbegin(), clArgNameStart);

		if (optsToChar.find(currentOpt) != optsToChar.end())
		{
			if (optsToChar[currentOpt].second == true)
			{
				if (argv[i + 1][0] == '-')
				{
					assert(false);
					std::cerr << std::string("Error: Invalid argument for option " + currentOpt + "\n").c_str();
					std::cerr << errorMsg.c_str() << std::endl;
					return false;
				}

				argMap[optsToChar[currentOpt].first] = argv[++i];
			}
			else
			{
				argMap.insert(ArgMap::value_type(optsToChar[currentOpt].first, ""));
			}
		}
		else
		{
			if (optionParam == true) {
				std::cerr << "Error: Found unexpected argument " << argv[i] << std::endl;
				std::cerr << errorMsg.c_str() << std::endl;
				return false;
			}
			// whenever something that's not an option is found it's concatenated to argMap["?"]
			argMap['?'] += std::string(argv[i]) + " ";
		}
	}

	return true;
}
