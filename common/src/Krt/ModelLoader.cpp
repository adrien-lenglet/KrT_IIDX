#include <iostream>
#include <fstream>
#include <sstream>
#include "ModelLoader.hpp"

namespace Krt {

struct ModelParsing
{
	std::vector<decltype(res.shaders().vertex().pnu().loaded())::Vertex> model;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	static glm::vec3 parseVec3(const std::vector<std::string> &tokens)
	{
		if (tokens.size() != 4)
			throw std::runtime_error("Vec3 expecting 4 tokens");

		return glm::vec3(std::stof(tokens.at(1)), std::stof(tokens.at(2)), std::stof(tokens.at(3)));
	}

	static glm::vec2 parseVec2(const std::vector<std::string> &tokens)
	{
		/*if (tokens.size() != 3)
			throw std::runtime_error("Vec2 expecting 3 tokens");*/

		return glm::vec2(std::stof(tokens.at(1)), std::stof(tokens.at(2)));
	}

	void parseFace(const std::vector<std::string> &tokens)
	{
		struct Vertex {
			glm::vec3 pos;
			glm::vec3 normal;
			glm::vec2 uv;

			operator decltype(model)::value_type(void) const
			{
				decltype(model)::value_type res;

				res.pos = pos;
				res.normal = normal;
				res.uv = uv;
				return res;
			}
		};
		std::vector<Vertex> face;

		bool compute_normal = false;
		auto end = tokens.end();
		for (auto it = tokens.begin() + 1; it != end; it++) {
			std::stringstream fss(*it);
			std::vector<std::string> ndxs;
			std::string ndx;
			while (std::getline(fss, ndx, '/'))
				ndxs.emplace_back(ndx);
			if (!(ndxs.size() >= 1 && ndxs.size() <= 3))
				throw std::runtime_error("Expected 1 to 3 indices for face decl");
			
			glm::vec3 pos = positions.at(std::stoull(ndxs.at(0)) - 1);
			glm::vec3 normal(0.0);
			glm::vec2 uv(0.0);
			if (ndxs.size() >= 2) {
				if (ndxs.at(1).size() > 0)
					uv = uvs.at(std::stoull(ndxs.at(1)) - 1);
			}
			if (ndxs.size() == 3)
				normal = normals.at(std::stoull(ndxs.at(2)) - 1);
			else
				compute_normal = true;
			face.emplace_back(Vertex{pos, normal, uv});
		}

		if (face.size() < 3)
			throw std::runtime_error("Expected at least 3 vertices to make a face");
		{
			if (compute_normal) {
				auto normal = glm::normalize(glm::cross(face.at(1).pos - face.at(0).pos, face.at(2).pos - face.at(0).pos));
				for (auto &v : face)
					v.normal = normal;
			}
			auto end = face.end() - 1;
			for (auto it = face.begin() + 1; it != end; it++) {
				model.emplace_back(face.at(0));
				model.emplace_back(*it);
				model.emplace_back(*(it + 1));
			}
		}
	}

	void parse(const std::vector<std::string> &tokens)
	{
		size_t i = 0;

		auto &dir = tokens.at(i++);
		if (dir == "mtllib" || dir == "s" || dir == "usemtl" || dir == "o" || dir == "g")
			return;
		if (dir == "v") {
			positions.emplace_back(parseVec3(tokens));
			return;
		}
		if (dir == "vn") {
			normals.emplace_back(parseVec3(tokens));
			return;
		}
		if (dir == "vt") {
			uvs.emplace_back(parseVec2(tokens));
			return;
		}
		if (dir == "f") {
			parseFace(tokens);
			return;
		}

		throw std::runtime_error(std::string("Unknown obj directive: ") + dir);
	}
};

std::vector<decltype(res.shaders().vertex().pnu().loaded())::Vertex> loadObj(const std::string &path)
{
	ModelParsing parsing;
	std::ifstream file(path);
	if (!file.good())
		throw std::runtime_error(std::string("Can't open obj file: ") + path);
	std::string line;
	while (std::getline(file, line)) {
		if (line.size() == 0)
			continue;
		if (line.at(0) == '#')
			continue;
		
		std::stringstream liness(line);
		std::vector<std::string> tokens;
		std::string tok;
		while (std::getline(liness, tok, ' ')) {
			if (tok.size() == 0)
				continue;
			tokens.emplace_back(tok);
		}

		try {
			parsing.parse(tokens);
		} catch (const std::exception &e) {
			std::cerr << "Err at line: " << line << std::endl;
			std::cerr << e.what() << std::endl;
			throw;
		}
	}
	return parsing.model;
}

}