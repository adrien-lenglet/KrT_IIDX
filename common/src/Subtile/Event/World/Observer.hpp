#pragma once

#include <chrono>
#include "../Observer.hpp"
#include "../../Input/Analog.hpp"
#include "../../Input/Button.hpp"
#include "../../ISystem.hpp"
#include "util.hpp"

namespace Subtile {

class EntityImpl;

namespace Event {
namespace World {

class Socket;

class Observer : public Event::Observer::Cluster, private util::dep<ISystem&>
{
public:
	Observer(ISystem &system);
	~Observer(void) override;

private:
	/*class Lifetime : public Event::Observer::Cluster
	{
	public:
		Lifetime(void);
		~Lifetime(void);

		class Add : public Event::Observer
		{
		public:
			Add(void);
			~Add(void);

			std::unique_ptr<Listener> operator()(Entity &parent, std::unique_ptr<Entity> &to_add);

		private:
			Bindings<util::ref_wrapper<Entity>, std::unique_ptr<Entity>> m_to_add;

			void update(void) override;
		} add;
	} lifetime;*/

public:
	class Input : public Cluster, private util::dep<ISystem&>
	{
	public:
		Input(ISystem &system);
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

			class Pressed : public Cluster, public DescGen<Pressed>, public Group<Pressed, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<>>
			{
			public:
				Pressed(Input &input);
				~Pressed(void) override;

			private:
				Input &m_input;
			} pressed;

			class Released : public Cluster, public DescGen<Released>, public Group<Released, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<>>
			{
			public:
				Released(Input &input);
				~Released(void) override;

			private:
				Input &m_input;
			} released;

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

	private:
		friend Analog;
		friend Button;
		friend Subtile::Instance;

		std::map<std::string, std::unique_ptr<IInput>> m_inputs;
		std::map<std::string, std::string> m_bindings;
		Observer::Cluster::Optimized m_input_update;

		void set(const std::function<void (const Setter &setter)> &binder)
		{
			if (m_inputs.size() != 0)
				throw std::runtime_error("Can't rebind inputs");
			binder(Setter(*this));
			m_bindings = loadBindings();
			for (const auto &p : m_bindings)
				m_inputs.at(p.first)->bind(static_cast<ISystem&>(*this).getInputs().at(p.second));
		}
		std::map<std::string, std::string> loadBindings(void) const;
		void saveBindings(void) const;
	} input;

	class Update : public Cluster, public DescGen<Update>, public Group<Update, std::tuple<>, std::tuple<double>>
	{
	public:
		Update(void);
		~Update(void) override;

	private:
		std::chrono::high_resolution_clock::time_point m_time_before;
	} update;

	class System
	{
	public:
		System(void);
		~System(void);

		class Quit
		{
		public:
			Quit(void);
			~Quit(void);

			void operator()(void);
			operator bool(void) const;

		private:
			bool m_quit;
		} quit;
	} system;

private:
	friend EntityImpl;
};

}
}
}

#include "../../Entity.hpp"
