#pragma once

#include <string>

namespace Subtile {

class Input
{
public:
	virtual ~Input(void) = default;

	virtual void update(void) = 0;
	virtual const std::string& id(void) const = 0;
	virtual bool active(void) const = 0;
};

class Button : public Input
{
public:
	virtual bool state(void) const = 0;
	virtual bool pressed(void) const = 0;
	virtual bool released(void) const = 0;
};

class Analog : public Input
{
public:
	virtual double state(void) const = 0;
};

}