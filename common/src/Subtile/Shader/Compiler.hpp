#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <set>
#include "../Shader.hpp"
#include "../Resource/Compiler.hpp"
#include "cpp_generator.hpp"
#include "util.hpp"
#include "util/string.hpp"
#include "util/sstream.hpp"

namespace Subtile {

class Shader::Compiler
{
public:
	using tstream = sb::rs::Compiler::token_stream;
	using token_output = sb::rs::Compiler::token_output;

private:
	class Stages;
public:
	class Stage;

private:
	class Primitive
	{
	public:
		virtual ~Primitive(void) = default;

		virtual void write(token_output &o, Sbi sbi) const = 0;
	};

public:
	class Variable;
	class Struct;

	class Function : public Primitive
	{
	public:
		Function(tstream &s) :
			m_proto_tokens(getProtoTokens(s)),
			m_tokens(getTokens(s))
		{
		}

		void write(token_output &o, Sbi) const override
		{
			o << m_return_type << m_name;
			for (auto &t : m_proto_tokens)
				o << t;
			for (auto &t : m_tokens)
				o << t;
		}

		auto& getName(void) const
		{
			return m_name;
		}

	private:
		std::string m_return_type;
		std::string m_name;
		std::vector<std::string> m_proto_tokens;
		std::vector<std::string> m_tokens;

		std::vector<std::string> getProtoTokens(tstream &s)
		{
			std::vector<std::string> res;

			m_return_type = s.poll();
			m_name = s.poll();
			s.expect("(");
			res.emplace_back("(");

			while (s.peek() != ")")
				res.emplace_back(s.poll());
			res.emplace_back(s.poll());

			return res;
		}

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

private:
	class Counter
	{
	public:
		Counter(void) :
			m_ndx(0)
		{
		}

		size_t next(void)
		{
			return m_ndx++;
		}

	private:
		size_t m_ndx;
	};

	static auto sbiIsGlsl(Sbi sbi)
	{
		static const std::set<Sbi> table {Sbi::Vulkan};

		return table.find(sbi) != table.end();
	}

	const sb::Resource::Compiler::modules_entry &m_entry;

public:
	auto& getModuleEntry(void) const
	{
		return m_entry;
	}

private:
	class DepSet
	{
	public:
		DepSet(void)
		{
		}

		bool isPresent(Compiler &dep)
		{
			auto &path = dep.getModuleEntry().getPath();
			return m_paths.find(path) != m_paths.end();
		}

		bool insert(Compiler &compiler)
		{
			auto &path = compiler.getModuleEntry().getPath();
			if (m_paths.find(path) != m_paths.end())
				return false;
			m_paths.emplace(path);
			m_deps.emplace_back(compiler);
			return true;
		}

		auto& getCompilers(void)
		{
			return m_deps;
		}
		auto& getCompilers(void) const
		{
			return m_deps;
		}

	private:
		std::set<std::fs::path> m_paths;
		std::vector<util::ref_wrapper<Compiler>> m_deps;
	};

	std::vector<util::ref_wrapper<Compiler>> m_read_deps;
	DepSet m_deps;
	DepSet m_all_deps;

	class Require;

public:
	auto& getDeps(void)
	{
		return m_deps;
	}

	auto& getAllDeps(void)
	{
		return m_all_deps;
	}

	void insertReadDep(Compiler &dep)
	{
		m_read_deps.emplace_back(dep);
		if (m_all_deps.insert(dep))
			for (auto &s : dep.getStructs())
				m_all_structs.emplace_back(s, dep.getModuleEntry().getResPath() + std::string("::Struct::") + s.getName());
	}

	auto& getForeignSet(Compiler &dep)
	{
		auto &path = dep.getModuleEntry().getPath();
		auto got = m_foreign_sets.find(path);
		if (got != m_foreign_sets.end())
			return got->second;
		else {
			auto [it, suc] = m_foreign_sets.emplace(std::piecewise_construct, std::forward_as_tuple(path), std::forward_as_tuple());
			if (!suc)
				throw std::runtime_error("Can't emplace foreign set");
			auto &res = it->second;
			for (auto &s : dep.m_sets)
				res.emplace_back(s, m_set_counter.next());
			return res;
		}
	}

	void addDep(Compiler &dep)
	{
		if (!m_deps.insert(dep))
			return;
		auto &sets = getForeignSet(dep);
		for (auto &set : sets)
			set.getStages() = set.getSet().getStages();
		for (auto &s : dep.getStages()) {
			for (auto &in : s.second.getInVariables())
				m_stages.at(s.first).addIn(in);
			for (auto &out : s.second.getOutVariables())
				m_stages.at(s.first).addOut(out);
		}
	}

	void insertDep(Compiler &dep)
	{
		for (auto &d : dep.getDeps().getCompilers())
			addDep(d);
		addDep(dep);
	}

	void addDepOnStage(Compiler &dep, Shader::Stage stage)
	{
		auto &foreign = getForeignSet(dep);
		auto &s = m_stages.at(stage);
		if (!s.getDeps().insert(dep))
			return;
		for (auto &set : foreign)
			set.getStages().emplace(stage);
		addStagePureIOs(dep, s);
	}

	void insertDepFromStage(Compiler &dep, Shader::Stage stage)
	{
		if (dep.isPureModule()) {
			for (auto &d : dep.getDeps().getCompilers())
				addDepOnStage(d, stage);
			addDepOnStage(dep, stage);
		} else
			insertDep(dep);
	}

	void prModuleWrite(token_output &o, Sbi sbi) const
	{
		m_collec.write_no_set(o, sbi);
	}

