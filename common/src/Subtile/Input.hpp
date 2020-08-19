#pragma once

#include "Event/Observer.hpp"
#include "System.hpp"

namespace Subtile {

class Input : public Event::Observer
{
public:
	virtual ~Input(void) = default;

	virtual bool bind(System::Input &input) = 0;

	class Button;
	class Analog;
};

class Input::Button : public Input
{
public:
	Button(bool isStrict = true, double analogThreshold = 0.5);
	~Button(void);

	void update(void) override;
	bool getState(void) const;
	bool isPressed(void) const;
	bool isReleased(void) const;
	bool bind(System::Input &input) override;


	class IAdapter
	{
	public:
		virtual ~IAdapter(void) = default;

		virtual bool read(void) = 0;

		class Analog;
		class Button;
		class Disconnected;
	};

private:
	bool m_is_strict;
	double m_analog_threshold;

	std::unique_ptr<IAdapter> m_adapter;
	bool m_last_state;
	bool m_state;
};

class Input::Button::IAdapter::Analog : public Input::Button::IAdapter
{
public:
	Analog(System::Input::Analog &input, double threshold);
	~Analog(void) override;

	bool read(void) override;

private:
	System::Input::Analog &m_input;
	double m_threshold;
};

class Input::Button::IAdapter::Button : public Input::Button::IAdapter::IAdapter
{
public:
	Button(System::Input::Button &input);
	~Button(void) override;

	bool read(void) override;

private:
	System::Input::Button &m_input;
};

class Input::Button::IAdapter::Disconnected : public Input::Button::IAdapter::IAdapter
{
public:
	Disconnected(void);
	~Disconnected(void) override;

	bool read(void) override;
};

class Input::Analog : public Input
{
public:
	Analog(double min = -1.0, double max = 1.0, bool isStrict = true, std::optional<double> def = std::optional<double>());
	~Analog(void) override;

	void update(void) override;
	double getState(void) const;
	bool bind(System::Input &input) override;

	class IAdapter
	{
	public:
		virtual ~IAdapter(void) = default;

		virtual double read(void) = 0;

		class Analog;
		class Button;
		class Disconnected;
	};

private:
	double m_min;
	double m_max;
	bool m_is_strict;
	double m_default;

	std::unique_ptr<IAdapter> m_adapter;
	double m_value;
};

class Input::Analog::IAdapter::Analog : public Input::Analog::IAdapter
{
public:
	Analog(System::Input::Analog &input, double min, double max);
	~Analog(void) override;

	double read(void) override;

private:
	System::Input::Analog &m_input;
	double m_min;
	double m_max;
};

class Input::Analog::IAdapter::Button : public Input::Analog::IAdapter
{
public:
	Button(System::Input::Button &input, double min, double max);
	~Button(void) override;

	double read(void) override;

private:
	System::Input::Button &m_input;
	double m_min;
	double m_max;
};

class Input::Analog::IAdapter::Disconnected : public Input::Analog::IAdapter
{
public:
	Disconnected(double value);
	~Disconnected(void) override;

	double read(void) override;

public:
	double m_value;
};

}