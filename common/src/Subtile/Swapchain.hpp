#pragma once

#include <vector>
#include "Image.hpp"

namespace Subtile {

class Swapchain
{
public:
	virtual ~Swapchain(void) = default;

	virtual std::vector<Image2D>& getImages(void) = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Swapchain> &&swapchain) :
			m_swapchain(std::move(swapchain))
		{
		}

		std::vector<Image2D>& images(void)
		{
			return m_swapchain->getImages();
		}

	private:
		std::unique_ptr<Swapchain> m_swapchain;
	};
};

}