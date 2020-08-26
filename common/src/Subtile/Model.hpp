#pragma once

#include "Buffer.hpp"

namespace Subtile {

class CommandBuffer;

class Model
{
public:
	virtual ~Model(void) = default;

	enum class IndexType {
		Uint16,
		Uint32
	};

	virtual void draw(CommandBuffer&) = 0;

	template <typename VertexType>
	class Typed;
};

template <typename VertexType>
class Model::Typed
{
	std::unique_ptr<Model> m_model;

public:
	Typed(std::unique_ptr<Model> &&model) :
		m_model(std::move(model))
	{
	}

	operator Model&(void)
	{
		return *m_model;
	}

	class Indexed16 : public Typed
	{
	public:
		Indexed16(std::unique_ptr<Model> &&model) :
			Typed(std::move(model))
		{
		}
	};

	class Indexed32 : public Typed
	{
	public:
		Indexed32(std::unique_ptr<Model> &&model) :
			Typed(std::move(model))
		{
		}
	};
};

}