#pragma once

#include "../Binding.hpp"

namespace Subtile {

class Binding::Source : public Binding
{
public:
	Source(void);
	~Source(void) override;

private:
	std::vector<Dependency> m_dependencies;
};

}