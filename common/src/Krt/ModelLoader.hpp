#include <vector>
#include "res.resdecl.hpp"

namespace Krt {

std::vector<decltype(res.shaders().vertex().pnu().loaded())::Vertex> loadObj(const std::string &path);

}