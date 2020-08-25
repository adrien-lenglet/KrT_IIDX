#pragma once

#include <memory>

namespace Subtile {

class Semaphore
{
public:
	virtual ~Semaphore(void) = default;

	class Handle
	{
	public:
		Handle(std::unique_ptr<Semaphore> &&semaphore) :
			m_semaphore(std::move(semaphore))
		{
		}

		operator Semaphore&(void)
		{
			return *m_semaphore;
		}

	private:
		std::unique_ptr<Semaphore> m_semaphore;
	};
};

}