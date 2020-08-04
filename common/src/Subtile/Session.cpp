#include "Session.hpp"

namespace Subtile {

SessionBase::SessionBase(Instance &instance) :
	m_instance(instance),
	m_done(false)
{
}

SessionBase::~SessionBase(void)
{
}

void SessionBase::run(void)
{
	while (!m_done) {
		m_instance.m_system->scanInputs();
		m_instance.m_events.updateEvents();
		for (auto &w : m_worlds)
			w.events.updateEvents();
		render();
		//m_system.render();
	}
}

void SessionBase::done(void)
{
	m_done = true;
}

util::stack<std::reference_wrapper<Instance>>& SessionBase::getCtx(void)
{
	static thread_local util::stack<std::reference_wrapper<Instance>> res;

	return res;
}

util::stack<std::reference_wrapper<SessionBase>>& SessionBase::getSessionStack(void)
{
	static thread_local util::stack<std::reference_wrapper<SessionBase>> res;

	return res;
}

}