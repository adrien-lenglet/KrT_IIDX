#pragma once

#include <string>
#include <stack>
#include "../Resource.hpp"

namespace Subtile {
namespace Resource {

class Folder;

class Element
{
protected:
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

	using should_forward_name = std::false_type;

protected:
	Folder& getParent(void);
	const std::string& getName(void);
	const std::string& getId(void);
	std::string getPath(void) const;
	static std::string mergePaths(const std::string &a, const std::string &b);

private:
	Folder *m_parent;
	const std::string m_name;
	const std::string m_id;

	virtual void ship(const std::string &basedir) const = 0;

	std::string computeId(void) const;
};

}
}

#include "Folder.hpp"