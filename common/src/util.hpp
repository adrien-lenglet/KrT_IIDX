#pragma once

#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iostream>

namespace util {

template <typename T, typename U>
class T::iterator find(T &container, const U &value)
{
	return std::find(container.begin(), container.end(), value);
}

template <typename T, typename U>
class T::iterator find_if(T &container, const U &value)
{
	return std::find_if(container.begin(), container.end(), value);
}

template <typename T, typename U>
class T::const_iterator find(const T &container, const U &value)
{
	return std::find(container.cbegin(), container.cend(), value);
}

template <typename T, typename U>
class T::const_iterator find_if(const T &container, const U &value)
{
	return std::find_if(container.cbegin(), container.cend(), value);
}

template <typename T, typename U>
bool contains(const T &container, const U &value)
{
	return find(container, value) != container.cend();
}

template <template<typename,typename...> typename T, typename U, typename V>
bool contains(const T<U> &container, const T<V> &included)
{
	for (const auto &i : included)
		if (!contains(container, i))
			return false;
	return true;
}

template <template<typename,typename...> typename T, typename U, typename V>
T<U> not_contained(const T<U> &container, const T<V> &included)
{
	T<U> res;

	for (const auto &i : included)
		if (!contains(container, i))
			res.push_back(i);
	return res;
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
bool erase_if(T &container, const U &value)
{
	auto it = find_if(container, value);

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

template <typename T>
class ref_wrapper : public std::reference_wrapper<T>
{
public:
	ref_wrapper(void)
	{
	}

	ref_wrapper(T &ref) :
		std::reference_wrapper<T>(ref)
	{
	}

	bool operator<(const std::reference_wrapper<T> &other) const
	{
		return &this->get() < &other.get();
	}
};

template <typename T>
class dep
{
public:
	dep(T value) :
		m_value(value)
	{
	}
	~dep(void)
	{
	}

	operator T(void) const
	{
		return m_value;
	}

private:
	T m_value;
};

template <typename CallbackType>
void fatal_throw(const CallbackType &callback)
{
	try {
		callback();
	} catch (const std::exception &e) {
		std::terminate();
	}
}

template<typename T>
class unique_set
{
	using Map = std::map<const T*, std::unique_ptr<T>>;

public:
	unique_set(void)
	{
	}
	~unique_set(void)
	{
	}

	class const_iterator
	{
		using map_const_iterator = typename Map::const_iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

		const_iterator(const map_const_iterator &it) :
			m_map_it(it)
		{
		}
		~const_iterator(void)
		{
		}

		const_iterator& operator++(void)
		{
			++m_map_it;
			return *this;
		}

		const_iterator& operator--(void)
		{
			--m_map_it;
			return *this;
		}

		reference operator*(void) const
		{
			return *m_map_it->second;
		}

		bool operator==(const const_iterator &other) const
		{
			return m_map_it == other.m_map_it;
		}

		bool operator!=(const const_iterator &other) const
		{
			return m_map_it != other.m_map_it;
		}

	private:
		map_const_iterator m_map_it;
	};

	const_iterator begin(void) const
	{
		return const_iterator(m_map.cbegin());
	}

	const_iterator end(void) const
	{
		return const_iterator(m_map.cend());
	}

	const_iterator cbegin(void) const
	{
		return begin();
	}

	const_iterator cend(void) const
	{
		return end();
	}

	class iterator
	{
		using map_iterator = typename Map::iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(const map_iterator &it) :
			m_map_it(it)
		{
		}
		~iterator(void)
		{
		}

		iterator& operator++(void)
		{
			++m_map_it;
			return *this;
		}

		iterator& operator--(void)
		{
			--m_map_it;
			return *this;
		}

		reference operator*(void) const
		{
			return *m_map_it->second;
		}

		bool operator==(const iterator &other) const
		{
			return m_map_it == other.m_map_it;
		}

		bool operator!=(const iterator &other) const
		{
			return m_map_it != other.m_map_it;
		}

	private:
		friend unique_set;

		map_iterator m_map_it;
	};

	iterator begin(void)
	{
		return iterator(m_map.begin());
	}

	iterator end(void)
	{
		return iterator(m_map.end());
	}

	size_t size(void) const
	{
		return m_map.size();
	}

	T& insert(std::unique_ptr<T> &&to_insert)
	{
		auto ptr = to_insert.release();

		auto [it, success] = m_map.emplace(ptr, ptr);
		if (!success)
			throw std::runtime_error("Can't insert element in set");
		return *ptr;
	}

	template <typename ...Args>
	T& emplace(Args &&...args)
	{
		auto to_insert = new T(std::forward<Args>(args)...);

		auto [it, success] = m_map.emplace(to_insert, to_insert);
		if (!success)
			throw std::runtime_error("Can't emplace element in set");
		return *to_insert;
	}

	template <typename TDerived, typename ...Args>
	TDerived& emplace(Args &&...args)
	{
		auto to_insert = new TDerived(std::forward<Args>(args)...);

		auto [it, success] = m_map.emplace(to_insert, to_insert);
		if (!success)
			throw std::runtime_error("Can't emplace element in set");
		return *to_insert;
	}

	const_iterator find(const T &elem) const
	{
		return const_iterator(m_map.find(&elem));
	}

	iterator find(const T &elem)
	{
		return iterator(m_map.find(&elem));
	}

	void erase(const iterator &it)
	{
		m_map.erase(it.m_map_it);
	}

private:
	Map m_map;
};

}