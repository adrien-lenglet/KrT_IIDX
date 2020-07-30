#include <iostream>
#include "EntityTest3.hpp"

namespace Krt {

EntityTest3::EntityTest3(void)
{
	std::cout << &world << std::endl;
}

EntityTest3::~EntityTest3(void)
{
}

}