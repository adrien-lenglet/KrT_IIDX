#include "Analog.hpp"

namespace Subtile {
namespace Input {

Analog::Analog(void) :
	m_observer([this](auto &) {
	})
{
}

Analog::~Analog(void)
{
}

void Analog::update(void)
{
	m_observer.update();
}

Observer<double>::Listener Analog::listen(const std::function<void (double)> &callback)
{
	return m_observer.listen(callback);
}

}
}