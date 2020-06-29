#pragma once

#include <vulkan/vulkan.h>
#undef assert
#include "../ISystem.hpp"
#include "Glfw.hpp"

namespace Subtile {
namespace System {

class Vk : public ISystem
{
public:
	Vk(bool isDebug = false);
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

	template <typename T, typename C, typename ...Args>
	static T create(C &&callable, Args &&...args)
	{
		T res;
		assert(callable(std::forward<Args>(args)..., &res));
		return res;
	}

	template <typename VkHandle>
	class Handle
	{
	public:
		Handle(VkHandle handle) :
			m_handle(handle)
		{
		}

		Handle(Handle &&other) :
			m_handle(other.m_handle)
		{
			m_handle = VK_NULL_HANDLE;
		}

		void destroy(VkHandle handle);

		~Handle(void)
		{
			if (m_handle != VK_NULL_HANDLE)
				destroy(m_handle);
		}

		operator VkHandle(void) const
		{
			return m_handle;
		}

	protected:
		VkHandle m_handle;
	};

	class Instance : public Handle<VkInstance>
	{
	public:
		Instance(bool isDebug, const util::svec &layers, const util::svec &extensions);

		template <typename FunType>
		FunType getProcAddr(const char *name)
		{
			auto res = vkGetInstanceProcAddr(m_handle, name);

			if (res == nullptr)
				throw std::runtime_error(std::string("Can't get proc '") + std::string(name) + std::string("'"));
			return reinterpret_cast<FunType>(res);
		}

		template <typename VkHandle>
		class Handle
		{
		public:
			Handle(Instance &instance, VkHandle handle) :
				m_instance(instance),
				m_handle(handle)
			{
			}

			Handle(Handle &&other) :
				m_instance(other.m_instance),
				m_handle(other.m_handle)
			{
				m_handle = VK_NULL_HANDLE;
			}

			void destroy(Instance &instance, VkHandle handle);

			~Handle(void)
			{
				if (m_handle != VK_NULL_HANDLE)
					destroy(m_instance, m_handle);
			}

			operator VkHandle(void) const
			{
				return m_handle;
			}

		protected:
			Instance &m_instance;
			VkHandle m_handle;
		};

	private:
		class Messenger : public Handle<VkDebugUtilsMessengerEXT>
		{
		public:
			Messenger(Instance &instance);

		private:
			VkDebugUtilsMessengerEXT create(Instance &instance);
		};

		std::optional<Messenger> m_messenger;

		VkInstance createInstance(const util::svec &layers, const util::svec &extensions);
		std::optional<Messenger> createMessenger(bool isDebug);
	};

	Instance m_instance;
};

}
}