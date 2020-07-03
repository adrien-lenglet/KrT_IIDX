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
#include "util/sstream.hpp"

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

			auto sep = "";
			bool new_lined = false;
			for (auto &t : m_tokens) {
				if (t == "{") {
					o << endl;
					write_tabs(o, indent);
					o << t << endl;
					new_lined = false;
					sep = "";
					indent++;
				} else if (t == "}") {
					indent--;
					write_tabs(o, indent);
					o << t << endl;
					new_lined = false;
					sep = "";
				} else if (t == ";") {
					o << t << endl;
					new_lined = false;
					sep = "";
				} else {
					if (!new_lined) {
						write_tabs(o, indent);
						new_lined = true;
					}
					o << sep << t;
					sep = " ";
				}
			}
		}

	private:
		std::vector<std::string> m_tokens;

		static void write_tabs(std::ostream &o, size_t n)
		{
			for (size_t i = 0; i < n; i++)
				o << "\t";
		}
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
		static const std::set<std::string> ops = {
			"(", ")", ";", "{", "}"
		};

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
			if ((buf_type == BufType::Operator) && (ops.find(buf) != ops.end()))
				flush_buffer(buf, buf_type, res);
		}
		flush_buffer(buf, buf_type, res);
		return res;
	}

	class Stages;
	class Stage;

	class Primitive
	{
	public:
		virtual ~Primitive(void) = default;

		virtual void write(token_output &o, Sbi sbi) const = 0;

		class Collection : public util::unique_vector<Primitive>
		{
		public:
			template <typename ...Args>
			Collection(Args &&...args) :
				util::unique_vector<Primitive>(std::forward<Args>(args)...)
			{
			}

			std::optional<std::reference_wrapper<Shader::Compiler::Primitive>> poll(tstream &s, Stages &stages);
			void dispatch(Stage *stage = nullptr);
			void recurAdd(Primitive &prim);
		};
	};

	class Stage
	{
	public:
		Stage(void)
		{
		}

		void add(Primitive &prim)
		{
			m_primitives.emplace_back(prim);
		}

		void write(token_output &o, Sbi sbi) const
		{
			for (auto &p : m_primitives)
				p.get().write(o, sbi);
		}

	private:
		std::vector<std::reference_wrapper<Primitive>> m_primitives;
	};

	class Stages : public std::map<Shader::Stage, Stage>
	{
	public:
		Stages(void)
		{
		}

		void add(Shader::Stage stage, Primitive &prim)
		{
			(*this)[stage].add(prim);
		}
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
		Section(tstream &s, Stages &stages) :
			m_stage(getStage(s, stages))
		{
			while (!poll_end(s))
				m_primitives.poll(s, stages);
			m_primitives.dispatch(m_stage);
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

		void recurAdd(Primitive &prim)
		{
			m_primitives.recurAdd(prim);
			if (m_stage)
				m_stage->add(prim);
		}

		void write(token_output &o, Sbi sbi) const override
		{
			for (auto &p : m_primitives)
				p.write(o, sbi);
		}

	private:
		Stage *m_stage;
		Primitive::Collection m_primitives;

		Stage* getStage(tstream &s, Stages &stages)
		{
			auto [first, second] = s.peek2();

			if (first == "{") {
				s.poll();
				return nullptr;
			} else {
				auto name = s.poll();
				s.poll();
				return &stages[stageTable().at(name)];
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

		void write(token_output &o, Sbi sbi) const override
		{
			if (sbi == Sbi::Vulkan) {
				write_vulkan(o);
			} else
				throw std::runtime_error("Can't output variable for such interface");
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
				s.poll();

				std::vector<std::string> res;

				while (s.peek() != ";")
					res.emplace_back(s.poll());
				return res;
			} else
				return std::nullopt;
		}

		void write_vulkan(token_output &o) const
		{
			static const std::map<Storage, size_t> storage_to_set {
				{Storage::Material, 0},
				{Storage::Object, 1}
			};

			if (m_storage == Storage::Const)
				o << "const";
			else
				o << "layout" << "(" << "set" << "=" << (storage_to_set.at(m_storage)) << "," << "binding" << "=" << 0 << ")" << "uniform";
			o << m_type << m_id;
			if (m_array)
				o << "[" << *m_array << "]";
			if (m_value) {
				o << "=";
				for (auto &v : *m_value)
					o << v;
			}
			o << ";";
		}
	};

	class Function : public Primitive
	{
	public:
		Function(tstream &s) :
			m_tokens(getTokens(s))
		{
		}

		void write(token_output &o, Sbi) const override
		{
			for (auto &t : m_tokens)
				o << t;
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

private:
	Stages m_stages;
};

inline std::optional<std::reference_wrapper<Shader::Compiler::Primitive>> Shader::Compiler::Primitive::Collection::poll(tstream &s, Stages &stages)
{
	if (s.peek() == ";") {
		s.poll();
		return std::nullopt;
	}
	if (Section::isComingUp(s))
		return emplace<Section>(s, stages);
	else if (Variable::isComingUp(s))
		return emplace<Variable>(s);
	else
		return emplace<Function>(s);
}

inline void Shader::Compiler::Primitive::Collection::dispatch(Shader::Compiler::Stage *stage)
{
	for (auto &p : *this) {
		if (!dynamic_cast<Section*>(&p)) {
			recurAdd(p);
			if (stage)
				stage->add(p);
		}
	}
}

inline void Shader::Compiler::Primitive::Collection::recurAdd(Primitive &prim)
{
	for (auto &p : *this) {
		auto sec = dynamic_cast<Section*>(&p);
		if (sec)
			sec->recurAdd(prim);
	}
}

inline Shader::Compiler::Compiler(const std::string &path)
{
	auto stream = token_stream(tokenize(read(path)));

	Primitive::Collection collec;
	while (stream.any_buf())
		collec.poll(stream, m_stages);
	collec.dispatch();

	std::cout << "STAGES:" << std::endl;
	for (auto &s : m_stages) {
		std::cout << static_cast<std::underlying_type_t<decltype(s.first)>>(s.first) << std::endl;
		token_output o;
		s.second.write(o, Sbi::Vulkan);
		o.write(std::cout);
		std::cout << std::endl;
	}
}

}