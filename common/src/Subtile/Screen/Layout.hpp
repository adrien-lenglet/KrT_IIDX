#pragma once

#include "Section.hpp"

namespace Subtile {

namespace Screen {

class Layout : public Section
{
public:
	Layout(void);
	virtual ~Layout(void) = 0;

private:
	void onRender(void) override final;
};

}
}