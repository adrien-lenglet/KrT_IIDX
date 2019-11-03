
#include "krt/krt.hpp"

static std::vector<std::string> getArgs(int argc, char **argv)
{
	std::vector<std::string> res;

	for (int i = 0; i < argc; i++)
		res.push_back(std::string(argv[i]));
	return res;
}

int main(int argc, char **argv)
{
	Krt krt(getArgs(argc, argv));

	krt.run();
	return 0;
}
