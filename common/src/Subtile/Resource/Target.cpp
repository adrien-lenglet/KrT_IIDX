#include "Target.hpp"

namespace Subtile {
namespace Resource {

Target::Target(const std::vector<std::reference_wrapper<Target>> &deps, bool ship) :
	File(ship),
	m_deps(deps)
{
}

bool Target::is_up_to_date(void) const
{
	return false;
}

}
}