#pragma once

#include "../IInput.hpp"
#include "../Observer.hpp"
#include "NAnalog/IAdapter.hpp"

namespace Subtile {
namespace Input {

class Analog : public IInput
{
public:
	Analog(double min, double max, bool isStrict);
	~Analog(void);

	void update(void) override;
	bool bind(System::IInput &input) override;

	Observer<double>::Listener listen(const std::function<void (double)> &callback);

private:
	double m_min;
	double m_max;
	bool m_is_strict;
	Observer<double> m_observer;
	std::unique_ptr<NAnalog::IAdapter> m_adapter;
};

}
}