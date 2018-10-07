#include <Permuter.hpp>
#include <string>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
	if (argc == 1) {
		std::cout << "Please input strings that will be permuted as parameters to permute\n";
	}

	std::vector<std::string> to_permute(argv+1, argv+argc);

	Permuter<std::string> p(to_permute);

	for (auto& result: p.generateResults()) {
		for (auto& str_entry: result) {
			std::cout << str_entry << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
