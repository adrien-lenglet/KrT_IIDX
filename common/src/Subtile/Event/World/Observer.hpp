#pragma once

#include "../Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

class Observer : public Event::Observer::Cluster
{
public:
	Observer(void)
	{
		add(input);
	}
	~Observer(void) override = default;

	class Input : public Cluster
	{
	public:
		Input(void)
		{
			add(static_cast<Cluster&>(analog));
		}
		~Input(void) = default;

		class Analog : public Cluster, public DescGen<Analog>, public Group<Analog, std::tuple<std::string>, std::tuple<double>>
		{
		public:
			Analog(void) :
				Group<Analog, std::tuple<std::string>, std::tuple<double>>([](const std::string &inputName) {
					static_cast<void>(inputName);
					return std::optional<std::tuple<double>>();
				})
			{
			}
			~Analog(void) override = default;
		} analog;

	} input;
};

}
}
}