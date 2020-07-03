#include <string>
#include <stdexcept>

namespace util {

template <typename T, typename ...Args>
auto stot(T (*conv)(const std::string &res, size_t*, int), const std::string &str)
{
	size_t pos;
	auto res = conv(str, &pos, 10);

	if (pos != str.size())
		throw std::runtime_error("Can't parse string");
	return res;
}

}