	void writeDepsFor(token_output &o, Sbi sbi, sb::Shader::Stage stage) const
	{
		for (auto &d : m_stages.at(stage).getDeps().getCompilers()) {
			for (auto &set : m_foreign_sets.at(d.get().getModuleEntry().getPath())) {
				auto &stages = set.getStages();
				if (stages.find(stage) != stages.end())
					set.write(o, sbi);
			}
			d.get().prModuleWrite(o, sbi);
		}
		for (auto &d : m_deps.getCompilers()) {
			for (auto &set : m_foreign_sets.at(d.get().getModuleEntry().getPath())) {
				auto &stages = set.getStages();
				if (stages.find(stage) != stages.end())
					set.write(o, sbi);
			}
			auto got = d.get().getStages().find(stage);
			if (got == d.get().getStages().end())
				return;
			for (auto &p : got->second.getPrimitives())
				p.get().write(o, sbi);
		}
	}

private:
	Counter m_set_counter;

public:
	auto gen_set_ndx(void)
	{
		return m_set_counter.next();
	}

	class Set;
	class ForeignSet;

private:
	std::map<std::fs::path, std::vector<ForeignSet>> m_foreign_sets;
	std::vector<util::ref_wrapper<Set>> m_sets;

	util::unique_vector<Struct> m_structs;

	struct FinalStruct
	{
		FinalStruct(Struct &str, const std::string &type_path) :
			str(str),
			type_path(type_path)
		{
		}

		Struct &str;
		std::string type_path;
	};

	std::vector<FinalStruct> m_all_structs;

public:
	template <typename ...Args>
	void addStruct(Args &&...args)
	{
		m_structs.emplace(std::forward<Args>(args)...);
	}

	util::unique_vector<Struct>& getStructs(void)
	{
		return m_structs;
	}
	auto& getAllStructs(void)
	{
		return m_all_structs;
	}

	auto& getSets(void)
	{
		return m_sets;
	}

	auto& getForeignSets(void)
	{
		return m_foreign_sets;
	}

	void addSet(Set &set)
	{
		m_sets.emplace_back(set);
	}

	class Stage
	{
	public:
		class InterfaceInOut
		{
		public:
			enum class Dir {
				In,
				Out
			};

			InterfaceInOut(Variable &var, Dir dir, size_t loc, bool is_array = false) :
				m_var(var),
				m_dir(dir),
				m_loc(loc),
				m_is_array(is_array)
			{
			}

			void write(token_output &o) const
			{
				static const std::map<Dir, std::string> io_table {
					{Dir::In, "in"},
					{Dir::Out, "out"}
				};
				static const std::map<Dir, const char*> io_prefix_table {
					{Dir::In, "in_"},
					{Dir::Out, "out_"}
				};

				o << "layout" << "(" << "location" << "=" << m_loc << ")" << io_table.at(m_dir);
				m_var.declare(o, io_prefix_table.at(m_dir), m_is_array);
			}

			auto& getVariable(void) const
			{
				return m_var;
			}

			auto getDir(void) const
			{
				return m_dir;
			}

			auto getLocation(void) const
			{
				return m_loc;
			}

		private:
			Variable &m_var;
			Dir m_dir;
			size_t m_loc;
			bool m_is_array;
		};

		Stage(Compiler &compiler, Shader::Stage stage) :
			m_compiler(compiler),
			m_stage(stage),
			m_is_complete(false)
		{
		}

		void add(Primitive &prim)
		{
			auto var = dynamic_cast<Variable*>(&prim);
			if (var) {
				var->addToStage(*this);
			} else {
				auto set = dynamic_cast<Set*>(&prim);
				if (set) {
					set->addToStage(*this);
					m_sets.emplace_back(*set);
				} else {
					auto func = dynamic_cast<Function*>(&prim);
					if (func) {
						if (func->getName() == "main")
							m_is_complete = true;
						m_primitives.emplace_back(*func);
					} else {
						if (tryAddRequire(prim));
						else
							m_primitives.emplace_back(prim);
					}
				}
			}
		}

		void emplacePrim(Primitive &prim)
		{
			m_primitives.emplace_back(prim);
		}

		void addIn(Variable &var)
		{
			m_in_variables.emplace_back(var);
		}
		void addOut(Variable &var)
		{
			m_out_variables.emplace_back(var);
		}

		static std::vector<std::reference_wrapper<Variable>>& getEmptyVariables(void)
		{
			static std::vector<std::reference_wrapper<Variable>> res;

			return res;
		}

		std::vector<std::reference_wrapper<Variable>>& getInVariables(void)
		{
			if (m_compiler.getStages().size() > 0) {
				if (m_compiler.getStages().begin()->first == m_stage) {
					return getEmptyVariables();
				}
			}

			if (m_stage == sb::Shader::Stage::Fragment)
				return getEmptyVariables();

			return m_in_variables;
		}

		std::vector<std::reference_wrapper<Variable>>& getOutVariables(void)
		{
			if (m_stage == sb::Shader::Stage::Fragment)
				return getEmptyVariables();

			return m_out_variables;
		}

		auto& getRawInVariables(void) const
		{
			return m_in_variables;
		}

		auto& getRawOutVariables(void) const
		{
			return m_out_variables;
		}

		auto& getInterface(void) const
		{
			return m_interface_ios;
		}

