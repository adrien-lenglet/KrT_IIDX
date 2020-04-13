#pragma once

#include "../IInput.hpp"
#include "../Observer.hpp"
#include "NAnalog/IAdapter.hpp"

namespace Subtile {
namespace Input {

class Analog : public IInput
{
public:
	Analog(double min = -1.0, double max = 1.0, bool isStrict = true, std::optional<double> def = std::optional<double>());
	~Analog(void) override;

	void update(void) override;
	double getState(void) const;
	bool bind(System::IInput &input) override;

private:
	double m_min;
	double m_max;
	bool m_is_strict;
	double m_default;

	std::unique_ptr<NAnalog::IAdapter> m_adapter;
	double m_value;
};

}
}