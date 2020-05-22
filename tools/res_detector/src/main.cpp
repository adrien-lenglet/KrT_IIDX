#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
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
			out << "," << std::endl;
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
			out << "," << std::endl;
			print_tabs(out, depth);
			out << "(" << got->second << ", " << e.path().stem().string() << ")";
		}
		res++;
	}
	return res;
}

static void print_folder(std::ostream &out, const std::string &root)
{
	out << "dir_export(" << std::fs::path(root).filename().string();
	process(out, std::fs::directory_iterator(root), 1);
	out << std::endl << ")" << std::endl;;
}

static void print_header(const std::string &root, const std::string &output, const std::vector<std::string> &ns)
{
	std::ofstream out(output, std::ios::trunc);

	out << "#include \"Subtile/Resource/Model.hpp\"" << std::endl;
	out << "#include \"Subtile/Resource/Texture.hpp\"" << std::endl;
	out << std::endl;
	out << "#include \"Subtile/Resource/Decl.hpp\"" << std::endl << std::endl;

	for (auto &n : ns)
		out << "namespace " << n << " {" << std::endl;
	if (ns.size())
		out << std::endl;

	print_folder(out, root);

	if (ns.size())
		out << std::endl;
	for (auto &n : ns) {
		static_cast<void>(n);
		out << "}" << std::endl;
	}

	out << std::endl;
	out << "#include \"Subtile/Resource/DeclEnd.hpp\"" << std::endl;
}

static void print_impl(const std::string &path, const std::string &hpath)
{
	std::ofstream out(path, std::ios::trunc);

	auto hp = std::fs::path(hpath).filename().string();

	out << "#include \"" << hp << "\"" << std::endl;
	out << "#define DIR_IMPL" << std::endl;
	out << "#include \"" << hp << "\"" << std::endl;
}

static auto getOutpath(const std::string &root, const std::string &output, const std::string &ext)
{
	std::stringstream ss;

	ss << output << "/" << std::fs::path(root).filename().string() << ext;
	return ss.str();
}

int main(int argc, char **argv)
{
	auto args = getArgs(argc, argv);
	auto &input = args.at(0);
	auto &output = args.at(1);
	auto ns = getNs(args);

	print_header(input, getOutpath(input, output, ".hpp"), ns);
	print_impl(getOutpath(input, output, ".cpp"), getOutpath(input, output, ".hpp"));

	return 0;
}