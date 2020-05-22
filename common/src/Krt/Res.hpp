#include "Subtile/Resource/Model.hpp"
#include "Subtile/Resource/Texture.hpp"

#include "Subtile/Resource/Decl.hpp"

namespace Krt {

dir_export(res,
	dir(models,
		dir(etc),
		dir(npc,
			(sb::rs::Model, gordon),
			(sb::rs::Texture, gordon_dif)
		)
	)
)

}

#include "Subtile/Resource/DeclEnd.hpp"
