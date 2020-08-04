#include "Race.hpp"

namespace Krt {

Race::Race(void) :
	m_track(add<Track>())
{
	bind(m_track.done, [this](){
		done();
	});
}
Race::~Race(void)
{
}

void Race::render(void)
{
	m_track.render.render();
}

}