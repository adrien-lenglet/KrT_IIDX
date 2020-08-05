#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <optional>
#include <functional>

#include "cpp_generator.hpp"
#include "Subtile/Shader/Compiler.hpp"
#include "Subtile/Resource/Shader.hpp"

using namespace CppGenerator;

namespace std {
namespace fs = filesystem;
}

class FolderPrinter
{
	//Util::CollectionBase &m_out;
	Util::CollectionBase &m_impl_out;

	static std::string id_storage(const std::string &id)
	{
		static const std::string st("_storage");

		return id + st;
	}

	static std::optional<std::tuple<std::string, std::string>> getMember(const std::fs::path &path)
	{
		static const std::map<std::string, std::string> exts = {
			{".obj", "sb::rs::Model"},
			{".png", "sb::rs::Image"},
			{".sbsl", "sb::rs::Shader"},
		};

		auto ext = path.extension().string();
		auto got = exts.find(ext);

		if (got == exts.end())
			return std::nullopt;
		auto &type = got->second;
		auto id = path.stem().string();
		return std::make_tuple(type, id);
	}

	static std::string class_name(const std::string &str)
	{
		static const std::string cl("_class");

		return str + cl;
	}

	void addgetterstorage(Util::CollectionBase &scope, Util::CollectionFunctionBase &ctor, Type t, const std::string &idRaw, const std::string &basefile)
	{
		Id id(idRaw);

		scope += Private;
		auto st = scope += t | &N | Id(id_storage(id.getValue()));
		scope += Public;
		auto getter = scope += t | &N | Id(id)(Void);
		m_impl_out += t | &N | getter(Void) | S
		{
			Return | st
		};

		ctor /= st("add"_v.T(t)(basefile));
	}

	Brace shaderStagesToBrace(const std::set<sb::Shader::Stage> &stages)
	{
		static const std::map<sb::Shader::Stage, Value> table {
			{sb::Shader::Stage::TesselationControl, "sb::Shader::Stage::TesselationControl"_v},
			{sb::Shader::Stage::TesselationEvaluation, "sb::Shader::Stage::TesselationEvaluation"_v},
			{sb::Shader::Stage::Geometry, "sb::Shader::Stage::Geometry"_v},
			{sb::Shader::Stage::Vertex, "sb::Shader::Stage::Vertex"_v},
			{sb::Shader::Stage::Fragment, "sb::Shader::Stage::Fragment"_v}
		};

		Brace res;

		for (auto &s : stages)
			res.add(table.at(s));
		return res;
	}

	template <bool isTemplate>
	decltype(auto) createShaderStructCollec(Util::CollectionBase &scope, const std::string &name)
	{
		auto a_name = std::string("_") + name + std::string("Collection");

		if constexpr (isTemplate)
			return scope += Template(Typename | "Layout") || Struct | a_name | S {};
		else
			return scope += Struct | a_name | S {};
	}

	template <bool isTemplate>
	decltype(auto) createShaderStructFinal(Util::CollectionBase &scope, const std::string &name, const Type &tfinal)
	{
		if constexpr (isTemplate)
			return scope += Template(Typename | "Layout") || (Using | name = tfinal);
		else
			return scope += Using | name = tfinal;
	}

	template <bool isTemplate>
	decltype(auto) createShaderStruct(Util::CollectionBase &scope, Util::CollectionBase &user_structs_scope, const std::string &name, const std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> &variables, const std::string &layout)
	{
		auto layout_c = isTemplate ? "Layout"_t : Type(layout);
		auto &s = createShaderStructCollec<isTemplate>(scope, name);

		std::vector<Id> ids;
		std::optional<Id> prev_id;
		for (auto &var : variables) {
			auto &v = var.get();
			auto p = v.getType().parse(layout);
			Type t = p.name;
			if (p.is_user_defined)
				t.assign((user_structs_scope >> t).T(layout_c));

			if (prev_id)
				t.assign("sb::Shader::Type::StructMember"_t.T(t, layout_c, Decltype(*prev_id)));
			else
				t.assign("sb::Shader::Type::StructMember"_t.T(t, layout_c));
			prev_id = s += t | Id(v.getName());
			ids.emplace_back(*prev_id);
		}

		s += Private;

		auto &vertex_input = s += Void | Id("createVertexInput")("sb::Shader::VertexInput::Creator"_t | &N | Id("creator")) | Const | S {};
		for (auto &i : ids)
			vertex_input += "sb::Shader::Type::CreateVertexInputAccessor"_t(i).M("create"_v("creator"_v));
		s += "template <typename> friend class sb::Shader::Type::CreateVertexInputAccessor"_v;

		auto s_w_param = Type(s);
		if constexpr (isTemplate)
			s_w_param.assign(s_w_param.T("Layout"_t));

		auto tfinal = "sb::Shader::Type::Struct"_t.T(s_w_param);
		for (auto &i : ids)
			tfinal.add(Decltype(s_w_param().M(i)));
		auto mapped_str = createShaderStructFinal<isTemplate>(scope, name, tfinal);
		return mapped_str;
	}

