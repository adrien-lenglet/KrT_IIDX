#pragma once

#include "../System/Observer.hpp"

namespace Subtile {

class Entity;

namespace Event {
namespace World {

class Socket;

class Observer : public Event::Observer::Cluster
{
public:
	Observer(Subtile::Event::System::Observer &system);
	~Observer(void) override;

	Subtile::Event::System::Observer &system;

	class Update : public Cluster, public DescGen<Update>, public Group<Update, std::tuple<>, std::tuple<double>>
	{
	public:
		Update(void);
		~Update(void) override;

	private:
		std::chrono::high_resolution_clock::time_point m_time_before;
	} update;

private:
	friend Entity;
	friend SessionBase;

	void updateEvents(void);
};

}
}
}