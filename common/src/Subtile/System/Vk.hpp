#pragma once

#include <vulkan/vulkan.h>
#include "../ISystem.hpp"
#include "Glfw.hpp"

namespace Subtile {
namespace System {

class Vk : public ISystem
{
public:
	Vk(void);
	~Vk(void);

	void scanInputs(void) override;
	const std::map<std::string, System::IInput&>& getInputs(void) override;

private:
	Glfw m_glfw;

	static const std::string& resultToString(VkResult res);
	static void assert(VkResult res);

	template <typename T>
	static std::vector<T> enumerate(VkResult (*callable)(uint32_t*, T*))
	{
		uint32_t size;

		assert(callable(&size, nullptr));
		std::vector<T> res(size);
		assert(callable(&size, res.data()));
		return res;
	}

	template <typename T, typename C, typename ...Args>
	static std::vector<T> enumerateAbstract(C &&callable, Args &&...args)
	{
		uint32_t size;

		assert(callable(std::forward<Args>(args)..., &size, nullptr));
		std::vector<T> res(size);
		assert(callable(std::forward<Args>(args)..., &size, res.data()));
		return res;
	}

	class Instance
	{
	public:
		Instance(const util::svec &layers, const util::svec &extensions);
		~Instance(void);

	private:
		VkInstance m_instance;
	};

	Instance m_instance;
};

}
}