#include <fstream>
#include "Observer.hpp"
#include "../../ISystem.hpp"
#include "Subtile/scp.hpp"

namespace Subtile {
namespace Event {
namespace System {

rt_scc(Observer,
	scp::Observer(ISystem &system) :
		util::dep<ISystem&>(system),
		input(system)
	{
		add(input);
		add(static_cast<Cluster&>(update));
	}

	scp::~Observer(void)
	{
	}

	scc(Input,
		scp::Input(ISystem &system) :
			util::dep<ISystem&>(system),
			analog(*this),
			button(*this)
		{
			add(static_cast<Cluster&>(analog));
			add(static_cast<Cluster&>(button));
			add(m_input_update);
		}

		scp::~Input(void)
		{
		}

		void scp::set(const std::function<void (const Setter &setter)> &binder)
		{
			if (m_inputs.size() != 0)
				throw std::runtime_error("Can't rebind inputs");
			binder(Setter(*this));
			m_bindings = loadBindings();
			for (const auto &p : m_bindings)
				m_inputs.at(p.first)->bind(static_cast<ISystem&>(*this).getInputs().at(p.second));
		}

		std::map<std::string, std::string> scp::loadBindings(void) const
		{
			std::map<std::string, std::string> res;

			res.emplace("quit", "KEY_ESCAPE");

			return res;
		}

		scc(Analog,
			scp::Analog(Input &input) :
				Observer::GroupCb<Analog, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Analog>>, std::tuple<double>>(
				[this](const std::string &inputName){
					return util::ref_wrapper(dynamic_cast<Subtile::Input::Analog&>(*m_input.m_inputs.at(inputName)));
				}, [](const util::ref_wrapper<Subtile::Input::Analog> &input) {
					return input.get().getState();
				}, [this](void) -> auto& {
					return m_input.m_input_update;
				}),
				m_input(input)
			{
			}

			scp::~Analog(void)
			{
			}
		)

		scc(Button,
			scp::Button(Input &input) :
				Observer::GroupCb<Button, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<bool>>(
				[this](const std::string &inputName){
					return util::ref_wrapper(dynamic_cast<Subtile::Input::Button&>(*m_input.m_inputs.at(inputName)));
				}, [](const util::ref_wrapper<Subtile::Input::Button> &input) {
					return input.get().getState();
				}, [this](void) -> auto& {
					return m_input.m_input_update;
				}),
				pressed(input),
				released(input),
				m_input(input)
			{
				add(static_cast<Observer::Cluster&>(pressed));
				add(static_cast<Observer::Cluster&>(released));
			}

			scp::~Button(void)
			{
			}

			scc(Pressed,
				scp::Pressed(Input &input) :
					Observer::GroupCb<Pressed, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<>>(
					[this](const std::string &inputName){
						return util::ref_wrapper(dynamic_cast<Subtile::Input::Button&>(*m_input.m_inputs.at(inputName)));
					}, [](const util::ref_wrapper<Subtile::Input::Button> &input) -> std::optional<std::tuple<>> {
						if (input.get().isPressed())
							return std::make_tuple();
						else
							return std::nullopt;
					}, [this](void) -> auto& {
						return m_input.m_input_update;
					}),
					m_input(input)
				{
				}

				scp::~Pressed(void)
				{
				}
			)

			scc(Released,
				scp::Released(Input &input) :
					Observer::GroupCb<Released, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<>>(
					[this](const std::string &inputName){
						return util::ref_wrapper(dynamic_cast<Subtile::Input::Button&>(*m_input.m_inputs.at(inputName)));
					}, [](const util::ref_wrapper<Subtile::Input::Button> &input) -> std::optional<std::tuple<>> {
						if (input.get().isReleased())
							return std::make_tuple();
						else
							return std::nullopt;
					}, [this](void) -> auto& {
						return m_input.m_input_update;
					}),
					m_input(input)
				{
				}

				scp::~Released(void)
				{
				}
			)
		)
	)

	scc(Update,
		scp::Update(void) :
			Observer::Group<Update, std::tuple<>, std::tuple<double>>([this](){
				auto now = std::chrono::high_resolution_clock::now();
				double res = std::chrono::duration<double>(now - m_time_before).count();
				m_time_before = now;
				return res;
			}),
			m_time_before(std::chrono::high_resolution_clock::now())
		{
		}

		scp::~Update(void)
		{
		}
	)

	scc(System,
		scp::System(void)
		{
		}

		scp::~System(void)
		{
		}

		scc(Quit,
			scp::Quit(void) :
				m_quit(false)
			{
			}

			scp::~Quit(void)
			{
			}

			void scp::operator()(void)
			{
				m_quit = true;
			}

			scp::operator bool(void) const
			{
				return m_quit;
			}
		)
	)

	void scp::updateEvents(void)
	{
		Event::Observer::Cluster::update();
	}
)

}
}
}