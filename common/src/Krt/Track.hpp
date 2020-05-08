#pragma once

#include "Subtile/World.hpp"
#include "EntityTest.hpp"
#include "Subtile/Camera.hpp"

namespace Krt {

class Track : public sb::World
{
public:
	Track(void);
	~Track(void) override;

	Event<> done;
	sb::Camera &camera;

private:
	EntityTest &entity;
};

}