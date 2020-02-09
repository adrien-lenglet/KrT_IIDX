#pragma once

#include <algorithm>

namespace util {

template <typename T, typename U>
class T::iterator find(T &container, const U &value)
{
	return std::find(container.begin(), container.end(), value);
}

template <typename T, typename U>
bool contains(T &container, const U &value)
{
	return find(container, value) != container.end();
}

template <typename T, typename U>
bool erase_if_contains(T &container, const U &value)
{
	auto it = find(container, value);

	if (it != container.end()) {
		container.erase(it);
		return true;
	} else
		return false;
}

template <typename T, typename U>
U join(const T &values, const U &delim)
{
	bool is_first = true;
	U res;

	for (const auto &v : values) {
		if (is_first)
			is_first = false;
		else
			res += delim;
		res += v;
	}
	return res;
}

template <typename T, typename U>
class T::iterator remove(T &container, const U &value)
{
	return container.erase(std::remove(container.begin(), container.end(), value), container.end());
}

template <typename T, typename U>
class T::iterator remove_if(T &container, const U &value)
{
	return container.erase(std::remove_if(container.begin(), container.end(), value), container.end());
}

template <template<typename,typename...> typename T, typename U, typename V>
T<V> map(const T<U> &container, const std::function<V(const U&)> &func)
{
	T<V> res;

	for (const U &el : container)
		res.push_back(func(el));
	return res;
}

}