#pragma once

namespace Subtile {

template <typename... GroupingType>
class Listener;

template <template <typename...> class GroupingType, typename... RequestTypes, typename... ReturnTypes>
class Listener<GroupingType<RequestTypes...>, GroupingType<ReturnTypes...>>
{
public:
	class Observer
	{
	public:
		Observer(std::function<void (std::function<> signal)> update);
		~Observer(void);

		void update(void)
		{
			m_update(signal);
		}

		void addListener(Listener &listener, const RequestTypes &...args)
		{
			m_listeners.emplace
		}

	private:
		friend Listener;

		std::function<void ()> m_update;
		std::map<Listener*, Listener&> m_listeners;

		void signalListeners(const RequestTypes &...args, const ReturnTypes &...payload)
		{
			for (auto &l : m_listeners.at(std::make_tuple(args...)))
				l.second.m_callback( std::forward(payload)...);
		}

	};

	Listener(const RequestTypes &...args);
	~Listener(void)
	{
		unlisten();
	}

private:
	friend Observer;

	std::function<void (const ReturnTypes &...args)> m_callback;

	void unlisten(void)
	{
		m_callback = nullptr;
	}
};

}