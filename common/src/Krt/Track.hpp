#pragma once

#include "Subtile/World.hpp"
#include "Subtile/Render.hpp"
#include "Subtile/Camera.hpp"

namespace Krt {

class EntityTest;

class Track : public sb::World
{
public:
	using Entity = sb::Entity<Track>;

	Track(void);
	~Track(void) override;

	Event<> done;
	sb::Camera &camera;
	int track_data = 96;

	sb::Render::Pass render;

private:
	EntityTest &entity;
};

}

#include "EntityTest.hpp"