#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

static auto getArgs(int argc, char **argv)
{
	std::vector<std::string> res;

	for (int i = 1; i < argc; i++)
		res.emplace_back(argv[i]);
	return res;
}

static auto getNs(const std::vector<std::string> &args)
{
	std::vector<std::string> res;

	for (size_t i = 2; i < args.size(); i++)
		res.emplace_back(args.at(i));
	return res;
}

namespace std {
namespace fs = filesystem;
}

static void print_tabs(std::ostream &out, size_t count)
{
	for (size_t i = 0; i < count; i++)
		out << "\t";
}

static size_t process(std::ostream &out, const std::fs::directory_iterator &it, size_t depth = 0)
{
	static const std::map<std::string, std::string> exts = {
		{".obj", "sb::rs::Model"},
		{".png", "sb::rs::Texture"},
	};
	size_t res = 0;

	for (auto &e : it) {
		auto name = e.path().filename().string();
		if (name.at(0) == '.')
			continue;

		if (e.is_directory()) {
			std::cout << "," << std::endl;
			print_tabs(out, depth);
			out << "dir(" << name;
			if (process(out, std::fs::directory_iterator(e), depth + 1)) {
				out << std::endl;
				print_tabs(out, depth);
			}
			out << ")";
		} else {
			auto ext = e.path().extension().string();
			auto got = exts.find(ext);

			if (got == exts.end())
				continue;
			std::cout << "," << std::endl;
			print_tabs(out, depth);
			out << "(" << got->second << ", " << e.path().stem().string() << ")";
		}
		res++;
	}
	return res;
}

int main(int argc, char **argv)
{
	auto args = getArgs(argc, argv);
	auto &input = args.at(0);
	auto &output = args.at(1);
	auto ns = getNs(args);

	std::cout << "dir_export(" << std::fs::path(input).filename().string();
	process(std::cout, std::fs::directory_iterator(input), 1);
	std::cout << std::endl << ")";
	return 0;
}