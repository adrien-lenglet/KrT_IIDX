#pragma once

#include <filesystem>
#include <stdexcept>
#include <vector>
#include <set>
#include <string>
#include <sstream>

namespace std {
namespace fs = filesystem;
}

namespace Subtile {
namespace Resource {
namespace Compiler {

static std::string strip_name(const std::string &in)
{
	size_t i = 0;

	if (in.at(0) == '[') {
		i++;
		while (i < in.size() && in.at(i) != ']')
			i++;
		i++;
		while (i < in.size() && in.at(i) == ' ')
			i++;
	}
	auto res = in.substr(i);
	if (res.size() == 0)
		throw std::runtime_error("Name of file stripped is empty !");
	return res;
}

class modules_entry
{
public:
	modules_entry(const modules_entry *parent, const std::fs::path &path) :
		m_parent(parent),
		m_path(path),
		m_is_directory(std::fs::is_directory(m_path)),
		m_name(path.filename().string()),
		m_id(strip_name(path.stem().string()))
	{
	}

	auto& getPath(void) const
	{
		return m_path;
	}

	auto isDirectory(void) const
	{
		return m_is_directory;
	}

	auto& getName(void) const
	{
		return m_name;
	}

	auto& getId(void) const
	{
		return m_id;
	}

	const modules_entry* resolve_in_dir(const std::string &id) const
	{
		for (auto &c : m_children)
			if (c.getId() == id)
				return &c;
		return nullptr;
	}

	// resolve in the whole scope
	const modules_entry* resolve(const std::string &id) const
	{
		auto in_dir = resolve_in_dir(id);
		if (in_dir)
			return in_dir;
		if (getId() == id)
			return this;
		if (m_parent == nullptr)
			return nullptr;
		else
			return m_parent->resolve(id);
	}

	const modules_entry& resolve_scope_expr(const std::string &expr) const
	{
		std::vector<std::string> exprs;
		std::string buf;

		char last = 0;
		for (auto &c : expr) {
			if (c == ':' && last == ':')
				flush_buf(exprs, buf);
			if (c == '_' || std::isalpha(c) || std::isdigit(c))
				buf.push_back(c);
			last = c;
		}
		flush_buf(exprs, buf);

		if (exprs.size() == 0)
			throw std::runtime_error("Expected expression for scope resolution");
		const modules_entry *res = resolve(exprs.at(0));
		if (res == nullptr)
			throw std::runtime_error(std::string("Expression '") + expr + std::string("': Can't resolve '") + exprs.at(0) + std::string("' from '") + getPath().string() + std::string("'"));

		size_t i = 1;
		while (i < exprs.size()) {
			auto &former_dir = *res;
			res = former_dir.resolve_in_dir(exprs.at(i));
			if (res == nullptr)
				throw std::runtime_error(std::string("Expression '") + expr + std::string("': Can't resolve '") + exprs.at(i) + std::string("' from '") + former_dir.getPath().string() + std::string("'"));
			i++;
		}
		return *res;

	}

	void addChild(const std::fs::path &path)
	{
		auto &got = m_children.emplace_back(this, path);
		auto found = m_children_ids.find(got.getId());
		if (found != m_children_ids.end()) {
			std::stringstream ss;
			ss << "Two items have the same id '" << got.getId() << "' within folder '" << m_path.string() << "': ";
			for (auto &c : m_children)
				if (c.getId() == got.getId()) {
					ss << c.getName();
					break;
				}
			ss << " and " << got.getName();
			throw std::runtime_error(ss.str());
		}
		m_children_ids.emplace(got.getId());
	}

	auto& getChildren(void)
	{
		return m_children;
	}

private:
	const modules_entry *m_parent;
	std::fs::path m_path;
	bool m_is_directory;
	std::string m_name;
	std::string m_id;
	std::set<std::string> m_children_ids;
	std::vector<modules_entry> m_children;

	static void flush_buf(std::vector<std::string> &res, std::string &buf)
	{
		res.emplace_back(buf);
		buf.clear();
	}
};

}
}
}