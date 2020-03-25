#pragma once

#include <map>
#include <functional>
#include <memory>

namespace Subtile {

template <typename... ReturnTypes>
class Observer
{
public:
	Observer(std::function<void (const std::function<void (const ReturnTypes &...payload)> &signal)> update) :
		m_signal_listeners([this](const ReturnTypes &...payload) {
			for (auto &l : m_listeners)
				l.second.m_callback(payload...);
		}),
		m_update(update)
	{
	}
	~Observer(void)
	{
	}

	void update(void)
	{
		m_update(m_signal_listeners);
	}

private:
	class ListenerImpl;
public:

	using Listener = std::unique_ptr<ListenerImpl>;
	Listener listen(const std::function<void (const ReturnTypes &...payload)> &callback)
	{
		auto res = new ListenerImpl(*this, callback);

		m_listeners.emplace(res, *res);
		return Listener(res);
	}

private:
	friend ListenerImpl;

	const std::function<void (const ReturnTypes &...payload)> m_signal_listeners;
	const std::function<void (const std::function<void (const ReturnTypes &...payload)> &signal)> m_update;
	std::map<ListenerImpl*, ListenerImpl&> m_listeners;

	void removeListener(ListenerImpl &listener)
	{
		auto got = m_listeners.find(&listener);

		if (got != m_listeners.end())
			m_listeners.erase(got);
		else
			throw std::runtime_error("Listener to remove not found among listeners");
	}

	class ListenerImpl
	{
	public:
		ListenerImpl(Observer &observer, const std::function<void (const ReturnTypes &...payload)> &callback) :
			m_observer(observer),
			m_callback(callback)
		{
		}
		~ListenerImpl(void)
		{
			unlisten();
		}

	private:
		friend Observer;

		Observer &m_observer;
		std::function<void (const ReturnTypes &...args)> m_callback;

		void unlisten(void)
		{
			m_observer.removeListener(*this);
		}
	};
};

}