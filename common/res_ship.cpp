#include <string>
#include <vector>

#include "Krt/res.resdecl.hpp"

int main(int argc, char **argv)
{
	std::vector<std::string> args;

	for (int i = 1; i < argc; i++)
		args.emplace_back(argv[i]);

	sb::rs::Folder::Shipper(Krt::res).ship(args.at(0));
	return 0;
}