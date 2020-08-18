#include "Session.hpp"

namespace Subtile {

SessionBase::SessionBase(InstanceBase &instance) :
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
		for (auto &w : updated_worlds())
			w.get().events.updateEvents();
		m_instance.system().acquireNextImage();
		render();
		m_instance.system().presentImage();
	}
}

void SessionBase::done(void)
{
	m_done = true;
}

util::stack<std::reference_wrapper<InstanceBase>>& SessionBase::getCtx(void)
{
	static thread_local util::stack<std::reference_wrapper<InstanceBase>> res;

	return res;
}

util::stack<std::reference_wrapper<SessionBase>>& SessionBase::getSessionStack(void)
{
	static thread_local util::stack<std::reference_wrapper<SessionBase>> res;

	return res;
}

}