		void done(void) // called when all primitives are in stages (build in / out blocks)
		{
			if (m_in_variables.size() > 0) {
				if (&m_compiler.getStages().begin()->second == this) {
					size_t loc = 0;
					for (auto &var : m_in_variables) {
						m_interface_ios.emplace_back(var, InterfaceInOut::Dir::In, loc);
						loc += var.get().getType().parse("nolayout").loc_size;
					}
				} else if (m_stage == Shader::Stage::Fragment) {
					throw std::runtime_error("Input attachment not handled yet");
				} else
					throw std::runtime_error("In variable must be declared only in the first stage of the pipeline");
			}

			size_t loc = 0;
			for (auto &var : m_out_variables) {
				m_interface_ios.emplace_back(var, InterfaceInOut::Dir::Out, loc);
				auto after = m_compiler.getStages().stageAfter(m_stage);
				if (after) {
					after->m_interface_ios.emplace_back(var, InterfaceInOut::Dir::In, loc, after->m_stage == sb::Shader::Stage::Geometry);
				}
				loc += var.get().getType().parse("nolayout").loc_size;
			}
		}

		void write(token_output &o, Sbi sbi) const
		{
			for (auto &s : m_compiler.getAllStructs())
				s.str.write(o);
			if (m_stage == sb::Shader::Stage::Geometry) {
				o << "layout" << "(" << "triangles" << ")" << "in" << ";";
				o << "layout" << "(" << "triangle_strip" << ", " << "max_vertices" << "=" << "32" << ")" << "out" << ";";

				/*o << "in gl_PerVertex" << "{";
				for (auto &io : m_interface_ios) {
					if (io.getDir() == InterfaceInOut::Dir::In)
						io.write(o);
				}
				o << "}" << "gl_vtx_in";
				for (auto &io : m_interface_ios) {
					if (io.getDir() == InterfaceInOut::Dir::Out)
						io.write(o);
				}*/
				for (auto &io : m_interface_ios)
					io.write(o);
			} else {
				for (auto &io : m_interface_ios)
					io.write(o);
			}
			token_output inter_o;

			m_compiler.writeDepsFor(o, sbi, m_stage);

			for (auto &s : m_sets)
				s.get().write(inter_o, sbi);
			for (auto &p : m_primitives)
				p.get().write(inter_o, sbi);
			std::string last_token;
			for (auto &t : inter_o.getTokens()) {
				bool has_subs = false;
				if (last_token != ".") {
					/*for (auto &b : m_compiler.getDescriptorSets()) {
						auto sub = b.get().getBlock().substituate(t, sbi);
						if (sub) {
							o << *sub;
							has_subs = true;
							break;
						}
					}*/
				}
				if (!has_subs)
					o << t;
				last_token = t;
			}
		}

		void write(std::ostream &o, Sbi sbi) const
		{
			token_output toks;
			o << "#version 450\n";
			write(toks, sbi);
			toks.write(o);
		}

		auto getStage(void)
		{
			return m_stage;
		}

		auto isComplete(void) const
		{
			return m_is_complete;
		}

		DepSet& getDeps(void)
		{
			return m_deps;
		}
		const DepSet& getDeps(void) const
		{
			return m_deps;
		}

		const std::vector<std::reference_wrapper<Primitive>>& getPrimitives(void) const
		{
			return m_primitives;
		}

	private:
		Compiler &m_compiler;
		Shader::Stage m_stage;
		bool m_is_complete;

		DepSet m_deps;
		std::vector<util::ref_wrapper<Set>> m_sets;
		std::vector<std::reference_wrapper<Primitive>> m_primitives;
		std::vector<std::reference_wrapper<Variable>> m_in_variables;
		std::vector<std::reference_wrapper<Variable>> m_out_variables;

		std::vector<InterfaceInOut> m_interface_ios;

		bool tryAddRequire(Primitive &prim);
	};

private:
	class Stages : public std::map<Shader::Stage, Stage>
	{
	public:
		Stages(Compiler &compiler) :
			m_compiler(compiler)
		{
		}

		void add(Shader::Stage stage, Primitive &prim)
		{
			auto got = find(stage);
			if (got == end()) {
				auto [it, succ] = emplace(std::piecewise_construct, std::forward_as_tuple(stage), std::forward_as_tuple(m_compiler, stage));
				got = it;
			}
			got->second.add(prim);
		}

		auto getSet(void) const
		{
			std::set<Shader::Stage> res;

			for (auto &p : *this)
				res.emplace(p.first);
			return res;
		}

		Stage* stageAfter(Shader::Stage stage)
		{
			auto got = find(stage);
			if (got == end())
				throw std::runtime_error("Base stage not found for neighbor search");
			++got;
			if (got == end())
				return nullptr;
			else
				return &got->second;
		}

	private:
		Compiler &m_compiler;
	};

	Stages m_stages;

public:
	Stages& getStages(void)
	{
		return m_stages;
	}

	class Type
	{
		static std::vector<size_t> parseArray(tstream &s)
		{
			std::vector<size_t> res;

			while (s.peek() == "[") {
				s.poll();
				res.emplace_back(util::stot(std::stoull, s.poll()));
				s.expect("]");
			}
			return res;
		}

	public:
		struct Parsed {
			Parsed(const std::string &name, bool is_opaque = false, bool is_user_defined = false) :
				name(name),
				is_user_defined(is_user_defined),
				is_opaque(is_opaque)
			{
			}

			std::string name;
			bool is_user_defined;
			std::string user_defined_type;
			bool is_opaque;

			size_t salign = 0;
			size_t balign = 0;
			size_t ealign = 0;
			size_t loc_size = 0;

			size_t bsize = 0;
			size_t esize = 0;

			void set_all_sizes(size_t size)
			{
				bsize = size;
				esize = size;
			}

