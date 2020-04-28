#pragma once

namespace Subtile {
namespace Event {

class Listener
{
public:
	virtual ~Listener(void) = 0;
};

class DoubleListener
{
public:
	virtual ~DoubleListener(void) = 0;
};

}
}