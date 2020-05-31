#pragma once

#include "util.hpp"

namespace Subtile {

template <typename ...Args>
class Cache;

template <template <typename...> class GroupingType, typename ...ReqTypes, typename CachedType>
class Cache<GroupingType<ReqTypes...>, CachedType>
{
	using Key = std::tuple<ReqTypes...>;

public:
	Cache(void)
	{
	}
	~Cache(void)
	{
	}

	class Entry
	{
	public:
		template <typename ...Args>	
		Entry(Cache &cache, Args &&...args) :
			m_cache(cache),
			m_key(nullptr),
			m_value(cache.build(std::forward<Args>(args)...)),
			m_ref_count(0)
		{
		}
		~Entry(void)
		{
		}

		class Ref
		{
		public:
			Ref(Entry &entry) :
				m_entry(entry)
			{
				m_entry.refCreated();
			}
			Ref(Ref &&other) :
				m_entry(other.m_entry)
			{
				m_entry.refCreated();
			}
			~Ref(void)
			{
				m_entry.refDestroyed();
			}

			auto& operator*(void) { return *m_entry; }
			auto& operator*(void) const { return *m_entry; }
			auto& operator->(void) { return *m_entry; }
			auto& operator->(void) const { return *m_entry; }

		private:
			Entry &m_entry;
		};

		auto& operator*(void) { return m_value; }
		auto& operator*(void) const { return m_value; }
		auto& operator->(void) { return m_value; }
		auto& operator->(void) const { return m_value; }

		Ref createRef(void)
		{
			return Ref(*this);
		}

	private:
		friend Ref;
		friend Cache;
		Cache &m_cache;
		const Key *m_key;
		CachedType m_value;
		size_t m_ref_count;

		void setKey(const Key &key)
		{
			m_key = &key;
		}

		void refCreated(void)
		{
			m_ref_count++;
		}

		void refDestroyed(void)
		{
			m_ref_count--;
			if (m_ref_count == 0)
				m_cache.destroy(*m_key);
		}
	};

	using Point = typename Entry::Ref;

	Point resolve(ReqTypes &&...args)
	{
		auto req = std::make_tuple(std::forward<ReqTypes>(args)...);
		auto got = m_cache.find(req);

		if (got == m_cache.end()) {
			auto [it, success] = m_cache.emplace(std::piecewise_construct, req, std::forward_as_tuple(*this, std::forward<ReqTypes>(args)...));
			if (!success)
				throw std::runtime_error("Can't emplace value in cache");
			it->second.setKey(it->first);
			got = it;
		}
		return got->second.createRef();
	}

protected:
	virtual CachedType build(const ReqTypes &...args) const = 0;

private:
	friend Entry;
	std::map<Key, Entry> m_cache;

	void destroy(const Key &key)
	{
		auto got = m_cache.find(key);

		if (got == m_cache.end())
			throw std::runtime_error("Can't remove value from cache");
		m_cache.erase(got);
	}
};

}