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

namespace Event {

class Observer
{
public:
	class Cluster;
	template <typename... Types>
	class Group;
	template <typename... Types>
	class GroupCb;

	virtual ~Observer(void) = default;

protected:
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
	void update(void) override;

private:
	std::vector<std::reference_wrapper<Observer>> m_observers;

	template <typename... GroupingType>
	friend class Group;
	template <typename... GroupingType>
	friend class GroupCb;
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
	template <typename... GroupingType>
	friend class GroupCb;

	void update(void) override;
};

class Socket;

template <typename ObserverType, template <typename...> class GroupingType, typename... StoreTypes, typename... ReturnTypes>
class Observer::Group<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>> : public Observer
{
protected:
	using UpdaterType = std::function<std::optional<std::tuple<ReturnTypes...>> (const StoreTypes &...)>;
	using CallbackType = std::function<void (const ReturnTypes &...)>;

public:
	Group(const UpdaterType &updater) :
		m_updater(updater)
	{
		static_cast<ObserverType&>(*this).Observer::Cluster::add(*this);
	}
	~Group(void) override
	{
	}

protected:
	friend Event::Socket;
	const UpdaterType m_updater;
	std::map<std::tuple<StoreTypes...>, Binding::Weak<CallbackType, true>> m_listeners;

	void update(void) override
	{
		for (auto &p : m_listeners) {
			auto res = m_updater(std::get<StoreTypes>(p.first)...);
			if (res)
				for (auto &listener : p.second)
					listener(std::get<ReturnTypes>(*res)...);
		}
	}

	void bind(Binding::Dependency::Socket &socket, const std::tuple<StoreTypes...> &req, const CallbackType &callback)
	{
		auto got = m_listeners.find(req);
		if (got == m_listeners.end()) {
			auto [it, success] = m_listeners.emplace(req, [this, req](){
				auto got = m_listeners.find(req);

				if (got == m_listeners.end())
					throw std::runtime_error("Can't destroy event");
				m_listeners.erase(got);
			});
			if (!success)
				throw std::runtime_error("Can't bind request");
			it->second.bind(socket, callback);
		} else
			got->second.bind(socket, callback);
	}
};

template <typename ObserverType, template <typename...> class GroupingType, typename... RequestTypes, typename... StoreTypes, typename... ReturnTypes>
class Observer::Group<ObserverType, GroupingType<RequestTypes...>, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>> : public Observer::Group<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>
{
	using Inherited = Observer::Group<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>;
	using UpdaterType = typename Inherited::UpdaterType;
	using CallbackType = typename Inherited::CallbackType;
	using ConverterType = std::function<std::tuple<StoreTypes...> (const RequestTypes &...)>;

public:
	Group(const ConverterType &converter, const UpdaterType &updater) :
		Observer::Group<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>(updater),
		m_converter(converter)
	{
	}
	~Group(void) override
	{
	}

private:
	friend Event::Socket;
	const ConverterType m_converter;

	void bind(Binding::Dependency::Socket &socket, const std::tuple<RequestTypes...> &request, const CallbackType &callback)
	{
		Observer::Group<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>::bind(socket, m_converter(std::get<RequestTypes>(request)...), callback);
	}
};

template <typename ObserverType, template <typename...> class GroupingType, typename... StoreTypes, typename... ReturnTypes>
class Observer::GroupCb<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>> : public Observer
{
protected:
	using UpdaterType = std::function<std::optional<std::tuple<ReturnTypes...>> (const StoreTypes &...)>;
	using CallbackType = std::function<void (const ReturnTypes &...)>;
	using ClusterCallbackType = std::function<Cluster::Optimized& (void)>;

public:
	GroupCb(const UpdaterType &updater, const ClusterCallbackType &callback) :
		m_updater(updater),
		m_cluster_cb(callback)
	{
		static_cast<ObserverType&>(*this).Observer::Cluster::add(*this);
	}
	~GroupCb(void) override
	{
	}

protected:
	friend Event::Socket;
	const UpdaterType m_updater;
	const ClusterCallbackType m_cluster_cb;
	std::map<std::tuple<StoreTypes...>, Binding::Weak<CallbackType, true>> m_listeners;

	void update(void) override
	{
		for (auto &p : m_listeners) {
			auto res = m_updater(std::get<StoreTypes>(p.first)...);
			if (res)
				for (auto &listener : p.second)
					listener(std::get<ReturnTypes>(*res)...);
		}
	}

	void bind(Binding::Dependency::Socket &socket, const std::tuple<StoreTypes...> &req, const CallbackType &callback)
	{
		auto got = m_listeners.find(req);
		if (got == m_listeners.end()) {
			auto [it, success] = m_listeners.emplace(req, [this, req](){
				auto got = m_listeners.find(req);

				if (got == m_listeners.end())
					throw std::runtime_error("Can't destroy event");
				if (m_cluster_cb)
					m_cluster_cb().remove(std::get<StoreTypes>(req)...);
				m_listeners.erase(got);
			});
			if (!success)
				throw std::runtime_error("Can't bind request");
			it->second.bind(socket, callback);
			if (m_cluster_cb)
				m_cluster_cb().add(std::get<StoreTypes>(req)...);
		} else
			got->second.bind(socket, callback);
	}
};

template <typename ObserverType, template <typename...> class GroupingType, typename... RequestTypes, typename... StoreTypes, typename... ReturnTypes>
class Observer::GroupCb<ObserverType, GroupingType<RequestTypes...>, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>> : public Observer::GroupCb<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>
{
	using Inherited = Observer::GroupCb<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>;
	using UpdaterType = typename Inherited::UpdaterType;
	using CallbackType = typename Inherited::CallbackType;
	using ClusterCallbackType = typename Inherited::ClusterCallbackType;
	using ConverterType = std::function<std::tuple<StoreTypes...> (const RequestTypes &...)>;

public:
	GroupCb(const ConverterType &converter, const UpdaterType &updater, const ClusterCallbackType &clusterCallback) :
		Observer::GroupCb<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>(updater, clusterCallback),
		m_converter(converter)
	{
	}
	~GroupCb(void) override
	{
	}

private:
	friend Event::Socket;
	const ConverterType m_converter;

	void bind(Binding::Dependency::Socket &socket, const std::tuple<RequestTypes...> &request, const CallbackType &callback)
	{
		Observer::GroupCb<ObserverType, GroupingType<StoreTypes...>, GroupingType<ReturnTypes...>>::bind(socket, m_converter(std::get<RequestTypes>(request)...), callback);
	}
};

}
}