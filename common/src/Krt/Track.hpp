#pragma once

#include "Subtile/World.hpp"
#include "EntityTest.hpp"

namespace Krt {

class Track : public sb::World
{
public:
	Track(void);
	~Track(void) override;

	Event<> done;

private:
	EntityTest &entity;
};

}