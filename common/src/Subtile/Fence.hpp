#pragma once

#include <memory>

namespace Subtile {

class Fence
{
public:
	virtual ~Fence(void) = default;

	virtual void wait(void) = 0;
	virtual void reset(void) = 0;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Fence> &&fence) :
			m_fence(std::move(fence))
		{
		}

		void wait(void)
		{
			m_fence->wait();
		}

		void reset(void)
		{
			m_fence->reset();
		}

		operator Fence&(void)
		{
			return *m_fence;
		}

	private:
		std::unique_ptr<Fence> m_fence;
	};
};

}