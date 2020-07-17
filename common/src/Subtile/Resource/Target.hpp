#pragma once

#include <vector>
#include "File.hpp"

namespace Subtile {
namespace Resource {

class Target : public File
{
public:
	Target(const std::vector<std::reference_wrapper<File>> &deps = {}, bool ship = false);

protected:
	void beforeRead(void) const override;

	virtual void build(std::ostream &o) const = 0;

private:
	std::vector<std::reference_wrapper<File>> m_deps;

	bool is_up_to_date(void) const;
};

}
}