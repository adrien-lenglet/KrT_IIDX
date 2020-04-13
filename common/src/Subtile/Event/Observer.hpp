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

class Instance;

namespace Event {

class Observer
{
public:
	class Cluster;
	template <typename... Types>
	class Group;

	virtual ~Observer(void) = default;

private:
	friend Instance;
	virtual void update(void) = 0;
};

template <typename ObserverType, typename ...ArgsType>
struct Descriptor
{
	Descriptor(ObserverType &observer, ArgsType &&...args) :
		observer(observer),
		args(std::forward_as_tuple<ArgsType>(args)...)
	{
	}
	~Descriptor(void) = default;

	ObserverType &observer;
	const std::tuple<ArgsType...> args;
};

template <typename ObserverType>
class DescGen
{
public:
	DescGen(void) = default;
	~DescGen(void) = default;

	template <typename ...ArgsTypes>
	Descriptor<ObserverType, ArgsTypes...> operator()(ArgsTypes &&...args)
	{
		return Descriptor<ObserverType, ArgsTypes...>(getObserver(), std::forward<ArgsTypes...>(args)...);
	}

private:
	ObserverType& getObserver(void)
	{
		return static_cast<ObserverType&>(*this);
	}
};

class Socket;

template <typename ObserverType, template <typename...> class GroupingType, typename... RequestTypes, typename... StoreTypes, typename... ReturnTypes>
class Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>> : public Observer
{
public:
	using ConverterType = std::function<std::tuple<StoreTypes...> (const RequestTypes &...)>;
	using UpdaterType = std::function<std::optional<std::tuple<ReturnTypes...>> (const StoreTypes &...)>;
	using CallbackType = std::function<void (const ReturnTypes &...)>;
	using ModCallbackType = std::function<void (const StoreTypes &...)>;

	Group(const ConverterType &converter, const UpdaterType &updater, const ModCallbackType &addCallback = nullptr, const ModCallbackType &removeCallback = nullptr) :
		m_converter(converter),
		m_updater(updater),
		m_add_cb(addCallback),
		m_remove_cb(removeCallback)
	{
		getObserver().Cluster::add(*this);
	}
	~Group(void) override
	{
	}

private:
	class Listener : Event::Listener
	{
	public:
		Listener(Group &group, const std::tuple<StoreTypes...> &request, const CallbackType &callback) :
			m_group(group),
			m_request(request),
			m_callback(callback)
		{
		}
		~Listener(void) override
		{
			m_group.unlisten(*this);
		}

	private:
		friend Group;
		Group &m_group;
		const std::tuple<StoreTypes...> m_request;
		const CallbackType m_callback;
	};

	friend Listener;
	const ConverterType m_converter;
	const UpdaterType m_updater;
	const ModCallbackType m_add_cb;
	const ModCallbackType m_remove_cb;
	std::map<std::tuple<StoreTypes...>, std::map<Listener*, Listener&>> m_listeners;

	friend Event::Socket;
	std::unique_ptr<Event::Listener> listen(const std::tuple<RequestTypes...> &request, const CallbackType &callback)
	{
		Listener *res = nullptr;

		if constexpr (std::is_same<std::tuple<RequestTypes...>, std::tuple<StoreTypes...>>::value)
			res = new Listener(*this, request, callback);
		else
			res = new Listener(*this, m_converter(std::get<RequestTypes>(request)...), callback);

		m_listeners[res->m_request].emplace(res, *res);
		if (m_add_cb)
			m_add_cb(std::get<StoreTypes>(res->m_request)...);
		return std::unique_ptr<Event::Listener>(res);
	}

	void unlisten(Listener &listener)
	{
		auto got = m_listeners.find(listener.m_request);
		if (got != m_listeners.end()) {
			auto &got_map = got->second;
			auto l = got_map.find(&listener);
			if (l != got_map.end()) {
				if (m_remove_cb)
					m_remove_cb(std::get<StoreTypes>(l->second.m_request)...);
				got_map.erase(l);
				if (got_map.size() == 0)
					m_listeners.erase(got);
			} else
				throw std::runtime_error("Can't unlisten");
		} else
			throw std::runtime_error("Can't unlisten");
	}

	void update(void) override
	{
		for (auto &p : m_listeners) {
			auto res = m_updater(std::get<StoreTypes>(p.first)...);
			if (res)
				for (auto &l : p.second)
					l.second.m_callback(std::get<ReturnTypes>(*res)...);
		}
	}

	ObserverType& getObserver(void)
	{
		return static_cast<ObserverType&>(*this);
	}
};

template <typename ObserverType, template <typename...> class GroupingType, typename... RequestTypes, typename... ReturnTypes>
class Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>> : public Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>>
{
public:
	using UpdaterType = std::function<std::optional<std::tuple<ReturnTypes...>> (const RequestTypes &...)>;
	using ModCallbackType = std::function<void (const RequestTypes &...)>;

	Group(const UpdaterType &updater, const ModCallbackType &addCallback = nullptr, const ModCallbackType &removeCallback = nullptr) :
		Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>>(nullptr, updater, addCallback, removeCallback)
	{
	}

	~Group(void) override
	{
	}
};

class Observer::Cluster : public Observer
{
public:
	virtual ~Cluster(void) = default;

	void add(Observer &observer);
	void remove(Observer &observer);

private:
	std::map<util::ref_wrapper<Observer>, size_t> m_observers;

	template <typename... GroupingType>
	friend class Group;
	void update(void) override;
};

}
}

#include "Socket.hpp"