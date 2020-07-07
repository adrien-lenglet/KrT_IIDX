#pragma once

#include "ISystem.hpp"
#include "Event/System/Observer.hpp"
#include "Screen/Layout.hpp"
#include "Math.hpp"
#include "util.hpp"

namespace Subtile {

class Instance;
class World;

template <class FinalType>
class Session;

class SessionBase : public Event::Socket
{
public:
	SessionBase(Instance &instance);
	virtual ~SessionBase(void) = 0;

	void run(void);

protected:
	virtual Screen::Layout& getScreenLayout(void) = 0;
	void done(void);

	template <class T>
	using Class = typename T::template Impl<T>;

	template <typename WorldType, typename ...ArgsTypes>
	auto& addWorld(ArgsTypes &&...args);

	template <class LayoutType, typename ...Args>
	std::unique_ptr<Screen::Layout> createLayout(Args &&...args)
	{
		return util::make_derived<Class<LayoutType>, Screen::Layout>(std::forward<Args>(args)...);
	}

private:
	friend Instance;
	template <class FinalType>
	friend class Session;

	static util::stack<std::reference_wrapper<Instance>>& getCtx(void);
	static util::stack<std::reference_wrapper<SessionBase>>& getSessionStack(void);

	Instance &m_instance;
	util::unique_set<World> m_worlds;
	bool m_done;
};

}

#include "Camera.hpp"
#include "Screen/Subsection.hpp"

namespace Subtile {

template <class FinalType>
class Session : public SessionBase
{
public:
	Session(void) :
		SessionBase(getCtx().top())
	{
		getSessionStack().emplace(*this);
	}
	~Session(void) override
	{
	}

	using Layout = Screen::Section::UserDerive<Screen::Layout>;

	class Subsection : public Screen::Section::UserDerive<Screen::Subsection>
	{
	public:
		Subsection(Camera &camera) :
			Screen::Section::UserDerive<Screen::Subsection>(camera)
		{
		}
		Subsection(const std::function<Camera& (FinalType&)> &resolver) :
			Screen::Section::UserDerive<Screen::Subsection>(resolver(static_cast<FinalType&>(getSessionStack().top().get())))
		{
		}
		~Subsection(void)
		{
		}
	};
};

}

#include "Instance.hpp"

namespace Subtile {

	template <typename WorldType, typename ...ArgsTypes>
	auto& SessionBase::addWorld(ArgsTypes &&...args)
	{
		auto &res = World::getInstanceStack().emplace_frame(std::function([&]() -> auto& {
			return Entity::getCtx().emplace_frame(std::function([&]() -> auto& {
				return m_worlds.emplace<WorldType>(std::forward<ArgsTypes>(args)...);
			}), nullptr, nullptr);
		}), m_instance);
		Entity::getEntityStack().pop();
		return res;
	}
}