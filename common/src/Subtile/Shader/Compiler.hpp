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
		token_stream(const std::vector<std::string> &tokens) :
			m_tokens(tokens),
			m_ndx(0)
		{
			m_tokens.emplace(m_tokens.begin(), "{");
			m_tokens.emplace_back("}");
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

	using tstream = token_stream;

	static auto read(const std::string &path)
	{
		std::stringstream res;
		std::ifstream in(path, std::ios::binary);

		res << in.rdbuf();
		return res.str();
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
	};

	class Variable;

	enum class Set {
		Material,
		Object
	};

	class SharedBlock
	{
	public:
		SharedBlock(Set set, size_t binding, const std::set<Shader::Stage> &stages) :
			m_set(set),
			m_binding(binding),
			m_stages(stages)
		{
		}

		void add(Variable &var)
		{
			m_variables.emplace_back(var);
		}

		auto& getStages(void) const
		{
			return m_stages;
		}

		void write(token_output &o, Sbi sbi) const
		{
			if (sbi == Sbi::Vulkan)
				write_vulkan(o);
			else
				throw std::runtime_error("Sbi not supported");
		}

		static std::string getSignature(Set set, size_t binding)
		{
			std::stringstream ss;

			ss << "___uni_s" << static_cast<std::underlying_type_t<decltype(set)>>(set) << "_b" << binding;
			return ss.str();
		}

		std::string getType(void) const
		{
			return getSignature(m_set, m_binding) + std::string("_t");
		}

		static std::string getVarName(Set set, size_t binding)
		{
			return getSignature(set, binding) + std::string("_v");
		}

		std::string getVarName(void) const
		{
			return getVarName(m_set, m_binding);
		}

		std::optional<std::string> substituate(const std::string &in) const
		{
			for (auto &v : m_variables) {
				auto &name = v.get().getName();
				if (name == in)
					return getVarName() + std::string(".") + name;
			}
			return std::nullopt;
		}

	private:
		Set m_set;
		size_t m_binding;
		std::set<Shader::Stage> m_stages;
		std::vector<std::reference_wrapper<Variable>> m_variables;

		void write_vulkan(token_output &o) const;
	};

	class DescriptorSet
	{
	public:
		DescriptorSet(Set set) :
			m_set(set),
			m_binding(0)
		{
		}

		auto& getBlocks(void)
		{
			return m_blocks;
		}

		SharedBlock& forStages(const std::set<Shader::Stage> &stages)
		{
			for (auto &b : m_blocks)
				if (b.getStages() == stages)
					return b;
			return m_blocks.emplace_back(m_set, m_binding++, stages);	
		}

	private:
		Set m_set;
		size_t m_binding;
		std::vector<SharedBlock> m_blocks;
	};

	class DescriptorSets : public std::map<Set, DescriptorSet>
	{
	public:
		DescriptorSets(void)
		{
		}

		SharedBlock& forStages(Set set, const std::set<Shader::Stage> &stages)
		{
			auto got = find(set);
			if (got == end()) {
				auto [it, succ] = emplace(set, set);
				got = it;
			}
			return got->second.forStages(stages);
		}
	};

	DescriptorSets m_blocks;

	std::vector<std::reference_wrapper<Variable>> m_variables;

public:
	void addVariable(Variable &variable)
	{
		m_variables.emplace_back(variable);
	}

private:
	class Stage
	{
	public:
		Stage(Shader::Stage stage) :
			m_stage(stage)
		{
		}

		void add(Primitive &prim)
		{
			m_primitives.emplace_back(prim);
		}

		void add(SharedBlock &block)
		{
			m_shared_blocks.emplace_back(block);
		}

		void write(token_output &o, Sbi sbi) const
		{
			for (auto &b : m_shared_blocks)
				b.get().write(o, sbi);
			token_output inter_o;
			for (auto &p : m_primitives)
				p.get().write(inter_o, sbi);
			for (auto &t : inter_o.getTokens()) {
				bool has_subs = false;
				for (auto &b : m_shared_blocks) {
					auto sub = b.get().substituate(t);
					if (sub) {
						o << *sub;
						has_subs = true;
						break;
					}
				}
				if (!has_subs)
					o << t;
			}
		}

		auto getStage(void)
		{
			return m_stage;
		}

	private:
		Shader::Stage m_stage;
		std::vector<std::reference_wrapper<SharedBlock>> m_shared_blocks;
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
			auto got = find(stage);
			if (got == end()) {
				auto [it, succ] = emplace(stage, stage);
				got = it;
			}
			got->second.add(prim);
		}
	};

	Stages m_stages;

public:
	auto& getStages(void)
	{
		return m_stages;
	}

