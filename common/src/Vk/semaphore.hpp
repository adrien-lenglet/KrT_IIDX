#pragma once

namespace Vk {

class Semaphore
{
public:
	Semaphore(Instance &vk);
	Semaphore(Semaphore &&that);	
	~Semaphore(void);

	Instance &vk;

	VkSemaphore semaphore;

private:
	VkSemaphore createSemaphore(void);
};

}