#include <filesystem>
#include <fstream>
#include <sstream>
#include "Target.hpp"

namespace Subtile {
namespace Resource {

Target::Target(const std::vector<std::reference_wrapper<File>> &deps, bool ship) :
	File(ship),
	m_deps(deps)
{
}

void Target::beforeRead(void) const
{
	if (is_up_to_date())
		return;

	std::stringstream ss;
	build(ss);

	std::ofstream file(getPath(), std::ios::binary | std::ios::trunc);
	file << ss.rdbuf();
}

bool Target::is_up_to_date(void) const
{
	auto p = std::filesystem::path(getPath());

	if (!std::filesystem::exists(p))
		return false;
	for (auto &d : m_deps)
		d.get().beforeRead();
	auto last = std::filesystem::last_write_time(p);
	for (auto &d : m_deps)
		if (std::filesystem::last_write_time(d.get().getPath()) > last)
			return false;
	return true;
}

}
}