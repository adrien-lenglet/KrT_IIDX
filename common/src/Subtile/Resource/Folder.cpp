#include <filesystem>
#include "Folder.hpp"

namespace Subtile {
namespace Resource {

Folder::Folder(void)
{
}

Folder::Folder(const std::string &name) :
	Element(Context(nullptr, name))
{
}

Folder::~Folder(void)
{
}

void Folder::ship(const std::string &basedir) const
{
	std::filesystem::create_directory(mergePaths(basedir, getPath()));
	for (auto &c : m_children)
		c.ship(basedir);
}

}
}