	Value getDescriptorType(sb::Shader::DescriptorType type)
	{
		static const std::map<sb::Shader::DescriptorType, Value> table {
			{sb::Shader::DescriptorType::UniformBuffer, "sb::Shader::DescriptorType::UniformBuffer"_v},
			{sb::Shader::DescriptorType::CombinedImageSampler, "sb::Shader::DescriptorType::CombinedImageSampler"_v}
		};

		return table.at(type);
	}

	auto shaderAddLayout(Util::CollectionBase &scope, Util::CollectionBase &user_structs_scope, const sb::Shader::Compiler::Set &set)
	{
		auto &set_scope = scope += Struct | set.getName() | S {};
		std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> vars;
		for (auto &v : set.getVariables())
			vars.emplace_back(v);
		auto mapped_str = createShaderStruct<false>(set_scope, user_structs_scope, "Mapped", vars, "sb::Shader::Type::Std140");

		auto t = "sb::Shader::DescriptorSet::Layout::Description"_t;

		auto fwd = set_scope += Static | t | Id("getLayout")(Void);
		auto &impl = m_impl_out += t | fwd(Void) | S {};

		auto gen_bindings = B {};
		auto layout = set.getLayout();
		for (auto &b : layout) {
			Value count = b.descriptorCount;
			if (sb::Shader::descriptorTypeIsMapped(b.descriptorType))
				count.assign(Sizeof(mapped_str));
			gen_bindings.add(B {b.binding, count, getDescriptorType(b.descriptorType), shaderStagesToBrace(b.stages)});
		}
		impl += Return | gen_bindings;

		return std::tuple<Util::CollectionBase&, Id>(set_scope, fwd);
	}

	auto shaderAddVertexInput(Util::CollectionBase &scope, Util::CollectionBase &user_structs_scope, sb::Shader::Compiler &shader)
	{
		std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> vars;
		for (auto &io : shader.getStages().begin()->second.getInterface())
			if (io.getDir() == sb::Shader::Compiler::Stage::InterfaceInOut::Dir::In) {
				vars.emplace_back(io.getVariable());
			}
		auto vertex_t = createShaderStruct<false>(scope, user_structs_scope, "Vertex", vars, "sb::Shader::Type::Std430");

		auto t = "sb::Shader::VertexInput"_t;
		auto fwd = scope += t | Id("vertexInput")(Void) | Const | Override;
		auto &impl = m_impl_out += t | fwd(Void) | Const | S {};

		auto res = impl += t | "res" | B {Sizeof(vertex_t), B {}};
		auto vertex = impl += vertex_t | "vertex";
		auto creator = impl += t>>"Creator"_t | Id("creator")(vertex, res);
		impl += "sb::Shader::Type::CreateVertexInputAccessor"_t("vertex"_v).M("create"_v(creator));
		impl += Return | "res"_v;

		return scope += Using | "Model" = "sb::Model"_t.T(vertex_t);
	}

