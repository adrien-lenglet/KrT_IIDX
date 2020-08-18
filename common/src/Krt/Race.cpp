#include "Race.hpp"

namespace Krt {

Race::Race(void) :
	m_track(instance.create<Track>()),
	m_worlds({*m_track})
{
	bind(m_track->done, [this](){
		done();
	});
}
Race::~Race(void)
{
}

void Race::render(void)
{
	m_track->render.render();
}

Race::VecWorldRef Race::updated_worlds(void)
{
	return m_worlds;
}

}