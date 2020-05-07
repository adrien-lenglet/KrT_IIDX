#include "Session.hpp"

namespace Subtile {

SessionBase::SessionBase(const Ctx &ctx) :
	m_system(ctx.system),
	m_events(ctx.events),
	m_done(false)
{
}

SessionBase::~SessionBase(void)
{
}

void SessionBase::run(void)
{
	while (!m_done) {
		m_system.scanInputs();
		m_events.updateEvents();
		getScreenLayout().render();
		m_system.render();
	}
}

void SessionBase::done(void)
{
	m_done = true;
}

thread_local util::stack<SessionBase::Ctx> SessionBase::m_ctx;
thread_local util::stack<std::reference_wrapper<SessionBase>> SessionBase::m_stack;

}