			void spec_array(const std::vector<size_t> &array, const std::string &layout)
			{
				if (array.size() == 0)
					return;

				for (auto it = array.crbegin(); it != array.crend(); it++) {
					auto &a = *it;
					std::stringstream ss;
					ss << typePrefix("Array") << "<" << name << ", " << a << ", " << layout << ">";
					name = ss.str();
				}
				size_t els = 1;
				for (auto &a : array)
					els *= a;
				loc_size *= els;
				ealign = util::align_dyn(ealign, 16);
				bsize *= els;
				esize *= els;
			}
		};

		Type(Compiler &compiler, tstream &s) :
			m_compiler(compiler),
			m_name(s.poll()),
			m_base_array(parseArray(s)),
			m_array(m_base_array)
		{
		}

		struct build_comma_t {};
		static inline constexpr build_comma_t build_comma {};

		Type(build_comma_t, const Type &other) :
			m_compiler(other.m_compiler),
			m_name(other.m_name),
			m_base_array(other.m_base_array),
			m_array(m_base_array)
		{
		}

		auto& getName(void) const
		{
			return m_name;
		}

		auto& getArray(void) const
		{
			return m_array;
		}

		auto getArrayElems(void) const
		{
			size_t res = 1;
			for (auto &a : m_array)
				res *= a;
			return res;
		}

		void extend(tstream &s)
		{
			auto array = parseArray(s);

			for (auto &e : m_array)
				array.emplace_back(e);
			m_array = array;
		}

		void write(token_output &o) const
		{
			o << m_name;
			for (auto &a : m_array)
				o << "[" << a << "]";
		}

		enum class Layout
		{
			Std140,
			Std430,
			Irrelevant = Std140
		};

		static std::string layoutToType(Layout layout)
		{
			static const std::map<Layout, std::string> table {
				{Layout::Std140, "Std140"},
				{Layout::Std430, "Std430"}
			};

			return typePrefix(table.at(layout));
		}

		Parsed parse(const std::string &layout) const
		{
			auto nopq = parseNOpq(layout);
			if (nopq)
				return *nopq;
			auto opq = parseOpq();
			if (opq)
				return Parsed(*opq, true);
			for (auto &as : m_compiler.getAllStructs()) {
				auto &s = as.str;
				if (s.getName() == m_name) {
					Parsed res(m_name, false, true);
					res.user_defined_type = as.type_path;

					res.salign = s.getSalign();
					res.balign = s.getBalign();
					res.ealign = s.getEalign();
					res.loc_size = s.getLocSize();
					res.bsize = s.getBsize();
					res.esize = s.getEsize();
					return res;
				}
			}
			throw std::runtime_error(std::string("Unknown type '") + m_name + std::string("'"));
		}

	private:
		Compiler &m_compiler;
		std::string m_name;
		std::vector<size_t> m_base_array;
		std::vector<size_t> m_array;

		static std::string typePrefix(const std::string &name)
		{
			static const std::string add("sb::Shader::Type::");

			return add + name;
		}

		static bool is_vec_num(char num)
		{
			static const std::set<char> table {
				'2', '3', '4'
			};

			return table.find(num) != table.end();
		}

		class Scalar
		{
		public:
			Scalar(const std::string &name, size_t size) :
				name(name),
				size(size)
			{
			}

			const std::string name;
			const size_t size;
		};

		static auto& Bool(void)
		{
			static const Scalar res("Bool", sizeof(sb::Shader::Type::Bool));
			return res;
		}
		static auto& Int(void)
		{
			static const Scalar res("Int", sizeof(sb::Shader::Type::Int));
			return res;
		}
		static auto& Uint(void)
		{
			static const Scalar res("Uint", sizeof(sb::Shader::Type::Uint));
			return res;
		}
		static auto& Float(void)
		{
			static const Scalar res("Float", sizeof(sb::Shader::Type::Float));
			return res;
		}
		static auto& Double(void)
		{
			static const Scalar res("Double", sizeof(sb::Shader::Type::Double));
			return res;
		}

		static Parsed contructVec(const Scalar &base, size_t size)
		{
			std::stringstream ss;

			ss << typePrefix("Vec") << "<" << typePrefix(base.name) << ", " << size << ">";

			Parsed res(ss.str());
			res.salign = base.size;
			res.balign = res.salign * (size == 2 ? 2 : 4);
			res.ealign = res.balign;
			res.loc_size = base.size == sizeof(double) && size > 2 ? 2 : 1;
			res.set_all_sizes(base.size * size);
			return res;
		}

		std::optional<Parsed> parseVec(void) const
		{
			static const std::string vecn("vecn");
			static const std::string tvecn("tvecn");
			static const std::map<char, Scalar> tvec_table {
				{'b', Bool()},
				{'i', Int()},
				{'u', Uint()},
				{'d', Double()}
			};

			if (m_name.size() == vecn.size()) {
				auto &num = m_name.at(3);
				if (m_name.substr(0, 3) == "vec" && is_vec_num(num))
					return contructVec(Float(), num - '0');
			}
			if (m_name.size() == tvecn.size()) {
				auto &num = m_name.at(4);
				auto got = tvec_table.find(m_name.at(0));
				if (got != tvec_table.end() && m_name.substr(1, 3) == "vec" && is_vec_num(num))
					return contructVec(got->second, num - '0');
			}
			return std::nullopt;
		}


		static Parsed constructMat(const Scalar &basetype, size_t c, size_t r, const std::string &layout)
		{
			std::stringstream ss;
			ss << typePrefix("Mat") << "<" << typePrefix(basetype.name) <<", " << c << ", " << r << ", " << layout << ">";

			auto vec = contructVec(basetype, c);
			Parsed res(ss.str());
			res.salign = vec.salign;
			res.balign = vec.balign;
			res.ealign = res.balign;
			res.bsize = res.balign * r;
			res.esize = res.ealign * r;
			return res;
		}

