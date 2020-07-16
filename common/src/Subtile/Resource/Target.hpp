#pragma once

#include <vector>
#include "File.hpp"

namespace Subtile {
namespace Resource {

class Target : public File
{
public:
	Target(const std::vector<std::reference_wrapper<Target>> &deps = {}, bool ship = false);

protected:
	virtual void build(std::ostream &o) = 0;

private:
	std::vector<std::reference_wrapper<Target>> m_deps;

	bool is_up_to_date(void) const;
};

}
}