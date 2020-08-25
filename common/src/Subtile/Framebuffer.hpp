#pragma once

#include <vector>
#include "Image.hpp"
#include "Color.hpp"

namespace Subtile {

class Framebuffer
{
public:
	virtual ~Framebuffer(void) = default;

	template <typename RenderPassType>
	class Handle : public RenderPassType::Framebuffer::template Runtime<Handle<RenderPassType>>
	{
	public:
		Handle(std::unique_ptr<Framebuffer> &&framebuffer) :
			m_framebuffer(std::move(framebuffer))
		{
		}

		using RenderPass = RenderPassType;

		operator Framebuffer&(void)
		{
			return *m_framebuffer;
		}

	private:
		std::unique_ptr<Framebuffer> m_framebuffer;
	};
};

}