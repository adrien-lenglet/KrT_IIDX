#pragma once

#include "../IInput.hpp"
#include "../Observer.hpp"

namespace Subtile {
namespace Input {

class Analog : public IInput
{
public:
	Analog(void);
	~Analog(void);

	void update(void) override;
	Observer<double>::Listener listen(const std::function<void (double)> &callback);

private:
	Observer<double> m_observer;
	//std::unique_ptr<Analog::IAdapter> m_adapter;
};

}
}