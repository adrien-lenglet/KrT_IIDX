#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

static std::string read_file(const std::string &path)
{
	std::stringstream res;
	std::ifstream in(path);

	res << in.rdbuf();
	return res.str();
}

static void output_file(const std::string &outpath, const std::string &data)
{
	auto got = read_file(outpath);
	if (got == data)
		return;

	std::cout << "Update " << outpath << std::endl;
	std::ofstream out(outpath, std::ios::trunc);

	out << data;
}

class CodeFormatter
{
	static bool is_whitespace(char in)
	{
		return in == ' ' || in == '\r' || in == '\n' || in == '\t';
	}

	static bool upcoming_char(const std::string &str, size_t ndx, char ch)
	{
		for (size_t i = ndx; i < str.size(); i++) {
			auto &c = str.at(i);
			if (c == ch)
				return true;
			if (is_whitespace(c))
				continue;
			return false;
		}
		return false;
	}

	static void str_add_tabs(std::string &str, size_t count)
	{
		for (size_t i = 0; i < count; i++)
			str.push_back('\t');
	}

	static void format_decorate(std::string &out, const std::string &in, size_t i, size_t d, bool has_changed)
	{
		auto &c = in.at(i);

		if ((has_changed && !upcoming_char(in, i, ';')) || c == ';') {
			out.push_back('\n');
			str_add_tabs(out, d);
		}
		if (c == '\n')
			str_add_tabs(out, d);
	}

	static std::string format_code_first(const std::string &in)
	{
		std::string out;
		size_t d = 0;

		for (size_t i = 0; i < in.size(); i++) {
			auto &c = in.at(i);

			auto deco = false;
			auto d_p = d;
			if (c == '{')
				d++;
			if (c == '}') {
				d--;
				format_decorate(out, in, i, d, d != d_p);
				deco = true;
			}
			out.push_back(c);
			if (!deco)
				format_decorate(out, in, i, d, d != d_p);
		}
		return out;
	}

	static size_t blank_line(const std::string &in, size_t ndx)
	{
		for (size_t i = ndx; i < in.size(); i++) {
			auto &c = in.at(i);
			if (c == '\n')
				return i;
			if (!is_whitespace(c))
				return ndx;
		}
		return in.size();
	}

	static std::string format_code_second(const std::string &in)
	{
		std::string out;

		for (size_t i = 0; i < in.size(); i++) {
			auto next = blank_line(in, i);
			if (next != i)
				i = next;
			else
				for (; i < in.size(); i++) {
					auto &c = in.at(i);
					out.push_back(c);
					if (c == '\n')
						break;
				}
		}
		return out;
	}

public:
	static std::string format(const std::string &in)
	{
		return format_code_second(format_code_first(in));
	}
};

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

static std::string id_storage(const std::string &id)
{
	return id + std::string("_storage");
}

static size_t process(std::ostream &out, const std::fs::directory_iterator &it)
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
			out << "class " << name << "{";
			process(out, std::fs::directory_iterator(e));
			out << "};";
		} else {
			auto ext = e.path().extension().string();
			auto got = exts.find(ext);

			if (got == exts.end())
				continue;
			auto &type = got->second;
			auto id = e.path().stem().string();
			out << "private: " << type << " " << id_storage(id) << ";";
			out << "public: " << type << "& " << id << "(void);";
		}
		res++;
	}
	return res;
}

static void print_folder(std::ostream &out, const std::string &root)
{
	out << "class " << std::fs::path(root).filename().string() << "_class {";
	process(out, std::fs::directory_iterator(root));
	out << "};";
}

static void print_header(const std::string &root, const std::string &output, const std::vector<std::string> &ns)
{
	std::stringstream out;

	out << "#include \"Subtile/Resource/Model.hpp\"" << std::endl;
	out << "#include \"Subtile/Resource/Texture.hpp\"" << std::endl;
	out << std::endl;

	for (auto &n : ns)
		out << "namespace " << n << " {" << std::endl;
	if (ns.size())
		out << std::endl;

	print_folder(out, root);

	out << std::endl;
	if (ns.size())
		out << std::endl;
	for (auto &n : ns) {
		static_cast<void>(n);
		out << "}" << std::endl;
	}

	output_file(output, CodeFormatter::format(out.str()));
}

static void print_impl(const std::string &path, const std::string &hpath)
{
	std::stringstream out;

	auto hp = std::fs::path(hpath).filename().string();

	out << "#include \"" << hp << "\"" << std::endl;
	out << "#define DIR_IMPL" << std::endl;
	out << "#include \"" << hp << "\"" << std::endl;

	output_file(path, CodeFormatter::format(out.str()));
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