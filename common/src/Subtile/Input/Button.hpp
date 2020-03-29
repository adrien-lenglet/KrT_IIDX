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
	bool bind(System::IInput &input) override;

	Observer<bool>::Listener listen(const std::function<void (bool)> &callback);
	Observer<>::Listener listenPressed(const std::function<void (void)> &callback);
	Observer<>::Listener listenReleased(const std::function<void (void)> &callback);

private:
	bool m_is_strict;
	double m_analog_threshold;

	bool m_last_state;
	bool m_state;

	Observer<bool> m_observer;
	Observer<> m_observer_pressed;
	Observer<> m_observer_released;
	std::unique_ptr<NButton::IAdapter> m_adapter;
};

}
}