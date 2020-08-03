#pragma once

#include <cstdlib>
#include <map>
#include <vector>
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
			return *(Vector::iterator::operator *());
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

template<unsigned N>
struct template_string {
    char buf[N + 1]{};
    constexpr template_string(char const* s) {
        for (unsigned i = 0; i != N; ++i) buf[i] = s[i];
    }
    constexpr operator char const*() const { return buf; }
};
template<unsigned N> template_string(char const (&)[N]) -> template_string<N - 1>;

template <typename ...Args>
static inline constexpr bool are_args_empty_v = std::is_same_v<std::tuple<Args...>, std::tuple<>>;

template <typename W, typename First, typename ...Args>
void vectorize_args_first(std::vector<W> &res, First &&first, Args &&...args)
{
	res.emplace_back(std::forward<First>(first));
	if constexpr (!util::are_args_empty_v<Args...>)
		vectorize_args_first(res, std::forward<Args>(args)...);
}

template <typename W, typename ...Args>
std::vector<W> vectorize_args(Args &&...args)
{
	std::vector<W> res;

	if constexpr (!util::are_args_empty_v<Args...>)
		vectorize_args_first(res, std::forward<Args>(args)...);
	return res;
}

template <template <typename...> class base,typename derived>
struct is_base_of_template
{
    template<typename... Ts>
    static constexpr std::true_type  test(const base<Ts...> *);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template <template <typename...> class base, typename derived>
using is_base_of_template_t = typename is_base_of_template<base,derived>::type;

template <template <typename...> class base,typename derived>
static inline constexpr bool is_base_of_template_v = std::is_same_v<is_base_of_template_t<base, derived>, std::true_type>;

namespace
{
    template <typename, template <typename...> typename>
    struct is_instance_of_template_impl : public std::false_type {};

    template <template <typename...> typename U, typename...Ts>
    struct is_instance_of_template_impl<U<Ts...>, U> : public std::true_type {};
}

template <typename T, template <typename ...> typename U>
using is_instance_of_template = is_instance_of_template_impl<std::decay_t<T>, U>;

template <template <typename ...> typename Cont, typename T>
auto initializer_list_move(std::initializer_list<T> &&list)
{
	Cont<T> res;

	res.resize(list.size());
	for (auto &el : list)
		res.emplace_back(std::move(const_cast<T&>(el)));
	return res;
}

template <typename First, typename ...Args>
auto tupleize_args_first(First &&first, Args &&...args)
{
	std::tuple<std::remove_reference_t<First>> cur(std::move(first));

	if constexpr (util::are_args_empty_v<Args...>)
		return cur;
	else
		return std::tuple_cat(std::move(cur), tupleize_args_first(std::forward<Args>(args)...));
}

template <typename ...Args>
auto tupleize_args(Args &&...args)
{
	if constexpr (util::are_args_empty_v<Args...>)
		return std::make_tuple();
	else
		return tupleize_args_first(std::forward<Args>(args)...);
}

class svec : public std::vector<std::string>
{
public:
	template <typename ...Args>
	svec(Args &&...args) :
		std::vector<std::string>(std::forward<Args>(args)...)
	{
	}

	svec(std::initializer_list<std::string> init_list) :
		std::vector<std::string>(init_list)
	{
	}

	auto c_strs(void) const
	{
		std::vector<const char*> res;

		res.reserve(size());
		for (auto &s : *this)
			res.emplace_back(s.c_str());
		return res;
	}

	auto operator+(svec &&other) &&
	{
		svec res;

		std::move(begin(), end(), std::back_inserter(res));
		std::move(other.begin(), other.end(), std::back_inserter(res));
		return res;
	}
};

template <typename T>
using remove_cvr_t = std::remove_cv_t<std::remove_reference_t<T>>;

struct empty_struct {};
template <bool Pred, class T>
using conditional_un_t = std::conditional_t<Pred, T, empty_struct>;

}

//#define auto_member(id, value) decltype(value) id = value