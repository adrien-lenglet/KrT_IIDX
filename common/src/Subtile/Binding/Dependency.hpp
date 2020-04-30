#pragma once

#include "../Binding.hpp"

namespace Subtile {

class Binding::Dependency : public Binding
{
public:
	Dependency(Socket &socket, Source &source);
	~Dependency(void) override;

private:
	Socket &m_socket;
	Source &m_source;
};

}