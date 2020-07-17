#include <filesystem>
#include "Folder.hpp"

namespace Subtile {
namespace Resource {

Folder::Folder(void)
{
}

Folder::Folder(is_root_t, const std::string &name) :
	Element(Context(nullptr, name))
{
}

Folder::Folder(const std::string &name) :
	Element(Context(getStack().top().parent, name))
{
#ifndef DEBUG
	std::filesystem::create_directory(getPath());	// ensure folder is created on debug (for non user-created structures)
#endif
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

Folder::Hidden::Hidden(const std::string &name) :
	Folder(std::string(".") + name)
{
}

Folder::Hidden::~Hidden(void)
{
}

}
}