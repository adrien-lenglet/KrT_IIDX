#include <filesystem>
#include <fstream>
#include <cstring>
#include "Model.hpp"
#include "tiny_obj_loader.h"

namespace Subtile {
namespace Resource {

Model::Model(void) :
	File(false),
	m_compiled(Folder::Mod(getParent()).add<Compiled>(getId() + "_compiled.sbobj", *this))
{
}

Model::~Model(void)
{
}

Model::Compiled::Compiled(Model &parent) :
	Target({parent}, true),
	m_parent(parent)
{
}

Model::Compiled::~Compiled(void)
{
}

std::vector<Model::Vertex> Model::Compiled::read(void) const
{
	auto got = Target::read();
	auto str = got.str();
	size_t count = str.size() / sizeof(Vertex);
	std::vector<Vertex> res;
	res.resize(count);
	std::memcpy(res.data(), str.data(), str.size());
	return res;
}

void Model::Compiled::build(std::ostream &o) const
{
	auto path = m_parent.getPath();
	std::vector<Vertex> res;
	std::ifstream file(path);
	if (!file.good())
		throw std::runtime_error(std::string("Can't open obj file: ") + path);
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &file)) {
		if (err.size() > 0)
			std::cerr << "ERROR: " << path << ": " << err << std::endl;
		throw std::runtime_error(std::string("Can't parse obj file: ") + path);
	}
	//if (warn.size() > 0)
	//	std::cout << "WARNING: " << path << ": " << warn << std::endl;
	if (err.size() > 0)
		std::cerr << "ERROR: " << path << ": " << err << std::endl;
	for (auto &shape : shapes) {
		size_t ndx = 0;
		for (auto &vert_count : shape.mesh.num_face_vertices) {
			std::vector<glm::vec3> pos;
			std::vector<glm::vec3> normal;
			std::vector<glm::vec2> uv;
			for (size_t i = 0; i < vert_count; i++) {
				auto indices = shape.mesh.indices.at(ndx++);
				if (indices.vertex_index >= 0)
					pos.emplace_back(attrib.vertices.at(indices.vertex_index * 3), attrib.vertices.at(indices.vertex_index * 3 + 1), attrib.vertices.at(indices.vertex_index * 3 + 2));
				if (indices.normal_index >= 0)
					normal.emplace_back(attrib.normals.at(indices.normal_index * 3), attrib.normals.at(indices.normal_index * 3 + 1), attrib.normals.at(indices.normal_index * 3 + 2));
				if (indices.texcoord_index >= 0)
					uv.emplace_back(attrib.texcoords.at(indices.texcoord_index * 2), attrib.texcoords.at(indices.texcoord_index * 2 + 1));
			}

			while (pos.size() < 3)
				pos.emplace_back(0.0);

			if (normal.size() != 3) {
				normal.clear();
				glm::vec3 comp_normal = glm::normalize(glm::cross(pos.at(1) - pos.at(0), pos.at(2) - pos.at(0)));
				for (size_t i = 0; i < 3; i++)
					normal.emplace_back(comp_normal);
			}

			while (uv.size() < 3)
				uv.emplace_back(0.0);

			for (size_t i = 0; i < pos.size(); i++) {
				decltype(res)::value_type vertex;
				vertex.pos = pos.at(i);
				vertex.normal = normal.at(i);
				vertex.uv = uv.at(i);
				res.emplace_back(vertex);
			}
		}
	}
	o.write(reinterpret_cast<const char*>(res.data()), res.size() * sizeof(decltype(res)::value_type));
}

}
}