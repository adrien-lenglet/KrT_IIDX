#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>
#include <set>
#include "../Shader.hpp"
#include "util.hpp"
#include "util/string.hpp"

namespace Subtile {

class Shader::Compiler
{
	class token_stream
	{
	public:
		token_stream(const std::vector<std::string> &tokens) :
			m_tokens(tokens),
			m_ndx(0)
		{
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
	};

	using tstream = token_stream;

	static auto read(const std::string &path)
	{
		std::stringstream res;
		std::ifstream in(path, std::ios::binary);

		res << in.rdbuf();
		return res.str();
	}

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

	static void flush_buffer(std::string &buf, BufType buf_type, std::vector<std::string> &res)
	{
		if (buf.size() > 0 && buf_type != BufType::Whitespace)
			res.emplace_back(buf);
		buf.clear();
	}

	static auto tokenize(const std::string &str)
	{
		std::vector<std::string> res;

		std::string buf;
		BufType buf_type = BufType::Whitespace;
		for (auto c : str) {
			auto t = c_type(c);
			if (t != buf_type) {
				flush_buffer(buf, buf_type, res);
				buf_type = t;
			}
			buf.push_back(c);
		}
		flush_buffer(buf, buf_type, res);
		return res;
	}

	class Primitive
	{
	public:
		virtual ~Primitive(void) = default;

		class Collection : public util::unique_vector<Primitive>
		{
		public:
			template <typename ...Args>
			Collection(Args &&...args) :
				util::unique_vector<Primitive>(std::forward<Args>(args)...)
			{
			}

			void poll(tstream &s);
		};
	};

	class Section : public Primitive
	{
		using StageTable = std::map<std::string, Shader::Stage>;

		static auto& stageTable(void)
		{
			static const StageTable table {
				{"tesselation", Shader::Stage::Tesselation},
				{"geometry", Shader::Stage::Geometry},
				{"vertex", Shader::Stage::Vertex},
				{"fragment", Shader::Stage::Fragment}
			};

			return table;
		}

	public:
		Section(tstream &s) :
			m_stage(getStage(s))
		{
			while (!poll_end(s))
				m_primitives.poll(s);
		}

		static bool isComingUp(tstream &s)
		{
			if (s.peek() == "{")
				return true;
			if (s.tokens_left() >= 2) {
				auto [first, second] = s.peek2();
				return (stageTable().find(first) != stageTable().end()) && (second == "{");
			}
			return false;
		}

	private:
		std::optional<Shader::Stage> m_stage;
		Primitive::Collection m_primitives;

		std::optional<Shader::Stage> getStage(tstream &s)
		{
			auto [first, second] = s.peek2();

			if (first == "{") {
				s.poll();
				return std::nullopt;
			} else {
				auto name = s.poll();
				s.poll();
				return stageTable().at(name);
			}
		}

		bool poll_end(tstream &s)
		{
			auto &p = s.peek();

			if (p == "}") {
				s.poll();
				return true;
			} else
				return false;
		}
	};

	class Variable : public Primitive
	{
		enum class Storage {
			Const,
			Material,
			Object
		};

		using StorageTable = std::map<std::string, Storage>;

		static auto& storageTable(void)
		{
			static const StorageTable table {
				{"const", Storage::Const},
				{"material", Storage::Material},
				{"object", Storage::Object}
			};

			return table;
		}

	public:
		Variable(tstream &s) :
			m_storage(storageTable().find(s.poll())->second),
			m_type(s.poll()),
			m_id(s.poll()),
			m_array(getArray(s)),
			m_value(getValue(s))
		{
			s.expect(";");
		}

		static bool isComingUp(tstream &s)
		{
			return storageTable().find(s.peek()) != storageTable().end();
		}

	private:
		Storage m_storage;
		std::string m_type;
		std::string m_id;
		std::optional<size_t> m_array;
		std::optional<std::vector<std::string>> m_value;

		std::optional<size_t> getArray(tstream &s)
		{
			if (s.peek() == "[") {
				s.poll();
				auto res = util::stot(std::stoull, s.poll());
				s.expect("]");
				return res;
			} else
				return std::nullopt;
		}

		std::optional<std::vector<std::string>> getValue(tstream &s)
		{
			if (s.peek() == "=") {
				std::vector<std::string> res;

				while (s.peek() != ";")
					res.emplace_back(s.poll());
				return res;
			} else
				return std::nullopt;
		}
	};

	class Function : public Primitive
	{
	public:
		Function(tstream &s) :
			m_tokens(getTokens(s))
		{
		}

	private:
		std::vector<std::string> m_tokens;

		std::vector<std::string> getTokens(tstream &s)
		{
			std::vector<std::string> res;

			while (true) {
				auto &cur = s.poll();
				res.emplace_back(cur);
				if (cur == "{")
					break;
			}
			size_t lev = 1;
			while (lev > 0) {
				auto &cur = s.poll();
				res.emplace_back(cur);
				if (cur == "{")
					lev++;
				else if (cur == "}")
					lev--;
			}
			return res;
		}
	};

public:	
	Compiler(const std::string &path);
};

inline void Shader::Compiler::Primitive::Collection::poll(tstream &s)
{
	if (s.peek() == ";") {
		s.poll();
		return;
	}
	if (Section::isComingUp(s))
		emplace<Section>(s);
	else if (Variable::isComingUp(s))
		emplace<Variable>(s);
	else
		emplace<Function>(s);
}

inline Shader::Compiler::Compiler(const std::string &path)
{
	auto stream = token_stream(tokenize(read(path)));

	Primitive::Collection collec;
	while (stream.any_buf())
		collec.poll(stream);
}

}