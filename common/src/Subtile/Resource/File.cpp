#include <fstream>
#include "File.hpp"

namespace Subtile {
namespace Resource {

File::Istream::Istream(std::stringstream &&ss) :
	std::stringstream(std::move(ss))
{
}

File::File(bool ship) :
	m_ship(ship)
{
}

File::File(const std::string &name, bool ship) :
	Element(Context(getStack().top().parent, name)),
	m_ship(ship)
{
}

File::Istream File::read(void) const
{
	beforeRead();

	std::stringstream ss;
	std::ifstream file(getPath(), std::ios::binary);

	ss << file.rdbuf();
	return Istream(std::move(ss));
}

void File::beforeRead(void) const
{
}

void File::ship(const std::string &basedir) const
{
	if (!m_ship)
		return;
	auto stream = read();

	std::ofstream o(mergePaths(basedir, getPath()), std::ios::binary);
	o << stream.rdbuf();
}

}
}