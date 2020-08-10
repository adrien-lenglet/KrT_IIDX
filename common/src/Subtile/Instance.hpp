#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/System/Observer.hpp"
#include "Resource/Shader.hpp"

namespace Subtile {

class World;
class SessionBase;
namespace Render {
class Pass;
}

class Instance
{
	Shader::Cache m_shaders;

public:
	Instance(bool isDebug = false, const std::string &name = "SUBTILE® Application");
	~Instance(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> createSession(ArgsTypes &&...args);

	void scanInputs(void);

	class Getter
	{
	public:
		Getter(Instance &ins) :
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

		template <typename ...Args>
		decltype(auto) loadShader(Args &&...args)
		{
			return m_ins.loadShader(std::forward<Args>(args)...);
		}

	private:
		Instance &m_ins;
	};

private:
	friend World;
	friend SessionBase;
	friend Render::Pass;
	friend Getter;

	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	ISystem& system(void);

	Shader::UniqueRef loadShaderRef(rs::Shader &shaderres);

	template <typename S>
	decltype(auto) loadShader(S &&shaderres)
	{
		return Shader::Loaded<std::remove_cv_t<std::remove_reference_t<S>>>(loadShaderRef(std::forward<S>(shaderres)));
	}
};

template <typename ShaderRes>
class Shader::DescriptorSet::Layout::Resolver::Foreign : public Shader::DescriptorSet::Layout::Resolver
{
public:
	Foreign(Instance &instance, ShaderRes &shaderres, size_t set_ndx) :
		m_loaded(Instance::Getter(instance).loadShader(shaderres)),
		m_layout(UniqueRef::template Getter<UniqueRefHolder>(m_loaded).get().setLayout(set_ndx))
	{
	}
	~Foreign(void) override
	{
	}

	const Layout& resolve(void) const override
	{
		return m_layout;
	}

private:
	Shader::Loaded<ShaderRes> m_loaded;
	const Layout &m_layout;
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