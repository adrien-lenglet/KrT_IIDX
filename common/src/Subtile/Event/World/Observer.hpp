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
			add(analog);
		}
		~Input(void) = default;

		class Analog : public Cluster, public DescGen<Analog>, Group<std::tuple<std::string>, std::tuple<double>>
		{
		public:
			Analog(void) = default;
			~Analog(void) override = default;

		private:
			friend Event::Socket;

			std::unique_ptr<Listener> listen(const std::string &inputName, const std::function<void (double)> &callback)
			{
				static_cast<void>(inputName);
				static_cast<void>(callback);
				callback(3.14);
				return std::unique_ptr<Listener>(nullptr);
			}

			void update(void) override
			{
			}
		} analog;

	} input;
};

}
}
}