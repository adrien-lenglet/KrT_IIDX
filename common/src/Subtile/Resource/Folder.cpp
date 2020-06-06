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

}
}