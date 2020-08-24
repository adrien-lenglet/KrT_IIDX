#pragma once

#include <vector>
#include "Image.hpp"

namespace Subtile {

class Framebuffer
{
public:
	virtual ~Framebuffer(void) = default;

	template <typename RenderPassType>
	class Handle
	{
	public:
		Handle(std::unique_ptr<Framebuffer> &&framebuffer) :
			m_framebuffer(std::move(framebuffer))
		{
		}

	private:
		std::unique_ptr<Framebuffer> m_framebuffer;
	};
};

}