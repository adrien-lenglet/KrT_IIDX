#pragma once

#include "Track.hpp"

namespace Krt {

class Race : public Instance::Session
{
public:
	Race(void);
	~Race(void);

	void render(void) override;
	VecWorldRef updated_worlds(void) override;

private:
	std::unique_ptr<Track> m_track;
	VecWorldRef m_worlds;
};

}