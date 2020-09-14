#pragma once

#include <memory>
#include "../Subtile.hpp"
#include "System.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Swapchain.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "Queue.hpp"

namespace Subtile {

class WorldBase;

class InstanceBase
{
public:
	InstanceBase(bool isDebug, bool isProfile);
	~InstanceBase(void);

	class Getter
	{
	public:
		Getter(InstanceBase &ins) :
			m_ins(ins)
		{
		}

		auto& system(void)
		{
			return *m_ins.m_system;
		}
		auto& system(void) const
		{
			return *m_ins.m_system;
		}

	private:
		InstanceBase &m_ins;
	};

private:
	friend WorldBase;
	friend Getter;

	std::unique_ptr<System> m_system;

	System& system(void);

public:
	auto surface(const svec2 &extent, const std::string &title)
	{
		return Surface::Handle(system().createSurface(extent, title));
	}

	auto device(Surface &surface, const Queue::Set &queues)
	{
		return Device::Handle(system().createDevice(surface, queues));
	}

	void scanInputs(void)
	{
		system().scanInputs();
	}
};

}

#include "World.hpp"

namespace Subtile {

template <typename InstanceType>
class Instance : public InstanceBase
{
public:
	Instance(bool isDebug, bool isProfile) :
		InstanceBase(isDebug, isProfile)
	{
	}

	template <typename WorldType>
	using World = sb::World<InstanceType, WorldType>;

	template <typename Type, typename ...Args>
	decltype(auto) create(Args &&...args)
	{
		if constexpr (std::is_base_of_v<WorldBase, Type>)
			return createWorld<Type>(std::forward<Args>(args)...);
		else
			static_assert(!std::is_same_v<Type, Type>, "Unknown primitive type to create");
	}

private:
	template <typename WorldType, typename ...ArgsTypes>
	std::unique_ptr<WorldType> createWorld(ArgsTypes &&...args)
	{
		static_assert(std::is_base_of_v<typename WorldType::instance_type, InstanceType>, "Incompatible world");

		auto res = WorldBase::getInstanceStack().emplace_frame(std::function([&]() -> auto {
			return EntityBase::getCtx().emplace_frame(std::function([&]() -> auto {
				return std::make_unique<WorldType>(std::forward<ArgsTypes>(args)...);
			}), nullptr, nullptr);
		}), *this);
		EntityBase::getEntityStack().pop();
		return res;
	}
};

}