#pragma once

#include <functional>
#include "../../Input/IButton.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {
namespace Input {

class AButton : public System::Input::IButton
{
public:
	AButton(const std::string &name, std::function<bool (void)> read_fun);
	~AButton(void) override;

	const std::string& getName(void) const override;
	double getActivity(void) const override;

	bool getState(void) const override;

	void update(void);

protected:
	std::string m_name;
	std::function<bool (void)> m_read_fun;
	bool m_last_state;
	bool m_state;
};

}
}
}
}