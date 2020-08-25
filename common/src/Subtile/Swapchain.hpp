#pragma once

#include <vector>
#include "Image.hpp"
#include "Semaphore.hpp"

namespace Subtile {

class Swapchain
{
public:
	virtual ~Swapchain(void) = default;

	class Image2D : public sb::Image2D
	{
	public:
		template <typename ...Args>
		Image2D(Swapchain &swapchain, Args &&...args) :
			sb::Image2D(std::forward<Args>(args)...),
			m_swapchain(swapchain)
		{
		}

		class Getter
		{
		public:
			Getter(void) = default;

			Swapchain& get(Image2D &img)
			{
				return img.m_swapchain;
			}
		};

	private:
		friend Getter;
		Swapchain &m_swapchain;
	};

	virtual std::vector<Image2D>& getImages(void) = 0;
	virtual size_t acquireNextImage(Semaphore &semaphore) = 0;

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

		size_t acquireNextImage(Semaphore &semaphore)
		{
			return m_swapchain->acquireNextImage(semaphore);
		}

	private:
		std::unique_ptr<Swapchain> m_swapchain;
	};
};

}