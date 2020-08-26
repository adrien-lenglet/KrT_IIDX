#pragma once

#include <vector>
#include <memory>
#include "../Binding.hpp"

namespace Subtile {

namespace Render {
class Pass;
}

namespace Event {

template <typename ObserverType, typename ...ArgsType>
struct Descriptor;
template <typename ObserverType>
class DescGen;

class Socket
{
public:
	Socket(void);
	~Socket(void);

	template <typename ...ReqTypes, typename ...Args>
	void bind(const Descriptor<ReqTypes...> &req, Args &&...args)
	{
		req.observer.bind(m_dependencies, req.args, std::forward<Args>(args)...);
	}

	template <typename ObserverType, typename ...Args>
	void bind(DescGen<ObserverType> &reqGen, Args &&...args)
	{
		auto req = reqGen();
		req.observer.bind(m_dependencies, req.args, std::forward<Args>(args)...);
	}

	template <typename T, typename ...PayloadTypes>
	void trigger(T &triggered, PayloadTypes &&...args)
	{
		triggered.trigger(*this, std::forward<PayloadTypes>(args)...);
	}

	template <typename RenderType>
	void bind(Render::Pass &pass, RenderType &&render);

private:
	Binding::Dependency::Socket m_dependencies;
};

}
}