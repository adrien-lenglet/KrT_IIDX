#pragma once

#include "File.hpp"

namespace Subtile {
namespace Resource {

class Image : public File
{
public:
	Image(void);
	~Image(void) override;
};

}
}