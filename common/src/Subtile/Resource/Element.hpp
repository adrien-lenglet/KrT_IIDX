#pragma once

#include <string>
#include <stack>
#include "../Resource.hpp"

namespace Subtile {
namespace Resource {

class Folder;

class Element
{
	friend Folder;
	struct Context
	{
		Context(Folder *parent, const std::string &name) :
			parent(parent),
			name(name)
		{
		}

		Folder *parent;
		const std::string &name;
	};

	static std::stack<Context>& getStack(void);

public:
	Element(void);
	Element(const Context &ctx);
	virtual ~Element(void) = 0;

protected:
	Folder& getParent(void);
	std::string getPath(void) const;
	static std::string mergePaths(const std::string &a, const std::string &b);

private:
	Folder *m_parent;
	const std::string m_name;

	virtual void ship(const std::string &basedir) const = 0;
};

}
}

#include "Folder.hpp"