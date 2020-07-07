#pragma once

#include <stdexcept>

namespace Subtile {

template <typename Key, typename Value>
class Cache
{
public:
	class Entry;

private:
	using MapType = std::map<Key, Entry>;

public:
	Cache(void)
	{
	}

	class Entry
	{
	public:
		template <typename ...Args>
		Entry(MapType &map, const Key &key, Args &&...args) :
			m_map(map),
			m_key(key),
			m_value(std::forward<Args>(args)...),
			m_refs(0)
		{
		}

		class Ref
		{
		public:
			Ref(Entry &entry) :
				m_entry(entry)
			{
				m_entry.new_ref_created();
			}
			Ref(const Ref &other) :
				m_entry(other.m_entry)
			{
				m_entry.new_ref_created();
			}
			~Ref(void)
			{
				m_entry.ref_lost();
			}

			operator Value&(void)
			{
				return m_entry.m_value;
			}
			operator Value&(void) const
			{
				return m_entry.m_value;
			}

			auto operator->(void)
			{
				return &m_entry.m_value;
			}
			auto operator->(void) const
			{
				return &m_entry.m_value;
			}

		private:
			Entry &m_entry;
		};

		friend Ref;
		Ref new_ref(void)
		{
			return *this;
		}

	private:
		MapType &m_map;
		Key m_key;
		Value m_value;
		size_t m_refs;

		void new_ref_created(void)
		{
			m_refs++;
		}

		void ref_lost(void)
		{
			m_refs--;
			if (m_refs == 0)
				destroy();
		}

		void destroy(void)
		{
			auto got = m_map.find(m_key);
			if (got == m_map.end())
				throw std::runtime_error("Can't find self in cache");
			m_map.erase(got);
		}
	};

	using Ref = typename Entry::Ref;

public:
	class iterator : public MapType::iterator
	{
	public:
		template <typename ...Args>
		iterator(Args &&...args) :
			MapType::iterator(std::forward<Args>(args)...)
		{
		}
	};

	iterator find(const Key &k)
	{
		return m_cache.find(k);
	}

	iterator begin(void)
	{
		return m_cache.begin();
	}
	iterator end(void)
	{
		return m_cache.end();
	}

	template <typename ...Args>
	auto emplace(const Key &key, Args &&...args)
	{
		auto [it, suc] = m_cache.emplace(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(m_cache, key, std::forward<Args>(args)...));
		if (!suc)
			throw std::runtime_error("Can't insert stuff in cache");
		return it->second.new_ref();
	}

private:
	MapType m_cache;
};

}