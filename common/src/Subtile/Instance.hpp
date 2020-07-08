#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/System/Observer.hpp"
#include "Resource/Shader.hpp"
#include "Cache.hpp"

namespace Subtile {

class World;
class SessionBase;

class Instance
{
public:
	Instance(bool isDebug = false, const std::string &name = "SUBTILE® Application");
	~Instance(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> createSession(ArgsTypes &&...args);

private:
	friend World;
	friend SessionBase;

	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	void scanInputs(void);

	using ShaderCache = Cache<util::ref_wrapper<rs::Shader>, std::unique_ptr<Shader>>;
	ShaderCache m_shaders;

	class UniqueShaderRef : public Shader
	{
	public:
		template <typename ...Args>
		UniqueShaderRef(Args &&...args) :
			m_ref(std::forward<Args>(args)...)
		{
		}

		std::unique_ptr<Shader::DescriptorSet> material(void) override
		{
			return (*m_ref)->material();
		}

		std::unique_ptr<Shader::DescriptorSet> object(void) override
		{
			return (*m_ref)->object();
		}

	private:
		ShaderCache::Ref m_ref;
	};

	UniqueShaderRef loadShader(rs::Shader &shaderres)
	{
		auto got = m_shaders.find(shaderres);
		if (got == m_shaders.end())
			return m_shaders.emplace(shaderres, m_system->loadShader(shaderres));
		else
			return got->second.new_ref();
	}
};

}

#include "World.hpp"
#include "Session.hpp"

namespace Subtile {

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> Instance::createSession(ArgsTypes &&...args)
	{
		auto res = SessionBase::getCtx().emplace_frame(std::function([&](){
			return std::make_unique<SessionType>(std::forward<ArgsTypes>(args)...);
		}), *this);
		SessionBase::getSessionStack().pop();
		return res;
	}
}