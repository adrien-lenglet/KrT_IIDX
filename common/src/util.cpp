#include "util.hpp"

namespace util {

size_t rounduppwr2(size_t value)
{
	value++;
	//for (size_t i = 0; i < sizeof(value);)
	value--;
	return value;
}

}