#pragma once

#include "Subtile/Resource/Model.hpp"
#include "Subtile/Resource/Texture.hpp"

namespace Krt {
	class res_class
	{
		class models_class
		{
			class etc_class
			{
				public:
			};
			class npc_class
			{
				sb::rs::Model gordon_storage;
				sb::rs::Texture gordon_diff_storage;
				public:
				sb::rs::Model& gordon(void);
				sb::rs::Texture& gordon_diff(void);
			};
			etc_class etc_storage;
			npc_class npc_storage;
			public:
			etc_class& etc(void);
			npc_class& npc(void);
		};
		class shaders_class
		{
			public:
		};
		models_class models_storage;
		shaders_class shaders_storage;
		public:
		models_class& models(void);
		shaders_class& shaders(void);
	};
}
