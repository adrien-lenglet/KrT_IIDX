#pragma once

#include "Track.hpp"

namespace Krt {

class Race : public Instance::Session
{
public:
	Race(void);
	~Race(void) override;

	void render(void) override;

private:
	Track &m_track;
};

}