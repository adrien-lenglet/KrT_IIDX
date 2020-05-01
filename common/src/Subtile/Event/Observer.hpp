#pragma once

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <optional>
#include <type_traits>
#include "../Binding.hpp"
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

class Observer::Cluster : public Observer
{
public:
	class Optimized;

	virtual ~Cluster(void) = default;

protected:
	void add(Observer &observer);

private:
	std::vector<std::reference_wrapper<Observer>> m_observers;

	template <typename... GroupingType>
	friend class Group;
	void update(void) override;
};


class Observer::Cluster::Optimized : public Observer
{
public:
	virtual ~Optimized(void) = default;

protected:
	void add(Observer &observer);
	void remove(Observer &observer);

private:
	std::map<util::ref_wrapper<Observer>, size_t> m_observers;

	template <typename... GroupingType>
	friend class Group;
	void update(void) override;
};

class Socket;

template <typename ObserverType, template <typename...> class GroupingType, typename... RequestTypes, typename... StoreTypes, typename... ReturnTypes>
class Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>> : public Observer
{
	using ConverterType = std::function<std::tuple<StoreTypes...> (const RequestTypes &...)>;
	using UpdaterType = std::function<std::optional<std::tuple<ReturnTypes...>> (const StoreTypes &...)>;
	using CallbackType = std::function<void (const ReturnTypes &...)>;
	using ClusterCallbackType = std::function<Cluster::Optimized& (void)>;
	using BindingsType = Binding::Weak<CallbackType, true>;

public:
	Group(const ConverterType &converter, const UpdaterType &updater, const ClusterCallbackType &clusterCallback = nullptr) :
		m_converter(converter),
		m_updater(updater),
		m_cluster_cb(clusterCallback)
	{
		static_cast<ObserverType&>(*this).Cluster::add(*this);
	}
	~Group(void) override
	{
	}

private:
	const ConverterType m_converter;
	const UpdaterType m_updater;
	const ClusterCallbackType m_cluster_cb;
	std::map<std::tuple<StoreTypes...>, Binding::Weak<CallbackType, true>> m_listeners;

	friend Event::Socket;

	auto getRequest(const std::tuple<RequestTypes...> &request)
	{
		if constexpr (std::is_same<std::tuple<RequestTypes...>, std::tuple<StoreTypes...>>::value)
			return request;
		else
			return m_converter(std::get<RequestTypes>(request)...);
	}

	void bind(const std::tuple<RequestTypes...> &request, Binding::Dependency::Socket &socket, const CallbackType &callback)
	{
		auto req = getRequest(request);

		auto got = m_listeners.find(req);
		if (got == m_listeners.end()) {
			auto [it, success] = m_listeners.emplace(req, [this, req](){
				m_cluster_cb().remove(std::get<StoreTypes>(req)...);
			});
			if (!success)
				throw std::runtime_error("Can't bind request");
			it->second.bind(socket, callback);
			m_cluster_cb().add(std::get<StoreTypes>(req)...);
		} else
			got->second.bind(socket, callback);
	}

	void update(void) override
	{
		for (auto &p : m_listeners) {
			auto res = m_updater(std::get<StoreTypes>(p.first)...);
			if (res)
				for (auto &listener : p.second)
					listener(std::get<ReturnTypes>(*res)...);
		}
	}
};

template <typename ObserverType, template <typename...> class GroupingType, typename... RequestTypes, typename... ReturnTypes>
class Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>> : public Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>>
{
public:
	using UpdaterType = std::function<std::optional<std::tuple<ReturnTypes...>> (const RequestTypes &...)>;
	using ClusterCallbackType = std::function<Cluster::Optimized& (void)>;

	Group(const UpdaterType &updater, const ClusterCallbackType &clusterCallback = nullptr) :
		Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>>(nullptr, updater, clusterCallback)
	{
	}

	~Group(void) override
	{
	}
};

}
}

#include "Socket.hpp"
