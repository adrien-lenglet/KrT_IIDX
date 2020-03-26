#include "Button.hpp"

namespace Subtile {
namespace Input {

Button::Button(void) :
	m_observer([this](auto &) {
	})
{
}

Button::~Button(void)
{
}

void Button::update(void)
{
	m_observer.update();
}

Observer<bool>::Listener Button::listen(const std::function<void (bool)> &callback)
{
	return m_observer.listen(callback);
}

}
}