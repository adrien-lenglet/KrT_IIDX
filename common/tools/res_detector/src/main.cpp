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

	void addVariableToStructCollec(Util::CollectionBase &scope, sb::Shader::Compiler::Variable &var, std::optional<Id> &prev_id, std::vector<Id> &ids)
	{
		auto &t = var.getType();
		auto &p = t.getParsed();
		Type t_fin = p.name;
		if (p.is_user_defined)
			t_fin.assign(scope >> t_fin);

		if (prev_id)
			t_fin.assign("sb::Shader::Type::StructMember"_t.T(t_fin, Decltype(*prev_id)));
		else
			t_fin.assign("sb::Shader::Type::StructMember"_t.T(t_fin));
		prev_id = scope += t_fin | Id(var.getName());
		ids.emplace_back(*prev_id);
	}

	void shaderaddlayout(Util::CollectionBase &scope, sb::Shader::Compiler::Set set, const std::string &met_name, sb::Shader::Compiler &shader)
	{
		std::optional<Id> previous_id;
		auto &mat_scope = scope += Struct | (met_name + std::string("Traits")) | S {};
		auto &str = mat_scope += Struct | "MappedCollection" | S {};
		auto str_ctor = str();
		std::vector<Id> ids;

		for (auto &sb : shader.getDescriptorSets())
			if (sb.get().getSet() == set)
				for (auto &b : sb.get().getBlocks()) {
					auto &nopq = b.getGlslNonOpaque();
					if (nopq) {
						for (auto &no : nopq->getVariables())
							addVariableToStructCollec(str, no.get(), previous_id, ids);
					}
				}
		auto tfinal = "sb::Shader::Type::Struct"_t.T(str);
		for (auto &i : ids)
			tfinal.add(Decltype(str_ctor.M(i)));
		auto mapped_str = mat_scope += Using | "Mapped" = tfinal;
		/*for (auto &sb : shader.getDescriptorSets())
			if (sb.get().getSet() == set)
				for (auto &b : sb.get().getBlocks())
					for (auto &v : b.getGlslOpaque())
							addVariableToStruct(str, v.getVariable(), previous_id);*/

		auto t = "sb::Shader::DescriptorSet::Layout"_t;

		auto fwd = scope += t | Id(met_name)(Void) | Const | Override;
		auto &impl = m_impl_out += t | fwd(Void) | Const | S {};

		auto bmapped = B {};
		auto bopq = B {};

		for (auto &sb : shader.getDescriptorSets())
			if (sb.get().getSet() == set) {
				auto &blocks = sb.get().getBlocks();
				for (auto &b : blocks) {
					auto &nopq = b.getGlslNonOpaque();
					if (nopq) {
						auto &n = *nopq;
						auto off = Decltype(str_ctor.M(Vd(n.getVariables().begin()->get().getName())))>>"offset::value"_v;
						auto size = Value(0);
						size.assign(size + (Decltype(str_ctor.M(Vd(n.getVariables().rbegin()->get().getName())))>>"offset_end::value"_v) - off);
						bmapped.add(B {B {n.getBinding(), static_cast<size_t>(1), "sb::Shader::DescriptorType::UniformBuffer"_v, shaderStagesToBrace(b.getStages())}, off, size});
					}
					for (auto &v : b.getGlslOpaque()) {
						size_t count = 1;
						auto &arr = v.getVariable().getArray();
						if (arr.size() > 0)
							count = arr.at(0);
						bopq.add(B {v.getBinding(), count, "sb::Shader::DescriptorType::CombinedImageSampler"_v, shaderStagesToBrace(b.getStages())});
					}
				}
			}
		impl += Return | B {bmapped, Sizeof(mapped_str), bopq};
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

		shaderaddlayout(sh, sb::Shader::Compiler::Set::Material, "material", compiled);
		shaderaddlayout(sh, sb::Shader::Compiler::Set::Object, "object", compiled);

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

		return sh;
	}

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

					if (type == "sb::rs::Shader")
						t.assign(addShader(scope, id, e.path().string(), e));
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
	FolderPrinter(Util::CollectionBase &out, Util::CollectionBase &impl_out, const std::string &root) :
		m_impl_out(impl_out)
	{
		print(root, out);
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

		FolderPrinter(*collec, impl, root);
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
	ResourceCompiler::run(input, ns, in, out);

	return 0;
}