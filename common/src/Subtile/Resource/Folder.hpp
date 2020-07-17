#pragma once

#include "Element.hpp"
#include "util.hpp"

namespace Subtile {
namespace Resource {

class Folder : public Element
{
public:
	class Hidden;
	class Mod;
	class Shipper;
	friend Mod;
	friend Shipper;

	Folder(void);
	~Folder(void) override;

protected:
	struct is_root_t {};
	static inline constexpr is_root_t is_root{};
	Folder(is_root_t, const std::string &name);	// root folder
	Folder(const std::string &name);

	template <class ElementType, typename ...Args>
	auto& add(const std::string &name, Args &&...args)
	{
		auto &stack = getStack();

		stack.emplace(this, name);
		auto &res = addNoStack<ElementType>(name, std::forward<Args>(args)...);
		stack.pop();

		return res;
	}

	struct no_name_t {};
	static inline constexpr no_name_t no_name{};

	template <class ElementType, typename ...Args>
	auto& add(no_name_t, Args &&...args)
	{
		auto &stack = getStack();

		stack.emplace(this, "");
		auto &res = m_children.emplace<ElementType>(std::forward<Args>(args)...);
		stack.pop();

		return res;
	}

private:
	util::unique_set<Element> m_children;

	template <class ElementType, typename ...Args>
	auto& addNoStack(const std::string &name, Args &&...args)
	{
		if constexpr (ElementType::should_forward_name::value) {
			return m_children.emplace<ElementType>(name, std::forward<Args>(args)...);
		} else
			return m_children.emplace<ElementType>(std::forward<Args>(args)...);
	}

	void ship(const std::string &basedir) const override final;
};

class Folder::Mod
{
public:
	using no_name_t = typename Folder::no_name_t;
	static inline constexpr no_name_t no_name{};

	Mod(Folder &folder) :
		m_folder(folder)
	{
	}

	template <typename T, typename ...Args>
	decltype(auto) add(Args &&...args)
	{
		return m_folder.add<T>(std::forward<Args>(args)...);
	}

private:
	Folder &m_folder;
};

class Folder::Shipper
{
public:
	Shipper(Folder &folder) :
		m_folder(folder)
	{
	}

	template <typename ...Args>
	decltype(auto) ship(Args &&...args)
	{
		return m_folder.ship(std::forward<Args>(args)...);
	}

private:
	Folder &m_folder;
};

class Folder::Hidden : public Folder
{
public:
	Hidden(const std::string &name);
	~Hidden(void) override;

	using should_forward_name = std::true_type;
};

}
}