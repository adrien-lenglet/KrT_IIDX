#pragma once

#include "Subtile/World.hpp"
#include "EntityTest.hpp"

namespace Krt {

class Track : public Subtile::World
{
public:
	Track(void);
	~Track(void) override;

	Subtile::Entity::Event<> done;

private:
	EntityTest &entity;
};

}