		std::optional<Parsed> try_construct_mat(const Scalar &basetype, const std::string &rest, const std::string &layout) const
		{
			if (rest.size() == 1) {
				auto num = rest.at(0);
				if (is_vec_num(num))
					return constructMat(basetype, num - '0', num - '0', layout);
			}
			if (rest.size() == 3) {
				auto c = rest.at(0);
				auto r = rest.at(2);
				if (rest.at(1) == 'x' && is_vec_num(c) && is_vec_num(r))
					return constructMat(basetype, c - '0', r - '0', layout);
			}
			return std::nullopt;
		}

		std::optional<Parsed> parseMat(const std::string &layout) const
		{
			static const std::string mat("mat");
			static const std::string dmat("dmat");

			if (m_name.substr(0, mat.size()) == mat) {
				auto got = try_construct_mat(Float(), m_name.substr(mat.size()), layout);
				if (got)
					return *got;
			}
			if (m_name.substr(0, dmat.size()) == dmat) {
				auto got = try_construct_mat(Double(), m_name.substr(dmat.size()), layout);
				if (got)
					return *got;
			}
			return std::nullopt;
		}

		std::optional<Parsed> parseNOpq(const std::string &layout) const
		{
			static const std::map<std::string, Scalar> scalars {
				{"bool", Bool()},
				{"int", Int()},
				{"uint", Uint()},
				{"float", Float()},
				{"double", Double()}
			};

			auto sgot = scalars.find(m_name);
			if (sgot != scalars.end()) {
				auto &scalar = sgot->second;
				Parsed res(typePrefix(sgot->second.name));
				res.salign = scalar.size;
				res.balign = res.salign;
				res.ealign = res.balign;
				res.loc_size = 1;
				res.set_all_sizes(scalar.size);
				res.spec_array(m_array, layout);
				return res;
			}
			auto vec = parseVec();
			if (vec) {
				vec->spec_array(m_array, layout);
				return *vec;
			}
			auto mat = parseMat(layout);
			if (mat) {
				mat->spec_array(m_array, layout);
				return *mat;
			}
			return std::nullopt;
		}

		//static std::map<std::string, s>

		std::optional<std::string> parseOpq(void) const
		{
			//static const std::map<std::string, std::string> sampler_table;
			//static const std::map<std::string, std::string> image_table = getImageTable("image");

			if (m_name == "atomic_uint")
				return typePrefix("AtomicUint");
			return std::nullopt;
		}
	};

	class Variable : public Primitive
	{
	public:
		enum class Storage {
			Inline,
			Const,
			In,
			Out
		};

	private:
		using StorageTable = std::map<std::string, Storage>;

		static auto& storageTable(void)
		{
			static const StorageTable table {
				{"const", Storage::Const},
				{"in", Storage::In},
				{"out", Storage::Out}
			};

			return table;
		}

		std::string getId(tstream &s)
		{
			auto res = s.poll();

			m_type.extend(s);
			return res;
		}

	public:
		Variable(Compiler &compiler, tstream &s, Storage storage) :
			m_compiler(compiler),
			m_storage(storage),
			m_type(compiler, s),
			m_id(getId(s)),
			m_value(getValue(s))
		{
		}

		Variable(Compiler &compiler, tstream &s) :
			Variable(compiler, s, storageTable().at(s.poll()))
		{
		}

		Variable(tstream &s, Variable &first) :
			m_compiler(first.m_compiler),
			m_storage(first.m_storage),
			m_type(Type::build_comma, first.m_type),
			m_id(getId(s)),
			m_value(getValue(s))
		{
		}

		static bool isComingUp(tstream &s)
		{
			return storageTable().find(s.peek()) != storageTable().end();
		}

		void declare(token_output &o, const char *id_prefix = nullptr, bool is_array = false) const
		{
			m_type.write(o);
			if (id_prefix)
				o << (std::string(id_prefix) + m_id);
			else
				o << m_id;
			if (is_array)
				o << "[" << "]";
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

		void addStage(Shader::Stage stage)
		{
			m_stages.emplace(stage);
		}

		void addToStage(Stage &stage)
		{
			if (m_storage == Storage::In) {
				stage.addIn(*this);
			} else if (m_storage == Storage::Out) {
				stage.addOut(*this);
			} else
				stage.emplacePrim(*this);
		}

		const std::set<Shader::Stage>& getStages(void) const
		{
			return m_stages;
		}

		const std::string& getName(void) const
		{
			return m_id;
		}

		const Type& getType(void) const
		{
			return m_type;
		}

		auto& getStorage(void) const
		{
			return m_storage;
		}

	private:
		Compiler &m_compiler;
		Storage m_storage;
		Type m_type;
		std::string m_id;
		std::optional<std::vector<std::string>> m_value;

		std::set<Shader::Stage> m_stages;

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
			/*static const std::map<Storage, size_t> storage_to_set {
				{Storage::Material, 0},
				{Storage::Object, 1}
			};*/

			if (m_storage == Storage::In || m_storage == Storage::Out)
				return;

			if (m_storage == Storage::Const)
				o << "const";
			/*else
				o << "layout" << "(" << "set" << "=" << (storage_to_set.at(m_storage)) << "," << "binding" << "=" << 0 << ")" << "uniform";*/
			declare(o);
		}
	};

