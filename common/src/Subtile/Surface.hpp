#pragma once

#include <memory>
#include <optional>
#include "Queue.hpp"

namespace Subtile {

class Surface
{
public:
	virtual ~Surface(void) = default;

	virtual svec2 getExtent(void) const = 0;
	virtual std::optional<svec2> isResized(void) const = 0;
	virtual bool shouldClose(void) const = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Surface> &&surface) :
			m_surface(std::move(surface))
		{
		}

		auto extent(void) const
		{
			return m_surface->getExtent();
		}

		auto resized(void) const
		{
			return m_surface->isResized();
		}

		bool shouldClose(void) const
		{
			return m_surface->shouldClose();
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