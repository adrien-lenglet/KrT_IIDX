#include "Subtile/Resource/Model.hpp"
#include "Subtile/Resource/Texture.hpp"

namespace Krt {
	class res_class
	{
		class models
		{
			class etc
			{
				public:
			};
			class npc
			{
				sb::rs::Model gordon_storage;
				sb::rs::Texture gordon_diff_storage;
				public:
				sb::rs::Model& gordon(void);
				sb::rs::Texture& gordon_diff(void);
			};
			public:
		};
		class shaders
		{
			public:
		};
		public:
	};
}
