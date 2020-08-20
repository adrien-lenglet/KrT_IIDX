#pragma once

#include <vector>

namespace Subtile {

class Model
{
public:
	virtual ~Model(void) = default;
};

/*template <typename VertexType>
class Model
{
public:
	using Vertex = VertexType;

	struct Triangle
	{
		using Vertex = typename Model::Vertex;

		Vertex a;
		Vertex b;
		Vertex c;

		auto& operator[](size_t ndx)
		{
			return reinterpret_cast<Vertex*>(this)[ndx];
		}

		auto& operator[](size_t ndx) const
		{
			return reinterpret_cast<const Vertex*>(this)[ndx];
		}
	};

	Model(std::vector<Triangle> &&triangles) :
		m_triangles(std::move(triangles))
	{
	}

	auto vertex_count(void) const
	{
		return m_triangles.size() * 3;
	}

	auto vertex_data(void) const
	{
		return reinterpret_cast<const Vertex*>(m_triangles.data());
	}

private:
	std::vector<Triangle> m_triangles;
};*/

}