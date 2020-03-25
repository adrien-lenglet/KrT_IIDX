#pragma once

#include "../IInput.hpp"
#include "../Observer.hpp"

namespace Subtile {
namespace Input {

class Button : public IInput
{
public:
	Button(void);
	~Button(void);

	void update(void) override;
	Observer<bool>::Listener listen(const std::function<void (bool)> &callback);

private:
	Observer<bool> m_observer;
	//std::unique_ptr<Button::IAdapter> m_adapter;
};

}
}