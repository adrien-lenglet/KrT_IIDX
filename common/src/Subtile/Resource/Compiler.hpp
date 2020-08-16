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

static auto read(const std::string &path)
{
	std::stringstream res;
	std::ifstream in(path, std::ios::binary);

	res << in.rdbuf();
	if (!in.good())
		throw std::runtime_error(std::string("Can't read shader '") + path + std::string("'"));
	return res.str();
}

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
		m_id(strip_name(path.stem().string())),
		m_res_path(computeResPath()),
		m_res_value(computeResValue())
	{
	}

	auto& getPath(void) const
	{
		return m_path;
	}

	auto& getResPath(void) const
	{
		return m_res_path;
	}

	auto& getResValue(void) const
	{
		return m_res_value;
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

	const modules_entry& resolve_scope_expr(const std::vector<std::string> &exprs) const
	{
		std::string expr;
		bool first = true;
		for (auto &e : exprs) {
			if (first)
				first = false;
			else
				expr.push_back(' ');
			for (auto &c : e)
				expr.push_back(c);
		}
		size_t i = 0;

		if (exprs.size() == 0)
			throw std::runtime_error("Expected expression for scope resolution");

		const modules_entry *res = nullptr;
		if (exprs.at(i) == "::") {
			i++;
			res = this;
			while (res->m_parent)
				res = res->m_parent;
			if (i >= exprs.size()) {
				std::stringstream ss;
				ss << "Expression '" << expr << "': expected token after beginning ::";
				throw std::runtime_error(ss.str());
			}
			if (exprs.at(i) != res->m_id) {
				std::stringstream ss;
				ss << "Expression '" << expr << "': expected '" << res->m_id << "' after beginning ::, but got '" << exprs.at(i) << "'";
				throw std::runtime_error(ss.str());
			}
			i++;
		} else {
			res = resolve(exprs.at(i));
			if (res == nullptr) {
				std::stringstream ss;
				ss << "Expression '" << expr << "': Can't resolve '" << exprs.at(i) << "' from '" << getPath().string() << "'";
				throw std::runtime_error(ss.str());
			}
			i++;
		}

		while (i < exprs.size()) {
			if (exprs.at(i) != "::") {
				std::stringstream ss;
				ss << "Expression '" << expr << "': expected :: after '" << exprs.at(i - 1) << "'";
				throw std::runtime_error(ss.str());
			}
			i++;
			auto &former_dir = *res;
			res = former_dir.resolve_in_dir(exprs.at(i));
			if (res == nullptr) {
				std::stringstream ss;
				ss << "Expression '" << expr << "': Can't resolve '" << exprs.at(i) << "' from '" << former_dir.m_path.string() << "'";
				throw std::runtime_error(ss.str());
			}
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
	std::string m_res_path;
	std::string m_res_value;
	std::set<std::string> m_children_ids;
	std::vector<modules_entry> m_children;

	std::string computeResPath(void) const
	{
		static const std::string scp("::");
		static const std::string cl("_class");

		auto res = m_id + cl;
		if (m_parent)
			res = m_parent->computeResPath() + scp + res;
		return res;
	}

	std::string computeResValue(void) const
	{
		static const std::string scp(".");
		static const std::string cl("()");

		auto res = m_id;
		if (m_parent)
			res = m_parent->computeResValue() + scp + res + cl;
		return res;
	}
};

enum class BufType {
	Whitespace,
	Id,
	Operator
};

static char lower_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;
	else
		return c;
}

static BufType c_type(char c)
{
	static const std::set<char> whitespace = {' ', '\n', '\t', '\r'};

	if (whitespace.find(c) != whitespace.end())
		return BufType::Whitespace;
	auto lower = lower_char(c);
	if (c == '_' || (lower >= 'a' && lower <= 'z') || (lower >= '0' && lower <= '9'))
		return BufType::Id;
	else
		return BufType::Operator;
}

class token_stream
{
public:
	token_stream(const std::vector<std::string> &tokens, bool add_enclosing_braces = false) :
		m_tokens(tokens),
		m_ndx(0)
	{
		if (add_enclosing_braces) {
			m_tokens.emplace(m_tokens.begin(), "{");
			m_tokens.emplace_back("}");
		}
	}

	auto& peek(void) const
	{
		return m_tokens.at(m_ndx);
	}

	auto peek2(void) const
	{
		return std::pair<const std::string&, const std::string&>(m_tokens.at(m_ndx), m_tokens.at(m_ndx + 1));
	}

	auto& poll(void)
	{
		auto &res = peek();

		m_ndx++;
		return res;
	}

	auto any_buf(void) const
	{
		return m_ndx < m_tokens.size();
	}

	auto is_end(void) const
	{
		return !any_buf();
	}

	size_t tokens_left(void) const
	{
		return m_tokens.size() - m_ndx;
	}

	void expect(const std::string &token)
	{
		auto got = poll();
		if (got != token)
			throw std::runtime_error(std::string("Expected '") + token + std::string("', but got '") + got + std::string("'"));
	}

private:
	std::vector<std::string> m_tokens;
	size_t m_ndx;

	static void flush_buffer(std::string &buf, BufType buf_type, std::vector<std::string> &res)
	{
		if (buf.size() > 0 && buf_type != BufType::Whitespace)
			res.emplace_back(buf);
		buf.clear();
	}

public:
	static auto tokenize(const std::string &str, bool add_enclosing_braces = false)
	{
		static const std::set<std::string> tops = {
			">>=", "<<="
		};
		static const std::set<std::string> sops = {
			"::", "+=", "-=", "++", "--", "/=", "*=", "%=", ">>", "<<", "&&", "||", "==", ">=", "<="
		};
		static const std::set<std::string> fops = {
			"(", ")", ",", ";", ":", "{", "}", "[", "]", "+", "-", "/", "*", "%", "=", "^", "|", "&", "~", "!", "?", ">", "<", "."
		};

		std::vector<std::string> res;

		std::string buf;
		BufType buf_type = BufType::Whitespace;
		size_t next_i = 0;
		bool is_sl_comment = false;
		bool is_comment = false;
		size_t delay = 0;
		for (auto c : str) {
			size_t i = next_i++;

			if (delay > 0) {
				delay--;
				continue;
			}

			std::optional<char> next;
			if (next_i < str.size())
				next = str.at(next_i);

			if (is_sl_comment) {
				if (c == '\n') {
					is_sl_comment = false;
					continue;
				}
			}
			if (is_comment) {
				if (c == '*' && next == '/') {
					is_comment = false;
					delay = 1;
					continue;
				}
			}

			if (c == '/' && next == '/') {
				flush_buffer(buf, buf_type, res);
				is_sl_comment = true;
			}
			if (c == '/' && next == '*') {
				flush_buffer(buf, buf_type, res);
				is_comment = true;
			}

			if (is_sl_comment || is_comment)
				continue;

			std::string sub = str.substr(i, 3);
			if (tops.find(sub) != tops.end()) {
				flush_buffer(buf, buf_type, res);
				buf_type = BufType::Operator;
				res.push_back(sub);
				delay = 2;
				continue;
			}
			sub = str.substr(i, 2);
			if (sops.find(sub) != sops.end()) {
				flush_buffer(buf, buf_type, res);
				buf_type = BufType::Operator;
				res.push_back(sub);
				delay = 1;
				continue;
			}
			sub = str.substr(i, 1);
			if (fops.find(sub) != fops.end()) {
				flush_buffer(buf, buf_type, res);
				buf_type = BufType::Operator;
				res.push_back(sub);
				continue;
			}

			auto t = c_type(c);
			if (t != buf_type) {
				flush_buffer(buf, buf_type, res);
				buf_type = t;
			}
			buf.push_back(c);
		}
		flush_buffer(buf, buf_type, res);
		return token_stream(res, add_enclosing_braces);
	}
};

class token_output
{
public:
	token_output(void)
	{
	}

	template <typename S>
	auto& operator<<(S &&str)
	{
		if constexpr (std::is_same_v<std::string, std::remove_cv_t<std::remove_reference_t<S>>>)
			m_tokens.emplace_back(str);
		else
			m_tokens.emplace_back(util::sstream_str(std::forward<S>(str)));
		return *this;
	}

	void write(std::ostream &o) const
	{
		size_t indent = 0;
		auto endl = "\n";

		auto prev_type = BufType::Whitespace;
		bool new_lined = false;
		for (auto &t : m_tokens) {
			if (t == "{") {
				o << endl;
				write_tabs(o, indent);
				o << t << endl;
				new_lined = false;
				prev_type = BufType::Whitespace;
				indent++;
			} else if (t == "}") {
				indent--;
				write_tabs(o, indent);
				o << t << endl;
				new_lined = false;
				prev_type = BufType::Whitespace;
			} else if (t == ";") {
				o << t << endl;
				new_lined = false;
				prev_type = BufType::Whitespace;
			} else {
				if (!new_lined) {
					write_tabs(o, indent);
					new_lined = true;
				}
				auto type = c_type(t.at(0));
				if (type == BufType::Id && prev_type == BufType::Id)
					o << " ";
				o << t;
				prev_type = type;
			}
		}
	}

	const auto& getTokens(void)
	{
		return m_tokens;
	}

private:
	std::vector<std::string> m_tokens;

	static void write_tabs(std::ostream &o, size_t n)
	{
		for (size_t i = 0; i < n; i++)
			o << "\t";
	}
};

}
}
}