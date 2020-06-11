#pragma once

#include <cstdlib>
#include <map>
#include <memory>
#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>

namespace util {

template <typename T, typename U>
auto find(T &&container, const U &value)
{
	return std::find(container.begin(), container.end(), value);
}

template <typename T, typename U>
auto find_if(T &&container, const U &value)
{
	return std::find_if(container.begin(), container.end(), value);
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
bool erase_if_contains(T &&container, const U &value)
{
	auto it = find(container, value);

	if (it != container.end()) {
		container.erase(it);
		return true;
	} else
		return false;
}

template <typename T, typename U>
bool erase_if(T &&container, const U &value)
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
auto remove(T &container, const U &value)
{
	return container.erase(std::remove(container.begin(), container.end(), value), container.end());
}

template <typename T, typename U>
auto remove_if(T &container, const U &value)
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

	class const_iterator : public Map::const_iterator
	{
		using map_const_iterator = typename Map::const_iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

		const_iterator(const map_const_iterator &it) :
			Map::const_iterator(it)
		{
		}
		~const_iterator(void)
		{
		}

		reference operator*(void) const
		{
			return *(*this)->second;
		}
	};

	const_iterator begin(void) const
	{
		return m_map.cbegin();
	}

	const_iterator end(void) const
	{
		return m_map.cend();
	}

	const_iterator cbegin(void) const
	{
		return begin();
	}

	const_iterator cend(void) const
	{
		return end();
	}

	class iterator : public Map::iterator
	{
		using map_iterator = typename Map::iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(const map_iterator &it) :
			Map::iterator(it)
		{
		}
		~iterator(void)
		{
		}

		reference operator*(void) const
		{
			return *(*this)->second;
		}
	};

	iterator begin(void)
	{
		return m_map.begin();
	}

	iterator end(void)
	{
		return m_map.end();
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

		auto [it, success] = m_map.emplace(std::piecewise_construct, std::make_tuple(to_insert), std::make_tuple(to_insert));
		if (!success)
			throw std::runtime_error("Can't emplace element in set");
		return *to_insert;
	}

	template <typename TDerived, typename ...Args>
	TDerived& emplace(Args &&...args)
	{
		static_assert(std::is_base_of<T, TDerived>::value, "Emplacing not derived type in unique_set");

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
		m_map.erase(it);
	}

	void clear(void)
	{
		m_map.clear();
	}

private:
	Map m_map;
};

template<typename T>
class unique_vector
{
	using Vector = std::vector<std::unique_ptr<T>>;

public:
	unique_vector(void)
	{
	}
	~unique_vector(void)
	{
	}

	class const_iterator : public Vector::const_iterator
	{
		using vector_const_iterator = typename Vector::const_iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::random_access_iterator_tag;

		const_iterator(const vector_const_iterator &it) :
			Vector::const_iterator(it)
		{
		}
		~const_iterator(void)
		{
		}

		reference operator*(void) const
		{
			return *(Vector::const_iterator::operator *());
		}
	};

	const_iterator begin(void) const
	{
		return m_vec.cbegin();
	}

	const_iterator end(void) const
	{
		return m_vec.cend();
	}

	const_iterator cbegin(void) const
	{
		return begin();
	}

	const_iterator cend(void) const
	{
		return end();
	}

	class iterator : public Vector::iterator
	{
		using vector_iterator = typename Vector::iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(const vector_iterator &it) :
			Vector::iterator(it)
		{
		}
		~iterator(void)
		{
		}

		reference operator*(void) const
		{
			return *(Vector::const_iterator::operator *());
		}
	};

	iterator begin(void)
	{
		return m_vec.begin();
	}

	iterator end(void)
	{
		return m_vec.end();
	}

	size_t size(void) const
	{
		return m_vec.size();
	}

	template <typename ...Args>
	T& emplace(Args &&...args)
	{
		auto to_insert = new T(std::forward<Args>(args)...);

		m_vec.emplace_back(to_insert);
		return *to_insert;
	}

	template <typename TDerived, typename ...Args>
	TDerived& emplace(Args &&...args)
	{
		static_assert(std::is_base_of<T, TDerived>::value, "Emplacing not derived type in unique_vector");

		auto to_insert = new TDerived(std::forward<Args>(args)...);

		m_vec.emplace_back(to_insert);
		return *to_insert;
	}

	void clear(void)
	{
		m_vec.clear();
	}

private:
	Vector m_vec;
};

template <typename T>
class stack : public std::stack<T>
{
	using Inherited = std::stack<T>;

public:
	using container_type = typename Inherited::container_type;
	using value_type = typename Inherited::value_type;
	using size_type = typename Inherited::size_type;
	using reference = typename Inherited::reference;
	using const_reference = typename Inherited::const_reference;

	stack(void)
	{
	}
	~stack(void)
	{
	}

	reference top(void)
	{
		ensure_not_empty();
		return std::stack<T>::top();
	}

	const_reference top(void) const
	{
		ensure_not_empty();
		return std::stack<T>::top();
	}

	template <typename Ret, typename ...Args>
	Ret emplace_frame(const std::function<Ret (void)> &callback, Args &&...args)
	{
		this->emplace(std::forward<Args>(args)...);
		Ret res = callback();
		this->pop();
		return res;
	}

private:
	void ensure_not_empty(void)
	{
		if (this->size() == 0)
			throw std::runtime_error("Runtime assertion failed: No element in stack");
	}
};

template <class DerType, class BaseType, typename ...Args>
std::unique_ptr<BaseType> make_derived(Args &&...args)
{
	auto res = new DerType(std::forward<Args>(args)...);

	return std::unique_ptr<BaseType>(static_cast<BaseType*>(res));
}

template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin(reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

template <typename T>
auto end(reversion_wrapper<T> w) { return std::rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse(T&& iterable) { return { iterable }; }

size_t rounduppwr2(size_t value);

template <typename T>
class vector
{
public:
	vector(void) :
		m_size(0),
		m_allocated(0),
		m_data(nullptr)
	{
	}
	vector(vector &&other) :
		m_size(other.m_size),
		m_allocated(other.m_allocated),
		m_data(other.m_data)
	{
		other.m_size = 0;
		other.m_allocated = 0;
		other.m_data = nullptr;
	}
	~vector(void)
	{
		clear();
	}

	void reserve(size_t elems)
	{
		if (elems <= m_allocated)
			return;
		m_allocated = elems;
		m_data = reinterpret_cast<T*>(realloc(m_data, m_allocated * sizeof(T)));
	}

	void clear(void)
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i].~T();
		free(m_data);
		m_size = 0;
		m_allocated = 0;
		m_data = nullptr;
	}

	template <typename ...Args>
	T& emplace_back(Args &&...args)
	{
		size_t cur = m_size++;

		if (m_size > m_allocated)
			reserve(m_allocated == 0 ? 1 : rounduppwr2(m_allocated));
		return *new (&m_data[cur]) T(std::forward<Args>(args)...);
	}

private:
	size_t m_size;
	size_t m_allocated;
	T *m_data;
};

}