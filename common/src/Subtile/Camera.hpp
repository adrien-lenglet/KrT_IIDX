#pragma once

#include "Entity.hpp"

namespace Subtile {

class Camera : public Entity<World>
{
public:
	Camera(void);
	~Camera(void);
};

}