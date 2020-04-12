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

	class Input : public Event::Observer::Cluster
	{
	public:
		Input(void)
		{
			add(analog);
		}
		~Input(void) = default;

		class Analog : public Event::Observer
		{
		public:
			Analog(void) = default;
			~Analog(void) override = default;

			template <typename ...ArgsTypes>
			Descriptor<Analog, ArgsTypes...> operator()(ArgsTypes &&...args)
			{
				return Descriptor<Analog, ArgsTypes...>(*this, std::forward<ArgsTypes...>(args)...);
			}

		private:
			friend Event::Socket;

			std::unique_ptr<Listener> listen(const std::string &inputName, const std::function<void (double)> &callback)
			{
				static_cast<void>(inputName);
				static_cast<void>(callback);
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