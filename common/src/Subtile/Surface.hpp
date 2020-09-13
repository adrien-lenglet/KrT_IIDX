#pragma once

#include <memory>
#include "Swapchain.hpp"
#include "Queue.hpp"

namespace Subtile {

class Surface
{
public:
	virtual ~Surface(void) = default;

	virtual std::unique_ptr<Swapchain> createSwapchain(const svec2 &extent, size_t desiredImageCount, sb::Image::Usage usage, sb::Queue &queue) = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Surface> &&surface) :
			m_surface(std::move(surface))
		{
		}

		auto swapchain(const svec2 &extent, size_t desiredImageCount, sb::Image::Usage usage, sb::Queue &queue)
		{
			return Swapchain::Handle(m_surface->createSwapchain(extent, desiredImageCount, usage, queue));
		}

	private:
		std::unique_ptr<Surface> m_surface;
	};
};

}