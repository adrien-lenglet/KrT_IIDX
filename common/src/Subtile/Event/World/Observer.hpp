#pragma once

#include <chrono>
#include "../Observer.hpp"
#include "../../Input/Analog.hpp"
#include "../../Input/Button.hpp"
#include "util.hpp"

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

		class Analog : public Cluster, public DescGen<Analog>, public Group<Analog, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Analog>>, std::tuple<double>>
		{
		public:
			Analog(Input &input);
			~Analog(void) override;

		private:
			Input &m_input;
		} analog;

		class Button : public Cluster, public DescGen<Button>, public Group<Button, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<bool>>
		{
		public:
			Button(Input &input);
			~Button(void) override;

		private:
			Input &m_input;
		} button;

		class Setter
		{
		public:
			Setter(Input &input) :
				m_input(input)
			{
			}
			~Setter(void)
			{
			}

			template <typename ...ArgsTypes>
			void addAnalog(const std::string &name, ArgsTypes &&...args) const
			{
				const auto [it, s] = m_input.m_inputs.emplace(name, new Subtile::Input::Analog(std::forward<ArgsTypes>(args)...));
				if (!s)
					throw std::runtime_error(std::string("Can't create analog input: '") + name + std::string("'"));
			}

			template <typename ...ArgsTypes>
			void addButton(const std::string &name, ArgsTypes &&...args) const
			{
				const auto [it, s] = m_input.m_inputs.emplace(name, new Subtile::Input::Button(std::forward<ArgsTypes>(args)...));
				if (!s)
					throw std::runtime_error(std::string("Can't create button input: '") + name + std::string("'"));
			}

		private:
			Input &m_input;
		};

		void set(const std::function<void (const Setter &setter)> &binder)
		{
			m_inputs.clear();
			binder(Setter(*this));
		}

	private:
		friend Analog;
		friend Button;

		std::map<std::string, std::unique_ptr<IInput>> m_inputs;
		Observer::Cluster m_input_update;
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