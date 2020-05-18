#include "Subtile/Resource.hpp"

namespace Krt {

	/*declfolder(sub1,
		(int) a,
		(int) b
	)*/

declfolder_export(res,
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

/*declfolder_export(res,
	declfolder(sub1),
	declfolder(sub2)
)*/

}

#include "Subtile/ResourceEnd.hpp"