	class Struct
	{
	public:
		Struct(tstream &s, Compiler &compiler) :
			m_compiler(compiler),
			m_name(getName(s)),
			m_variables(getVariables(s)),
			m_variables_parsed(getVariablesParsed()),
			m_salign(computeAlign(&Type::Parsed::salign)),
			m_balign(computeAlign(&Type::Parsed::balign)),
			m_ealign(util::align_dyn(computeAlign(&Type::Parsed::ealign), 16)),
			m_loc_size(computeLocSize()),
			m_bsize(computeSize(&Type::Parsed::bsize, &Type::Parsed::balign)),
			m_esize(computeSize(&Type::Parsed::esize, &Type::Parsed::ealign))
		{
			m_compiler.getAllStructs().emplace_back(*this, compiler.getModuleEntry().getResPath() + std::string("::Struct::") + getName());
			s.expect(";");
		}

		static bool isComingUp(tstream &s)
		{
			return s.peek() == "struct";
		}

		void write(token_output &o) const
		{
			o << "struct" << m_name << "{";
			for (auto &v : m_variables)
				v.declare(o);
			o << "}" << ";";
		}

		const std::string& getName(void) const
		{
			return m_name;
		}

		auto& getVariables(void) const
		{
			return m_variables;
		}

		size_t getSalign(void) const { return m_salign; }
		size_t getBalign(void) const { return m_balign; }
		size_t getEalign(void) const { return m_ealign; }
		size_t getLocSize(void) const { return m_loc_size; }
		size_t getBsize(void) const { return m_bsize; }
		size_t getEsize(void) const { return m_esize; }

	private:
		Compiler &m_compiler;
		std::string m_name;
		util::unique_vector<Variable> m_variables;
		std::vector<Type::Parsed> m_variables_parsed;
		size_t m_salign;
		size_t m_balign;
		size_t m_ealign;
		size_t m_loc_size;

		size_t m_bsize;
		size_t m_esize;

		std::string getName(tstream &s)
		{
			s.expect("struct");
			return s.poll();
		}

		util::unique_vector<Variable> getVariables(tstream &s)
		{
			util::unique_vector<Variable> res;

			s.expect("{");
			while (s.peek() != "}") {
				auto &first = res.emplace(m_compiler, s, Variable::Storage::Inline);
				while (s.peek() == ",") {
					s.poll();
					res.emplace(s, first);
				}
				s.expect(";");
			}
			s.poll();

			return res;
		}

		std::vector<Type::Parsed> getVariablesParsed(void)
		{
			std::vector<Type::Parsed> res;

			for (auto &v : m_variables)
				res.emplace_back(v.getType().parse("nolayout"));
			return res;
		}

		size_t computeAlign(size_t Type::Parsed::*resolver)
		{
			size_t res = 0;

			for (auto &p : m_variables_parsed)
				res = std::max(res, p.*resolver);
			return res;
		}

		size_t computeLocSize(void)
		{
			size_t res = 0;

			for (auto &p : m_variables_parsed)
				res += p.loc_size;
			return res;
		}

		size_t computeSize(size_t Type::Parsed::*size_resolver, size_t Type::Parsed::*align_resolver)
		{
			size_t res = 0;

			for (auto &p : m_variables_parsed) {
				auto size = p.*size_resolver;
				auto align = p.*align_resolver;
				res = util::align_dyn(res, align);
				res += size;
			}
			return res;
		}
	};

	class GlslMappedBlock
	{
	public:
		GlslMappedBlock(Set &set, size_t binding, const std::string &name) :
			m_set(set),
			m_binding(binding),
			m_name(name)
		{
		}

		void write(token_output &o, Sbi sbi, size_t set_ndx) const
		{
			if (sbi == Sbi::Vulkan)
				write_vulkan(o, set_ndx);
			else
				throw std::runtime_error("Sbi not supported");
		}

		void add(Variable &var)
		{
			m_variables.emplace_back(var);
		}

		auto getLayoutBinding(void) const
		{
			sb::Shader::DescriptorSet::Layout::DescriptionBinding res;

			res.binding = m_binding;
			res.descriptorCount = 0;
			res.descriptorType = sb::Shader::DescriptorType::UniformBuffer;
			res.stages = m_set.getStages();
			return res;
		}

	private:
		Set &m_set;
		size_t m_binding;
		const std::string &m_name;
		std::vector<std::reference_wrapper<Variable>> m_variables;

		void write_vulkan(token_output &o, size_t set_ndx) const
		{
			o << "layout" << "(" << "std140" << "," << "set" << "=" << set_ndx << "," << "binding" << "=" << m_binding << ")" << "uniform" << (std::string("_") + m_name + std::string("_t_")) << "{";
			for (auto &v : m_variables)
				v.get().declare(o);
			o << "}" << m_name << ";";
		}
	};

	class GlslOpaqueVar
	{
	public:
		GlslOpaqueVar(Set &set, size_t binding, Variable &variable) :
			m_set(set),
			m_binding(binding),
			m_variable(variable)
		{
		}

		void write(token_output &o, Sbi sbi, size_t set_ndx) const
		{
			if (sbi == Sbi::Vulkan)
				write_vulkan(o, set_ndx);
			else
				throw std::runtime_error("Sbi not supported");
		}

		auto getLayoutBinding(void) const
		{
			sb::Shader::DescriptorSet::Layout::DescriptionBinding res;

			res.binding = m_binding;
			res.descriptorCount = m_variable.getType().getArrayElems();
			res.descriptorType = sb::Shader::DescriptorType::CombinedImageSampler;
			res.stages = m_set.getStages();
			return res;
		}

	private:
		Set &m_set;
		size_t m_binding;
		Variable &m_variable;

