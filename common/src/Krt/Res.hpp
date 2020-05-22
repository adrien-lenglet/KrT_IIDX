#include "Subtile/Resource/Decl.hpp"

namespace Krt {

dir_export(res,
	dir(sub1,
		(int, a),
		(int, b)
	),
	dir(sub2,
		(int, a),
		(int, b),
		dir(subsub,
			(double, deep_res)
		)
	),
	(float, flres)
)

}

#include "Subtile/Resource/DeclEnd.hpp"