	Type addShader(Util::CollectionBase &scope, const std::string &id, const std::string &shaderpath, const std::fs::directory_entry &shaderentry)
	{
		static const Type shader_type("sb::rs::Shader");
		sb::Shader::Compiler compiled(shaderpath);

		//scope += Private;
		auto &sh = scope += Class | (id + std::string("_type")) | C(Public | shader_type) | S {Public};
		auto ctor_fwd = sh += Ctor(Void);
		auto &ctor = m_impl_out += ctor_fwd(Void) | S {};
		auto dtor_fwd = sh += Dtor(Void);
		m_impl_out += dtor_fwd(Void) | S {};

		ctor /= shader_type(shaderStagesToBrace(compiled.getStages().getSet()));

		auto &u_structs = sh += Struct | "Struct" | S {};
		for (auto &us_desc : compiled.getStructs()) {
			std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> vars;
			for (auto &v : us_desc.getVariables())
				vars.emplace_back(v);
			createShaderStruct<true>(u_structs, u_structs, us_desc.getName(), vars, "Layout");
		}
		auto model = shaderAddVertexInput(sh, u_structs, compiled);

		auto ref_acc = "sb::Shader::DescriptorSet::RefAccessor"_t.T("Up"_t);
		auto unique_ref = "sb::Shader::UniqueRef"_t;

		auto &u_sets = sh += Struct | "Set" | S {};
		auto &runtime = sh += Template(Typename | "Up") || Class | "Runtime" | S
		{
			unique_ref | &N | Id("m_ref"),
		Public,
			Ctor(unique_ref | &N | Id("ref"))  | C(Id("m_ref")("ref"_v)) | S
			{
				StaticCast(Void, "m_ref"_v)
			}
		};

		auto vec_resolver = "sb::rs::Shader::DescriptorSetLayouts"_t;
		auto desc_layout_fwd = sh += vec_resolver | Id("loadDescriptorSetLayouts")("sb::ISystem"_t | &N | Id("sys")) | Const | Override;
		auto &desc_layout = m_impl_out += vec_resolver | desc_layout_fwd("sb::ISystem"_t | &N | Id("sys")) | Const | S
		{
			StaticCast(Void, "sys"_v)
		};
		auto render_type = "sb::Shader::Render"_t.T(Type(Value(compiled.getSets().size()).getValue()));
		auto &render = runtime += render_type | Id("render")(Const | "sb::Shader::Model::Handle"_t.T(model) | &N | Id("model")) | S {};
		auto render_list = B {};
		size_t ndx = 0;
		auto desc_layout_res = desc_layout += vec_resolver | Id("res");
		for (auto &set : compiled.getSets()) {
			auto [set_scope, getLayout] = shaderAddLayout(u_sets, u_structs, set);

			set_scope +=
			Template(Typename | "Up") ||
			Class | "Runtime" | C(Public | set_scope>>"Mapped"_t) | S
			{
				unique_ref | &N | Id("m_ref"),
				"template <typename> friend class sb::Shader::UniqueRef::Getter"_v,
			Public,
				Ctor(unique_ref | &N | Id("ref")) | C(Id("m_ref")("ref"_v)) | S
				{
					StaticCast(Void, "m_ref"_v)
				}
			};
			desc_layout += "res"_v.M("emplace_back"_v("new sb::Shader::DescriptorSet::Layout::Resolver::Inline"_v("sys"_v, Vd(getLayout.getValue())())));
			auto handle_t = "sb::Shader::DescriptorSet::Handle"_t.T(set_scope);
			runtime += handle_t | Id(set.get().getName())(Void) | S
			{
				Return | handle_t("m_ref"_v, ndx)
			};

			auto param = render *= handle_t | &N | Id(set.get().getName());
			render_list.add(param);

			ndx++;
		}
		desc_layout += Return | desc_layout_res;
		render += Return | render_type("m_ref"_v.M("getShader"_v()), "sb::Shader::Model::BaseHandle::Getter"_t("model"_v).M("getModel"_v()), render_list);

		auto name = shaderentry.path().parent_path().string() + std::string("/.") + id + std::string("_stages");
		std::fs::create_directory(name);
		for (auto &s : compiled.getStages()) {
			for (auto &sbi : sb::Shader::getSbi()) {
				std::stringstream ss;
				s.second.write(ss, sbi);

				auto data = ss.str();
				auto path = name + std::string("/") + sb::rs::Shader::Stage::Source::getFileName(s.first, sbi);
				if (data != Util::File::read(path)) {
					std::ofstream file(path, std::ios::binary);
					file << data;
				}
			}
		}

		sh += Static | "sb::Shader::Loaded"_t.T(sh) | Id("loaded")(Void) | S
		{
			"throw"_v
		};

		return sh;
	}

	class FileError : public std::runtime_error
	{
	public:
		template <typename ...Args>
		FileError(Args &&...args) :
			std::runtime_error(computeErrMsg(std::forward<Args>(args)...))
		{
		}

