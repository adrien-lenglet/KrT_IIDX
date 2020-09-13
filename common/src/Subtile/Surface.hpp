#pragma once

#include <memory>
#include "Queue.hpp"

namespace Subtile {

class Surface
{
public:
	virtual ~Surface(void) = default;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Surface> &&surface) :
			m_surface(std::move(surface))
		{
		}

		operator Surface&(void)
		{
			return *m_surface;
		}

	private:
		std::unique_ptr<Surface> m_surface;
	};
};

}