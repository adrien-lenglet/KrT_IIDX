#include <filesystem>
#include <fstream>
#include "Element.hpp"
#include "File.hpp"
#include "Folder.hpp"
#include "Image.hpp"
#include "Model.hpp"
#include "RenderPass.hpp"
#include "Target.hpp"

namespace Subtile {
namespace Resource {

std::stack<Element::Context>& Element::getStack(void)
{
	static thread_local std::stack<Element::Context> res;

	return res;
}

Element::Element(void) :
	Element(getStack().top())
{
}

Element::Element(const Element::Context &ctx) :
	m_parent(ctx.parent),
	m_name(ctx.name),
	m_id(computeId())
{
}

Element::~Element(void)
{
}

Folder& Element::getParent(void)
{
	return *m_parent;
}

const std::string& Element::getName(void)
{
	return m_name;
}

const std::string& Element::getId(void)
{
	return m_id;
}

std::string Element::getPath(void) const
{
	if (m_parent)
		return mergePaths(m_parent->getPath(), m_name);
	else
		return m_name;
}

std::string Element::mergePaths(const std::string &a, const std::string &b)
{
	static const std::string sep("/");

	return a + sep + b;
}

std::string Element::computeId(void) const
{
	auto path = std::filesystem::path(m_name);

	return path.stem().string();
}

File::Istream::Istream(std::stringstream &&ss) :
	std::stringstream(std::move(ss))
{
}

File::File(bool ship) :
	m_ship(ship)
{
}

File::File(const std::string &name, bool ship) :
	Element(Context(getStack().top().parent, name)),
	m_ship(ship)
{
}

File::Istream File::read(void) const
{
	beforeRead();

	std::stringstream ss;
	std::ifstream file(getPath(), std::ios::binary);

	ss << file.rdbuf();
	return Istream(std::move(ss));
}

void File::beforeRead(void) const
{
}

void File::ship(const std::string &basedir) const
{
	if (!m_ship)
		return;
	auto stream = read();

	std::ofstream o(mergePaths(basedir, getPath()), std::ios::binary);
	o << stream.rdbuf();
}

Folder::Folder(void)
{
}

Folder::Folder(is_root_t, const std::string &name) :
	Element(Context(nullptr, name))
{
}

Folder::Folder(const std::string &name) :
	Element(Context(getStack().top().parent, name))
{
#ifndef DEBUG
	std::filesystem::create_directory(getPath());	// ensure folder is created on debug (for non user-created structures)
#endif
}

Folder::~Folder(void)
{
}

void Folder::ship(const std::string &basedir) const
{
	std::filesystem::create_directory(mergePaths(basedir, getPath()));
	for (auto &c : m_children)
		c.ship(basedir);
}

Folder::Hidden::Hidden(const std::string &name) :
	Folder(std::string(".") + name)
{
}

Folder::Hidden::~Hidden(void)
{
}

Image::Image(void) :
	File(true)
{
}

Image::~Image(void)
{
}

RenderPass::RenderPass(void) :
	File(false)
{
}

RenderPass::~RenderPass(void)
{
}

Target::Target(const std::vector<std::reference_wrapper<File>> &deps, bool ship) :
	File(ship),
	m_deps(deps)
{
}

void Target::beforeRead(void) const
{
	if (is_up_to_date())
		return;

	std::stringstream ss;
	build(ss);

	std::ofstream file(getPath(), std::ios::binary | std::ios::trunc);
	file << ss.rdbuf();
}

bool Target::is_up_to_date(void) const
{
#ifndef DEBUG
	return true;
#endif

	auto p = std::filesystem::path(getPath());

	if (!std::filesystem::exists(p))
		return false;
	for (auto &d : m_deps)
		d.get().beforeRead();
	auto last = std::filesystem::last_write_time(p);
	for (auto &d : m_deps)
		if (std::filesystem::last_write_time(d.get().getPath()) > last)
			return false;
	return true;
}

}
}