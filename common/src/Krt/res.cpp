#include "res.hpp"

namespace Krt {
	sb::rs::Model& res_class::models_class::npc_class::gordon(void)
	{
		return gordon_storage;
	}
	sb::rs::Texture& res_class::models_class::npc_class::gordon_diff(void)
	{
		return gordon_diff_storage;
	}
	res_class::models_class::etc_class& res_class::models_class::etc(void)
	{
		return etc_storage;
	}
	res_class::models_class::npc_class& res_class::models_class::npc(void)
	{
		return npc_storage;
	}
	res_class::models_class& res_class::models(void)
	{
		return models_storage;
	}
	res_class::shaders_class& res_class::shaders(void)
	{
		return shaders_storage;
	}
}
