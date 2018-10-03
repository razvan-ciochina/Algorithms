#pragma once
#include <map>
typedef std::map<char, std::string> ArgMap;

// usage strings have the format i[insertion]:df => -i or --insertion 1 arg, -d no arguments, no long version, -f no arguments, no long version
// - between [] there's the long version of the option
// - the : is used to specify that the option's going to require an argument
bool ParseArgs(int argc, char *argv[], const std::string& usageStr, ArgMap& argMap, const std::string& errorMsg);
