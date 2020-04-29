#pragma once

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <optional>
#include <type_traits>
#include "Listener.hpp"
#include "util.hpp"

namespace Subtile {
namespace Event {

template <typename Key, typename Value>
class Bindings
{
	using Map = std::map<Key, util::unique_set<Value>>;

public:
	using const_iterator = typename Map::const_iterator;
	using iterator = typename Map::iterator;
	using callback = std::function<void (bool isAdd, const Key &key, const Value &value)>;

	Bindings(const callback &callback = nullptr) :
		m_callback(callback)
	{
	}
	~Bindings(void)
	{
		util::fatal_throw([this](){
			if (m_bindings.size() > 0)
				throw std::runtime_error("Bindings are still connected");
		});
	}

	class Binder : public Event::Listener
	{
	public:
		Binder(Bindings &bindings, typename Map::value_type &pair, Value &value) :
			m_bindings(&bindings),
			m_pair(&pair),
			m_value(&value)
		{
		}
		~Binder(void) override
		{
			if (m_bindings)
				m_bindings->unbind(*m_pair, *m_value);
		}

		Binder(Binder &&other) :
			m_bindings(other.m_bindings),
			m_pair(other.m_pair),
			m_value(other.m_value)
		{
			other.m_bindings = nullptr;
			other.m_pair = nullptr;
			other.m_value = nullptr;
		}

	private:
		Bindings *m_bindings;
		typename Map::value_type *m_pair;
		Value *m_value;
	};

	const_iterator begin(void) const
	{
		return m_bindings.cbegin();
	}

	const_iterator end(void) const
	{
		return m_bindings.cend();
	}

	const_iterator cbegin(void) const
	{
		return begin();
	}

	const_iterator cend(void) const
	{
		return end();
	}

	template <typename ...ArgsTypes>
	std::unique_ptr<Event::Listener> bind(const Key &key, ArgsTypes &&...args)
	{
		auto &value = m_bindings[key].emplace(std::forward<ArgsTypes>(args)...);
		if (m_callback)
			m_callback(true, key, value);
		auto &p = *m_bindings.find(key);
		return std::unique_ptr<Event::Listener>(new Binder(*this, p, value));
	}

private:
	friend Binder;
	Map m_bindings;
	const callback m_callback;

	void unbind(typename Map::value_type &pair, Value &value)
	{
		auto &map = pair.second;
		auto got = map.find(value);
		if (got == map.end())
			throw std::runtime_error("Can't unbind");
		if (m_callback)
			m_callback(false, pair.first, value);
		map.erase(got);
		if (map.size() == 0) {
			auto b_got = m_bindings.find(pair.first);
			if (b_got == m_bindings.end())
				throw std::runtime_error("Can't unbind");
			m_bindings.erase(b_got);
		}
	}
};

}
}