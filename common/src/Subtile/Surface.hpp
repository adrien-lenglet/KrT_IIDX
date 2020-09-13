#pragma once

#include <memory>
#include "Queue.hpp"

namespace Subtile {

class Surface
{
public:
	virtual ~Surface(void) = default;

	virtual svec2 getExtent(void) const = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Surface> &&surface) :
			m_surface(std::move(surface))
		{
		}

		svec2 extent(void) const
		{
			return m_surface->getExtent();
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