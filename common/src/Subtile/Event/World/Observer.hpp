#pragma once

#include <chrono>
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
		~Input(void) override;

		class Analog : public Cluster, public DescGen<Analog>, public Group<Analog, std::tuple<std::string>, std::tuple<std::string>, std::tuple<double>>
		{
		public:
			Analog(void);
			~Analog(void) override;
		} analog;

		class Button : public Cluster, public DescGen<Button>, public Group<Button, std::tuple<std::string>, std::tuple<bool>>
		{
		public:
			Button(void);
			~Button(void) override;
		} button;

	} input;

	class Update : public Cluster, public DescGen<Update>, public Group<Update, std::tuple<>, std::tuple<double>>
	{
	public:
		Update(void);
		~Update(void) override;

	private:
		std::chrono::high_resolution_clock::time_point m_time_before;
	} update;
};

}
}
}