		void write_vulkan(token_output &o, size_t set_ndx) const
		{
			o << "layout" << "(" << "std140" << "," << "set" << "=" << set_ndx << "," << "binding" << "=" << m_binding << ")" << "uniform";
			m_variable.declare(o);
		}
	};

	class Set : public Primitive
	{
	public:
		Set(tstream &s, Compiler &compiler) :
			m_compiler(compiler),
			m_set_ndx(compiler.gen_set_ndx()),
			m_name(getName(s)),
			m_is_all_stages(false),
			m_variables(getVariables(s, compiler))
		{
			s.expect(";");
			compiler.addSet(*this);
		}

		static bool isComingUp(tstream &s)
		{
			return s.peek() == "set";
		}

		size_t getNdx(void) const
		{
			return m_set_ndx;
		}

		const std::set<sb::Shader::Stage>& getStages(void) const
		{
			return m_stages;
		}

		void setAllStages(void)
		{
			m_is_all_stages = true;
			m_stages.emplace(sb::Shader::Stage::All);
		}

		bool isAllStages(void) const
		{
			return m_is_all_stages;
		}

		void write_custom_set_ndx(token_output &o, Sbi sbi, size_t set_ndx) const
		{
			if (sbiIsGlsl(sbi)) {
				if (m_mapped_block)
					m_mapped_block->write(o, sbi, set_ndx);
				for (auto &opq : m_opaque_vars)
					opq.write(o, sbi, set_ndx);
			} else
				throw std::runtime_error("Unsupported SBI");
		}

		void write(token_output &o, Sbi sbi) const override
		{
			write_custom_set_ndx(o, sbi, m_set_ndx);
		}

		void addToStage(Stage &stage)
		{
			m_stages.emplace(stage.getStage());
			//stage.addSet(*this);
		};

		auto& getName(void) const { return m_name; }
		auto& getVariables(void) const { return m_variables; }
		auto getLayout(void) const
		{
			sb::Shader::DescriptorSet::Layout::Description res;

			if (m_mapped_block)
				res.emplace_back(m_mapped_block->getLayoutBinding());
			for (auto &o : m_opaque_vars)
				res.emplace_back(o.getLayoutBinding());
			return res;
		}

		auto& getCompiler(void) { return m_compiler; }

	private:
		Compiler &m_compiler;
		size_t m_set_ndx;
		Counter m_binding_counter;
		std::string m_name;
		std::optional<GlslMappedBlock> m_mapped_block;
		std::vector<GlslOpaqueVar> m_opaque_vars;
		std::set<sb::Shader::Stage> m_stages;
		bool m_is_all_stages;

		util::unique_vector<Variable> m_variables;

		std::string getName(tstream &s)
		{
			s.expect("set");
			return s.poll();
		}

		util::unique_vector<Variable> getVariables(tstream &s, Compiler &compiler)
		{
			util::unique_vector<Variable> res;

			s.expect("{");
			while (s.peek() != "}") {
				auto &first = res.emplace(compiler, s, Variable::Storage::Inline);
				varAdded(first);
				while (s.peek() == ",") {
					s.poll();
					varAdded(res.emplace(s, first));
				}
				s.expect(";");
			}
			s.poll();
			return res;
		}

		void varAdded(Variable &var)
		{
			auto parsed = var.getType().parse("nolayout");

			if (parsed.is_opaque) {
				m_opaque_vars.emplace_back(*this, m_binding_counter.next(), var);
			} else {
				if (!m_mapped_block)
					m_mapped_block.emplace(*this, m_binding_counter.next(), m_name);
				m_mapped_block->add(var);
			}
		}
	};

	class ForeignSet
	{
	public:
		ForeignSet(Set &base, size_t set_ndx) :
			m_base(base),
			m_set_ndx(set_ndx)
		{
		}

		void write(token_output &o, Sbi sbi) const
		{
			m_base.write_custom_set_ndx(o, sbi, m_set_ndx);
		}

		std::set<Shader::Stage>& getStages(void)
		{
			return m_stages;
		}

		const std::set<Shader::Stage>& getStages(void) const
		{
			return m_stages;
		}

		Set& getSet(void)
		{
			return m_base;
		}

		auto getNdx(void)
		{
			return m_set_ndx;
		}

	private:
		Set &m_base;
		size_t m_set_ndx;
		std::set<Shader::Stage> m_stages;
	};

private:
	class Section : public Primitive
	{
		using StageTable = std::map<std::string, Shader::Stage>;

