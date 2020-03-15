#pragma once

#include <vector>

namespace Subtile {
namespace System {
namespace Vk {

void vkAssert(VkResult res, const char *file, int line, const char *fun);

}

#define vkAssert(res) Vk::vkAssert(res, __FILE__, __LINE__, __func__)

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

template <typename T, typename U>
std::vector<T> retrieve(VkResult (*func)(U a,uint32_t *count, T *props), U a)
{
	uint32_t count = 0;

	vkAssert(func(a, &count, nullptr));
	std::vector<T> res(count);
	vkAssert(func(a, &count, res.data()));

	return res;
}

template <typename T, typename U, typename V>
std::vector<T> retrieve(VkResult (*func)(U a, V b, uint32_t *count, T *props), U a, V b)
{
	uint32_t count = 0;

	vkAssert(func(a, b, &count, nullptr));
	std::vector<T> res(count);
	vkAssert(func(a, b, &count, res.data()));

	return res;
}

template <typename T, typename U>
std::vector<T> retrieve(void (*func)(U a,uint32_t *count, T *props), U a)
{
	uint32_t count = 0;

	func(a, &count, nullptr);
	std::vector<T> res(count);
	func(a, &count, res.data());

	return res;
}

}
}
}