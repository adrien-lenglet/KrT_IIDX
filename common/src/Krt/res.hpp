#include "Subtile/Resource/Model.hpp"
#include "Subtile/Resource/Texture.hpp"

namespace Krt {
	class res_class {
		class models{
			class etc{
			};
			class npc{
				private: sb::rs::Model gordon_storage;
				public: sb::rs::Model& gordon(void);
				private: sb::rs::Texture gordon_diff_storage;
				public: sb::rs::Texture& gordon_diff(void);
			};
		};
		class shaders{
		};
	};
}
