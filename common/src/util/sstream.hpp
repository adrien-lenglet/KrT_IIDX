#pragma once

#include <sstream>

namespace util {

template <typename T>
std::string sstream_str(T &&t)
{
	std::stringstream ss;

	ss << t;
	return ss.str();
}

}