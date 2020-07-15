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

public:
	Instance(bool isDebug = false, const std::string &name = "SUBTILE® Application");
	~Instance(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> createSession(ArgsTypes &&...args);

	void scanInputs(void);

	template <typename ResType>
	class Shader
	{
		using Res = util::remove_cvr_t<ResType>;

	public:
		Shader(UniqueShaderRef &&shader_ref) :
			m_ref(std::move(shader_ref))
		{
		}
		Shader(Shader<Res> &&other) :
			m_ref(std::move(other.m_ref))
		{
		}

		using Material = sb::Shader::DescriptorSet::Handle<typename Res::materialTraits>;
		auto material(void)
		{
			return Material(m_ref.material());
		}

		using Object = sb::Shader::DescriptorSet::Handle<typename Res::objectTraits>;
		auto object(void)
		{
			return Object(m_ref.object());
		}

	private:
		template <typename>
		friend class Shader;

		UniqueShaderRef m_ref;
	};

private:
	friend World;
	friend SessionBase;

	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	UniqueShaderRef loadShaderRef(rs::Shader &shaderres)
	{
		auto got = m_shaders.find(shaderres);
		if (got == m_shaders.end())
			return m_shaders.emplace(shaderres, m_system->loadShader(shaderres));
		else
			return got->second.new_ref();
	}

	template <typename S>
	decltype(auto) loadShader(S &&shaderres)
	{
		return Shader<std::remove_cv_t<std::remove_reference_t<S>>>(loadShaderRef(std::forward<S>(shaderres)));
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