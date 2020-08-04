#pragma once

#include "Track.hpp"

namespace Krt {

class Race : public sb::Session
{
public:
	Race(void);
	~Race(void) override;

	void render(void) override;

private:
	Track &m_track;
};

}