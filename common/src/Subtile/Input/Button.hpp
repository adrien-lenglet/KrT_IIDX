#pragma once

#include "../IInput.hpp"
#include "../Observer.hpp"
#include "NButton/IAdapter.hpp"

namespace Subtile {
namespace Input {

class Button : public IInput
{
public:
	Button(bool isStrict = true, double analogThreshold = 0.5);
	~Button(void);

	void update(void) override;
	bool getState(void) const;
	bool isPressed(void) const;
	bool isReleased(void) const;
	bool bind(System::IInput &input) override;

private:
	bool m_is_strict;
	double m_analog_threshold;

	std::unique_ptr<NButton::IAdapter> m_adapter;
	bool m_last_state;
	bool m_state;
};

}
}