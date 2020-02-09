#pragma once

#include <vector>

void vkAssert_real(VkResult res, const char *file, int line, const char *fun);
#define vkAssert(res) vkAssert_real(res, __FILE__, __LINE__, __func__)

namespace Vk {

template <typename T>
std::vector<T> retrieve(VkResult (*func)(uint32_t *count, T *props))
{
	uint32_t count = 0;

	vkAssert(func(&count, nullptr));
	std::vector<T> res(count);
	vkAssert(func(&count, res.data()));

	return res;
}

}