#pragma once

#include "util.hpp"

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
		for (auto &l : m_listeners)
			l.second.observerDestroyed();
	}

	void update(void)
	{
		if (m_listeners.size() > 0)
			m_update(m_signal_listeners);
	}

private:
	class ListenerImpl;
public:

	using Listener = std::unique_ptr<ListenerImpl>;
	Listener listen(const std::function<void (const ReturnTypes &...payload)> &callback, const std::function<void (void)> &observerDestroyed = [](){ throw std::runtime_error("Observer destroyed"); })
	{
		return m_listeners.template emplace<ListenerImpl>(*this, callback, observerDestroyed);
	}

private:
	friend ListenerImpl;

	const std::function<void (const ReturnTypes &...payload)> m_signal_listeners;
	const std::function<void (const std::function<void (const ReturnTypes &...payload)> &signal)> m_update;
	util::unique_set<ListenerImpl> m_listeners;

	void removeListener(ListenerImpl &listener)
	{
		auto got = m_listeners.find(listener);

		if (got == m_listeners.end())
			throw std::runtime_error("Listener to remove not found among listeners");
		m_listeners.erase(got);
	}

	class ListenerImpl
	{
	public:
		ListenerImpl(Observer &observer, const std::function<void (const ReturnTypes &...payload)> &callback, const std::function<void (void)> &observerDestroyed) :
			m_observer(observer),
			m_callback(callback),
			m_oberver_destroyed(observerDestroyed),
			m_has_unlisten(false)
		{
		}
		~ListenerImpl(void)
		{
			unlisten();
		}

	private:
		friend Observer;

		Observer &m_observer;
		const std::function<void (const ReturnTypes &...args)> m_callback;
		const std::function<void (void)> m_oberver_destroyed;
		bool m_has_unlisten;

		void unlisten(void)
		{
			if (!m_has_unlisten) {
				m_observer.removeListener(*this);
				m_has_unlisten = true;
			}
		}

		void observerDestroyed(void)
		{
			unlisten();
			m_oberver_destroyed();
		}
	};
};

}