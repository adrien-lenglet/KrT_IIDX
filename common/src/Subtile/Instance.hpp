#pragma once

#include <memory>
#include "../Subtile.hpp"
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/System/Observer.hpp"
#include "Shader.hpp"

namespace Subtile {

class WorldBase;
class SessionBase;
namespace Render {
class Pass;
}

class InstanceBase
{
	Shader::Cache m_shaders;
	RenderPass::Cache m_render_passes;

public:
	InstanceBase(bool isDebug = false, const std::string &name = "SUBTILE® Application");
	~InstanceBase(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	void scanInputs(void);

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

		template <typename ...Args>
		decltype(auto) loadShader(Args &&...args)
		{
			return m_ins.loadShader(std::forward<Args>(args)...);
		}

	private:
		InstanceBase &m_ins;
	};

private:
	friend WorldBase;
	friend SessionBase;
	friend Render::Pass;
	friend Getter;

	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	ISystem& system(void);

	Shader::Cache::Ref loadShaderRef(rs::Shader &shaderres);
	RenderPass::Cache::Ref loadRenderPassRef(rs::RenderPass &renderpassres);

	template <typename S>
	decltype(auto) loadShader(S &&shaderres)
	{
		return Shader::Loaded<std::remove_cv_t<std::remove_reference_t<S>>>(loadShaderRef(std::forward<S>(shaderres)));
	}
	template <typename R>
	decltype(auto) loadRenderPass(R &&renderpassres)
	{
		return RenderPass::Loaded<std::remove_cv_t<std::remove_reference_t<R>>>(loadRenderPassRef(std::forward<R>(renderpassres)));
	}


public:
	template <typename ResType>
	decltype(auto) load(ResType &&res)
	{
		static_cast<void>(res);

		if constexpr (std::is_base_of_v<rs::Shader, std::remove_reference_t<ResType>>) {
			return loadShader(std::forward<ResType>(res));
		} else if constexpr (std::is_base_of_v<rs::RenderPass, std::remove_reference_t<ResType>>) {
			return loadRenderPass(std::forward<ResType>(res));
		} else
			static_assert(std::is_same_v<ResType, ResType>, "Unsupported resource type");
	}
};

template <typename ShaderRes>
class Shader::DescriptorSet::Layout::Resolver::Foreign : public Shader::DescriptorSet::Layout::Resolver
{
public:
	Foreign(InstanceBase &instance, ShaderRes &shaderres, size_t set_ndx) :
		m_loaded(InstanceBase::Getter(instance).loadShader(shaderres)),
		m_layout((**RefGetter<CacheRefHolder>(m_loaded).get()).setLayout(set_ndx))
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

#include "Session.hpp"
#include "World.hpp"

namespace Subtile {

template <typename InstanceType>
class Instance : public InstanceBase
{
public:
	template <typename ...Args>
	Instance(Args &&...args) :
		InstanceBase(std::forward<Args>(args)...)
	{
	}

	using World = sb::World<InstanceType>;
	using Session = sb::Session;

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> createSession(ArgsTypes &&...args)
	{
		auto res = SessionBase::getCtx().emplace_frame(std::function([&](){
			return std::make_unique<SessionType>(std::forward<ArgsTypes>(args)...);
		}), *this);
		SessionBase::getSessionStack().pop();
		return res;
	}
};

}