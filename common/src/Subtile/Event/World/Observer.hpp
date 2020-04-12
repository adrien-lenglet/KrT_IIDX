#pragma once

#include "../Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

class Observer : public Event::Observer::Cluster
{
public:
	Observer(void);
	~Observer(void) override;

	class Input : public Cluster
	{
	public:
		Input(void);
		~Input(void);

		class Analog : public Cluster, public DescGen<Analog>, public Group<Analog, std::tuple<std::string>, std::tuple<double>>
		{
		public:
			Analog(void);
			~Analog(void) override;
		} analog;

	} input;
};

}
}
}