#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Element.hpp"

namespace Subtile {
namespace Resource {

class Target;

class File : public Element
{
public:
	File(bool ship);

	class Istream : public std::stringstream
	{
	public:
		Istream(std::stringstream &&ss);
	};

	Istream read(void) const;

protected:
	File(const std::string &name, bool ship);

	friend Target;
	virtual void beforeRead(void) const;

private:
	bool m_ship;

	void ship(const std::string &basedir) const override final;
};

}
}