	private:
		static std::string computeErrMsg(const std::string &type, const std::string &path, const std::string &what)
		{
			std::stringstream ss;

			ss << "[" << type << "]: " << path << " fatal error:" << std::endl;
			ss << what << std::endl;
			return ss.str();
		}
	};

	template <typename T>
	void it_dir(const T &itbase, Util::CollectionBase &scope, Util::CollectionFunctionBase &ctor)
	{
		auto dtor_fwd = scope += Dtor(Void) | Override;
		m_impl_out += dtor_fwd(Void) | S{};

		for (auto &e : std::fs::directory_iterator(itbase)) {
			auto &path = e.path();
			auto name = path.filename().string();
			if (name.at(0) == '.')
				continue;

			if (e.is_directory()) {
				auto &cl = scope += Class | class_name(name) | C(Public | "sb::rs::Folder"_t) | S{};
				addgetterstorage(scope, ctor, cl, name, name);
				cl += Public;
				auto ctor_fwd = cl += Ctor(Void);
				auto &ctor_sub = m_impl_out += ctor_fwd(Void) | S{};
				it_dir(e, cl, ctor_sub);
			} else {
				auto got = getMember(e.path());
				if (got) {
					auto [type, id] = *got;
					auto t = Type(type);

					if (type == "sb::rs::Shader") {
						try {
							t.assign(addShader(scope, id, e.path().string(), e));
						} catch (const std::exception &excep) {
							throw FileError(type, e.path().string(), excep.what());
						}
					}
					addgetterstorage(scope, ctor, t, id, name);
				}
			}
		}
	}

	void print(const std::string &root, Util::CollectionBase &scope)
	{
		auto fname = std::fs::path(root).filename().string();
		auto &cl = scope += Class | class_name(fname) | C(Public | "sb::rs::Folder"_t) | S{};

		cl += Public;
		auto ctor_fwd = cl += Ctor(Void);
		auto &ctor = m_impl_out += ctor_fwd(Void) | S{};

		ctor /= "sb::rs::Folder"_t("is_root"_v, fname);

		it_dir(root, cl, ctor);

		auto var = scope += Extern | cl | Id(fname);
		m_impl_out += cl | var;
	}

public:
	FolderPrinter(Util::CollectionBase &scope, Util::CollectionBase &impl_out, Util::CollectionBase &out, const std::string &root) :
		//m_out(out),
		m_impl_out(impl_out)
	{
		static_cast<void>(out);
		print(root, scope);
	}
	~FolderPrinter(void)
	{
	}
};

class ResourceCompiler
{
public:
	static void run(const std::string &root, const std::vector<std::string> &ns, const std::string &implpath, const std::string &hpath)
	{
		Out header(hpath);

		header | S {
			Pp::Pragma | "once",
			Pp::Include | "Subtile/Instance.hpp",
			Pp::Include | "Subtile/Resource/Folder.hpp",
			Pp::Include | "Subtile/Resource/Model.hpp",
			Pp::Include | "Subtile/Resource/Image.hpp",
			Pp::Include | "Subtile/Resource/Shader.hpp"
		};

		Out impl(implpath);

		auto hp = std::fs::path(hpath).filename().string();

		impl.include(header);	// inline inclusion, ensure coherency of resource compilation

		Util::CollectionBase *collec = std::addressof(header);
		for (auto &n : ns)
			collec = std::addressof((*collec) += Namespace | n | S {});

		FolderPrinter(*collec, impl, header, root);
	}
};

static auto getOutpath(const std::string &root, const std::string &output, const std::string &ext)
{
	std::stringstream ss;

	ss << output << "/" << std::fs::path(root).filename().string() << ext;
	return ss.str();
}

static auto getArgs(int argc, char **argv)
{
	std::vector<std::string> res;

	for (int i = 1; i < argc; i++)
		res.emplace_back(argv[i]);
	return res;
}

static auto getNs(const std::vector<std::string> &args)
{
	std::vector<std::string> res;

	for (size_t i = 2; i < args.size(); i++)
		res.emplace_back(args.at(i));
	return res;
}

int main(int argc, char **argv)
{
	auto args = getArgs(argc, argv);
	auto &input = args.at(0);
	auto &output = args.at(1);
	auto ns = getNs(args);

	auto in = getOutpath(input, output, ".resdecl.cpp");
	auto out = getOutpath(input, output, ".resdecl.hpp");

	try {
		ResourceCompiler::run(input, ns, in, out);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

	return 0;
}