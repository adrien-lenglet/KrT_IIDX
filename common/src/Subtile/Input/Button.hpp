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

private:
	bool m_is_strict;
	double m_analog_threshold;
	Observer<bool> m_observer;
	std::unique_ptr<NButton::IAdapter> m_adapter;
};

}
}