#include <iostream>
#include "Krt/Krt.hpp"

#ifdef DEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif

static std::vector<std::string> getArgs(int argc, char **argv)
{
	std::vector<std::string> res;

	for (int i = 1; i < argc; i++)
		res.push_back(std::string(argv[i]));
	return res;
}

int main(int argc, char **argv)
{
	Krt::Instance(getArgs(argc, argv), IS_DEBUG).run();
	std::cout << "Engine done." << std::endl;
	return 0;
}