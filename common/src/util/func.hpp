#pragma once

#include <functional>

namespace util {

template <template<typename,typename> typename T, typename U, typename V>
T<V, std::allocator<V>> map(const T<U, std::allocator<U>> &container, const std::function<V(const U&)> &func)
{
	T<V, std::allocator<V>> res;

	for (const U &el : container)
		res.push_back(func(el));
	return res;
}

}