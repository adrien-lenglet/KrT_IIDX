#include "Subtile/Resource/Model.hpp"
#include "Subtile/Resource/Texture.hpp"

#include "Subtile/Resource/Decl.hpp"

namespace Krt {

dir_export(res,
	dir(models,
		dir(etc),
		dir(npc,
			(sb::rs::Model, gordon),
			(sb::rs::Texture, gordon_diff)
		)
	),
	dir(shaders,
		dir(diffuse_pipeline)
	)
)

}

#include "Subtile/Resource/DeclEnd.hpp"