		static auto& stageTable(void)
		{
			static const StageTable table {
				{"tesselation_control", Shader::Stage::TesselationControl},
				{"tesselation_evaluation", Shader::Stage::TesselationEvaluation},
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

		void write_no_set(token_output &o, Sbi sbi) const
		{
			for (auto &p : m_primitives) {
				if (dynamic_cast<const Set*>(&p))
					continue;
				p.write(o, sbi);
			}
		}

		void poll(tstream &s, Compiler &compiler);

		void recurAdd(Primitive &prim)
		{
			if (m_stage)
				m_stage->add(prim);
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

		auto& getPrimitives(void)
		{
			return m_primitives;
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
					auto [it, suc] = stages.emplace(std::piecewise_construct, std::forward_as_tuple(stage), std::forward_as_tuple(m_compiler, stage));
					if (!suc)
						throw std::runtime_error("Can't emplace stage");
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

private:
	tstream m_stream;
	Section m_collec;
	Compiler *m_vertex = nullptr;
	bool m_has_custom_vertex;
	bool m_is_complete;

public:
	Compiler* getVertex(void)
	{
		return m_vertex;
	}

private:
	bool computeHasCustomVertexLocal(void) const
	{
		if (m_stages.size() == 0)
			return false;
		if (m_stages.begin()->first == sb::Shader::Stage::Fragment)
			return false;

		return m_stages.begin()->second.getRawInVariables().size() > 0;
	}

	bool hasCustomVertex(void) const
	{
		return m_has_custom_vertex;
	}

	bool isStageComplete(sb::Shader::Stage stage) const
	{
		auto stageit = m_stages.find(stage);
		if (stageit == m_stages.end())
			return false;
		if (!stageit->second.isComplete())
			return false;
		return true;
	}

	bool computeHasCustomVertex(void)
	{
		for (auto &d : m_deps.getCompilers()) {
			if (d.get().hasCustomVertex()) {
				if (m_vertex) {
					std::stringstream ss;
					ss << "Have another dep '" << m_vertex->getModuleEntry().getPath() << "' defining vertex input prior to dep '" << d.get().getModuleEntry().getPath() << "'";
					throw std::runtime_error(ss.str());
				} else {
					m_vertex = &d.get();
				}
			}
		}
		auto res = computeHasCustomVertexLocal();
		if (res)
			if (m_vertex) {
				std::stringstream ss;
				ss << "Have dep '" << m_vertex->getModuleEntry().getPath() << "' defining vertex input prior to inner definition";
				throw std::runtime_error(ss.str());
			}
		if (m_vertex && m_stages.size() > 0)
			for (auto &in : m_vertex->getStages().begin()->second.getRawInVariables())
				m_stages.begin()->second.addIn(in);

		for (auto &s : m_stages)
			s.second.done();
		return res;
	}

	bool getIsComplete(void)
	{
		if (!isStageComplete(sb::Shader::Stage::Vertex))
			return false;
		if (!isStageComplete(sb::Shader::Stage::Fragment))
			return false;
		return true;
	}

public:
	Compiler(const sb::Resource::Compiler::modules_entry &entry);

	bool isModule(void) const
	{
		return !m_is_complete;
	}

	bool isPureModule(void) const
	{
		return isModule() && m_stages.size() == 0;
	}

private:
	void addStagePureIOs(Compiler &dep, Stage &stage)
	{
		for (auto &p : dep.m_collec.getPrimitives()) {
			auto var = dynamic_cast<Variable*>(&p);
			if (var) {
				if (var->getStorage() == Variable::Storage::In)
					stage.addIn(*var);
				if (var->getStorage() == Variable::Storage::Out)
					stage.addOut(*var);
			}
		}
	}
};

class Shader::Compiler::Require : public Shader::Compiler::Primitive
{
public:
	Require(Compiler &compiler, tstream &s) :
		m_compiled(getCompiled(compiler.getModuleEntry(), s))
	{
		compiler.insertReadDep(m_compiled);
		compiler.getForeignSet(m_compiled);
	}

	static bool isComingUp(tstream &s)
	{
		return s.peek() == "require";
	}

	void write(token_output &o, Sbi sbi) const override
	{
		static_cast<void>(o);
		static_cast<void>(sbi);
	}

	Compiler& getCompiler(void)
	{
		return m_compiled;
	}

private:
	Compiler m_compiled;

	Compiler getCompiled(const sb::Resource::Compiler::modules_entry &entry, tstream &s)
	{
		std::vector<std::string> expr;

		s.expect("require");
		while (true) {
			auto &cur = s.poll();
			if (cur == ";")
				break;
			expr.emplace_back(cur);
		}
		return Compiler(entry.resolve_scope_expr(expr));
	}
};

inline bool Shader::Compiler::Stage::tryAddRequire(Primitive &prim)
{
	auto req = dynamic_cast<Require*>(&prim);
	if (req) {
		m_compiler.insertDepFromStage(req->getCompiler(), m_stage);
		return true;
	} else
		return false;
}

inline void Shader::Compiler::Section::poll(tstream &s, Compiler &compiler)
{
	if (s.peek() == ";") {
		s.poll();
		return;
	}
	if (Section::isComingUp(s))
		m_primitives.emplace<Section>(s, compiler);
	else if (Struct::isComingUp(s)) {
		compiler.addStruct(s, compiler);
	} else if (Set::isComingUp(s)) {
		m_primitives.emplace<Set>(s, compiler);
	} else if (Variable::isComingUp(s)) {
		auto &first = m_primitives.emplace<Variable>(compiler, s);
		while (s.peek() == ",") {
			s.poll();
			m_primitives.emplace<Variable>(s, first);
		}
		s.expect(";");
	} else if (Require::isComingUp(s)) {
		m_primitives.emplace<Require>(compiler, s);
	} else
		m_primitives.emplace<Function>(s);
}

inline Shader::Compiler::Compiler(const sb::Resource::Compiler::modules_entry &entry) :
	m_entry(entry),
	m_stages(*this),
	m_stream(tstream::tokenize(rs::Compiler::read(entry.getPath().string()), true)),
	m_collec(m_stream, *this),
	m_has_custom_vertex((m_collec.dispatch(), computeHasCustomVertex())),
	m_is_complete(getIsComplete())
{
	if (isPureModule()) {
		for (auto &d : m_read_deps) {
			if (!d.get().isPureModule()) {
				std::stringstream ss;
				ss << "pure module can't require non pure module '" << d.get().getModuleEntry().getPath().string() << "'";
				throw std::runtime_error(ss.str());
			}
			insertDep(d);
		}
		for (auto &s : m_sets)
			s.get().setAllStages();
	}
}

}