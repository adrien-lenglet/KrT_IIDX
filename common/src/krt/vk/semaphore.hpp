
#pragma once

class Semaphore
{
public:
	Semaphore(Vk &vk);
	Semaphore(Semaphore &&that);	
	~Semaphore(void);

	Vk &vk;

	VkSemaphore semaphore;

private:
	VkSemaphore createSemaphore(void);
};