private:
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
		Variable(tstream &s, Compiler &compiler) :
			m_storage(storageTable().find(s.poll())->second),
			m_type(s.poll()),
			m_id(s.poll()),
			m_array(getArray(s)),
			m_value(getValue(s))
		{
			s.expect(";");
			compiler.addVariable(*this);
		}

		static bool isComingUp(tstream &s)
		{
			return storageTable().find(s.peek()) != storageTable().end();
		}

		void declare(token_output &o) const
		{
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

		void write(token_output &o, Sbi sbi) const override
		{
			if (sbi == Sbi::Vulkan) {
				write_vulkan(o);
			} else
				throw std::runtime_error("Can't output variable for such interface");
		}

		bool isUniform(void) const
		{
			return m_storage == Storage::Material || m_storage == Storage::Object;
		}

		void addStage(Shader::Stage stage)
		{
			m_stages.emplace(stage);
		}

		const std::set<Shader::Stage>& getStages(void) const
		{
			return m_stages;
		}

		std::optional<Set> getSet(void) const
		{
			static const std::map<Storage, Set> table {
				{Storage::Material, Set::Material},
				{Storage::Object, Set::Object}
			};

			auto got = table.find(m_storage);
			if (got == table.end())
				return std::nullopt;
			else
				return got->second;
	
		}

		const std::string& getName(void) const
		{
			return m_id;
		}

	private:
		Storage m_storage;
		std::string m_type;
		std::string m_id;
		std::optional<size_t> m_array;
		std::optional<std::vector<std::string>> m_value;

		std::set<Shader::Stage> m_stages;

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
			declare(o);
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
		Section(tstream &s, Compiler &compiler) :
			m_compiler(compiler),
			m_stage(getStage(s))
		{
			while (!poll_end(s))
				poll(s, compiler);
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

		void write(token_output &o, Sbi sbi) const override
		{
			for (auto &p : m_primitives)
				p.write(o, sbi);
		}

		void poll(tstream &s, Compiler &compiler);

		void recurAdd(Primitive &prim)
		{
			if (m_stage) {
				auto var = dynamic_cast<Variable*>(&prim);
				if (var) {
					if (var->isUniform()) {
						var->addStage(m_stage->getStage());
					} else
						m_stage->add(prim);
				} else
					m_stage->add(prim);
			}
			for (auto &p : m_primitives) {
				auto s = dynamic_cast<Section*>(&p);
				if (s)
					s->recurAdd(prim);
			}
		}

		void dispatch(void)
		{
			for (auto &p : m_primitives) {
				auto s = dynamic_cast<Section*>(&p);
				if (s)
					s->dispatch();
				else
					recurAdd(p);
			}
		}

	private:
		Compiler &m_compiler;
		Stage *m_stage;
		util::unique_vector<Primitive> m_primitives;

		Stage* getStage(tstream &s)
		{
			auto [first, second] = s.peek2();

			if (first == "{") {
				s.poll();
				return nullptr;
			} else {
				auto name = s.poll();
				s.poll();
				auto stage = stageTable().at(name);
				auto &stages = m_compiler.getStages();
				auto got = stages.find(stage);
				if (got == stages.end()) {
					auto [it, suc] = stages.emplace(stage, stage);
					got = it;
				}
				return &got->second;
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
};

inline void Shader::Compiler::Section::poll(tstream &s, Compiler &compiler)
{
	if (s.peek() == ";") {
		s.poll();
		return;
	}
	if (Section::isComingUp(s))
		m_primitives.emplace<Section>(s, compiler);
	else if (Variable::isComingUp(s))
		m_primitives.emplace<Variable>(s, compiler);
	else
		m_primitives.emplace<Function>(s);
}

inline void Shader::Compiler::SharedBlock::write_vulkan(token_output &o) const
{
	static const std::map<Set, size_t> set_ndx_table {
		{Set::Material, 0},
		{Set::Object, 1}
	};

	o << "layout" << "(" << "std140" << "," << "set" << "=" << set_ndx_table.at(m_set) << "," << "binding" << "=" << m_binding << ")" << "uniform" << getType() << "{";
	for (auto &v : m_variables)
		v.get().declare(o);
	o << "}" << getVarName() << ";";
}

inline Shader::Compiler::Compiler(const std::string &path)
{
	auto stream = token_stream(tokenize(read(path)));

	Section collec(stream, *this);
	collec.dispatch();

	for (auto &v : m_variables) {
		auto var = v.get();
		auto set = var.getSet();
		if (set)
			m_blocks.forStages(*set, var.getStages()).add(v);
	}

	for (auto &pb : m_blocks)
		for (auto &b : pb.second.getBlocks())
			for (auto &s : b.getStages())
				m_stages.at(s).add(b);

	std::cout << "STAGES:" << std::endl;
	for (auto &s : m_stages) {
		std::cout << static_cast<std::underlying_type_t<decltype(s.first)>>(s.first) << std::endl;
		token_output o;
		s.second.write(o, Sbi::Vulkan);
		o.write(std::cout);
	}
}

}