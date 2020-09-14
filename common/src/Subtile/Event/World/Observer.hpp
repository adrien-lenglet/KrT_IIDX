#pragma once

#include <chrono>
#include "Subtile/Event/Observer.hpp"

namespace Subtile {

namespace Event {
namespace World {

class Socket;

class Observer : public Event::Observer::Cluster
{
public:
	Observer(void);
	~Observer(void) override;

	class Update : public Cluster, public DescGen<Update>, public Group<Update, std::tuple<>, std::tuple<double>>
	{
	public:
		Update(void);
		~Update(void) override;

	private:
		std::chrono::high_resolution_clock::time_point m_time_before;
	} update;

	void updateEvents(void);
};

}
}
}