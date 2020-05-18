#pragma once

#include "Subtile/Resource.hpp"

namespace Krt {

extern declfolder_export(res,
	declfolder(sub1,
		(int) a,
		(int) b
	),
	declfolder(sub2,
		(int) a,
		(int) b,
		declfolder(subsub,
			(double) deep_res
		)
	),
	(float) flres
)

}

#include "Subtile/ResourceEnd.hpp"