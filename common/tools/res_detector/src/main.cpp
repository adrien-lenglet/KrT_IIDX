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
#include "Subtile/RenderPass/Compiler.hpp"
#include "Subtile/Shader/Compiler.hpp"
#include "Subtile/Resource/Shader.hpp"
#include "Subtile/Resource/RenderPass.hpp"

using namespace CppGenerator;

class FolderPrinter
{
	Util::CollectionBase &m_scope;
	//Util::CollectionBase &m_out;
	Util::CollectionBase &m_impl_out;

	static std::string id_storage(const std::string &id)
	{
		static const std::string st("_storage");

		return id + st;
	}

	static std::optional<std::string> getMember(const std::fs::path &path)
	{
		static const std::map<std::string, std::string> exts = {
			{".obj", "sb::rs::Model"},
			{".png", "sb::rs::Image"},
			{".sbsl", "sb::rs::Shader"},
			{".sbrp", "sb::rs::RenderPass"}
		};

		auto ext = path.extension().string();
		auto got = exts.find(ext);

		if (got == exts.end())
			return std::nullopt;
		return got->second;
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
			{sb::Shader::Stage::Fragment, "sb::Shader::Stage::Fragment"_v},
			{sb::Shader::Stage::All, "sb::Shader::Stage::All"_v}
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
	decltype(auto) createShaderStruct(Util::CollectionBase &scope, const std::string &name, const std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> &variables, const std::string &layout)
	{
		auto layout_c = isTemplate ? "Layout"_t : Type(layout);
		auto &s = createShaderStructCollec<isTemplate>(scope, name);

		s += Using | "MemberCount" = "std::integral_constant"_t.T(Size_t, Type(Value(variables.size()).getValue()));

		std::vector<Id> ids;
		std::optional<Id> prev_id;
		for (auto &var : variables) {
			auto &v = var.get();
			auto p = v.getType().parse(layout);
			Type t = p.name;
			if (p.is_opaque)
				std::runtime_error(std::string("Opaque variable '") + v.getName() + std::string("' found in struct"));

			if (p.is_user_defined)
				t.assign((m_scope >> Type(p.user_defined_type)).T(layout_c));

			if (prev_id)
				t.assign("sb::Shader::Type::StructMember"_t.T(t, layout_c, Decltype(*prev_id)));
			else
				t.assign("sb::Shader::Type::StructMember"_t.T(t, layout_c));
			prev_id = s += t | Id(v.getName());
			ids.emplace_back(*prev_id);
		}

		s += Private;

		auto &vertex_input = s += Void | Id("createVertexInput")("sb::Shader::VertexInput::Creator"_t | &N | Id("creator")) | Const | S
		{
			StaticCast(Void, "creator"_id)
		};
		for (auto &i : ids)
			vertex_input += "sb::Shader::Type::CreateVertexInputAccessor"_t.T(Decltype(i))(i).M("create"_v("creator"_v));
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
			{sb::Shader::DescriptorType::Sampler, "sb::Shader::DescriptorType::Sampler"_v},
			{sb::Shader::DescriptorType::CombinedImageSampler, "sb::Shader::DescriptorType::CombinedImageSampler"_v},
			{sb::Shader::DescriptorType::SampledImage, "sb::Shader::DescriptorType::SampledImage"_v},
			{sb::Shader::DescriptorType::StorageImage, "sb::Shader::DescriptorType::StorageImage"_v},
			{sb::Shader::DescriptorType::UniformTexelBuffer, "sb::Shader::DescriptorType::UniformTexelBuffer"_v},
			{sb::Shader::DescriptorType::StorageTexelBuffer, "sb::Shader::DescriptorType::StorageTexelBuffer"_v},
			{sb::Shader::DescriptorType::UniformBuffer, "sb::Shader::DescriptorType::UniformBuffer"_v},
			{sb::Shader::DescriptorType::StorageBuffer, "sb::Shader::DescriptorType::StorageBuffer"_v},
			{sb::Shader::DescriptorType::UniformBufferDynamic, "sb::Shader::DescriptorType::UniformBufferDynamic"_v},
			{sb::Shader::DescriptorType::StorageBufferDynamic, "sb::Shader::DescriptorType::StorageBufferDynamic"_v},
			{sb::Shader::DescriptorType::InputAttachment, "sb::Shader::DescriptorType::InputAttachment"_v}
		};

		return table.at(type);
	}

	auto shaderAddLayout(Util::CollectionBase &scope, const sb::Shader::Compiler::Set &set)
	{
		auto &set_scope = scope += Struct | set.getName() | S {};
		std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> uniform_vars;
		std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> storage_vars;
		if (set.getUniform()) {
			for (auto &v : set.getUniform()->getVariables())
				uniform_vars.emplace_back(v);
		}
		if (set.getStorage()) {
			for (auto &v : set.getStorage()->getVariables())
				storage_vars.emplace_back(v);
		}
		auto uniform_str = createShaderStruct<false>(set_scope, "Uniform", uniform_vars, "sb::Shader::Type::Std140");
		auto storage_str = createShaderStruct<false>(set_scope, "Storage", storage_vars, "sb::Shader::Type::Std430");

		auto t = "sb::Shader::DescriptorSet::Layout::Description"_t;

		auto fwd = set_scope += Static | t | Id("getLayout")(Void);
		auto &impl = m_impl_out += t | fwd(Void) | S {};

		auto gen_bindings = B {};
		auto layout = set.getLayout();
		for (auto &b : layout) {
			Value count = b.descriptorCount;
			if (sb::Shader::descriptorTypeIsMapped(b.descriptorType)) {
				if (b.descriptorType == sb::Shader::DescriptorType::UniformBuffer)
					count.assign(Sizeof(uniform_str));
				else if (b.descriptorType == sb::Shader::DescriptorType::StorageBuffer)
					count.assign(Sizeof(storage_str));
				else
					throw std::runtime_error("Unknown storage type");
			}
			gen_bindings.add(B {b.binding, count, getDescriptorType(b.descriptorType), shaderStagesToBrace(b.stages)});
		}
		impl += Return | gen_bindings;

		return std::tuple<Util::CollectionBase&, Id>(set_scope, fwd);
	}

	Type shaderAddVertex_t(Util::CollectionBase &scope, sb::Shader::Compiler &shader)
	{
		if (shader.getVertex()) {
			return scope += Using | "Vertex" = m_scope >> Type(shader.getVertex()->getModuleEntry().getResPath()) >> "Vertex"_t;
		} else {
			std::vector<std::reference_wrapper<const sb::Shader::Compiler::Variable>> vars;
			if (shader.getStages().size() > 0)
				for (auto &io : shader.getStages().begin()->second.getInterface())
					if (io.getDir() == sb::Shader::Compiler::Stage::InterfaceInOut::Dir::In)
						vars.emplace_back(io.getVariable());
			return createShaderStruct<false>(scope, "Vertex", vars, "sb::Shader::Type::Std430");
		}
	}

	void shaderAddVertexInput(Util::CollectionBase &scope, sb::Shader::Compiler &shader)
	{
		auto vertex_t = shaderAddVertex_t(scope, shader);

		auto t = "sb::Shader::VertexInput"_t;
		auto fwd = scope += t | Id("vertexInput")(Void) | Const | Override;
		auto &impl = m_impl_out += t | fwd(Void) | Const | S {};

		auto res = impl += t | "res" | B {Sizeof(vertex_t), B {}};
		auto vertex = impl += vertex_t | "vertex";
		auto creator = impl += t>>"Creator"_t | Id("creator")(vertex, res);
		impl += "sb::Shader::Type::CreateVertexInputAccessor"_t("vertex"_v).M("create"_v(creator));
		impl += Return | "res"_v;
	}

	struct ResSet
	{
		ResSet(const std::string &name, const Type &type, const Type &set_type) :
			name(name),
			type(type),
			set_type(set_type)
		{
		}

		std::string name;
		Type type;
		Type set_type;
		Value value;
		std::optional<Id> inlineValue;
		size_t foreignNdx;
	};

	Type addShader(Util::CollectionBase &scope, const sb::Resource::Compiler::modules_entry &entry)
	{
		static const Type shader_type("sb::rs::Shader");
		sb::Shader::Compiler compiled(entry);

		//scope += Private;
		auto &sh = scope += Class | (entry.getId() + std::string("_class")) | C(Public | shader_type) | S {Public};
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
			createShaderStruct<true>(u_structs, us_desc.getName(), vars, "Layout");
		}
		shaderAddVertexInput(sh, compiled);

		auto ref_acc = "sb::Shader::DescriptorSet::RefAccessor"_t.T("Up"_t);
		auto unique_ref = "sb::Shader::Cache::Ref"_t;

		auto &u_sets = sh += Struct | "Set" | S {};
		auto &runtime = sh += Template(Typename | "Up") || Class | "Runtime" | S
		{
			unique_ref | &N | Id("m_ref"),
		Public,
			Ctor(unique_ref | &N | Id("ref"))  | C(Id("m_ref")("ref"_v)) | S
			{
				StaticCast(Void, "m_ref"_v)
			},
			Using | "Vertex" = sh>>"Vertex"_t
		};

		size_t ndx = 0;
		std::vector<util::ref_wrapper<Util::CollectionBase>> set_scopes;
		std::vector<Id> layouts;
		for (auto &set : compiled.getSets()) {
			auto [set_scope, getLayout] = shaderAddLayout(u_sets, set);
			set_scopes.emplace_back(set_scope);
			layouts.emplace_back(getLayout);

			auto &set_runtime = set_scope +=
			Template(Typename | "Up") ||
			Class | "Runtime" | C(Public | set_scope>>"Uniform"_t, Public | set_scope>>"Storage"_t) | S
			{
			Public
			};

			auto &ctor = set_runtime +=
			Ctor("sb::Shader::DescriptorSet"_t | &N | Id("set")) | S
			{
				StaticCast(Void, "set"_v)
			};

			for (auto &nopq : set.get().getOpaque()) {
				auto &v = nopq.getVariable();
				auto p = v.getType().parse("irrelevant");

				if (v.getType().getArray().size() == 0) {
					auto mem = set_runtime += Type(p.name).T(Type(Value(nopq.getBinding()).getValue())) | Id(v.getName());
					ctor /= mem("set, 0"_v);
				} else {
					if (v.getType().getArray().size() != 1) {
						std::stringstream ss;
						ss << "Variable '" << v.getName() << "' is opaque and has more than one array dimension";
						throw std::runtime_error(ss.str());
					}
					auto mem = set_runtime += "sb::Shader::Type::OpaqueArray"_t.T(Type(p.name).T(Type(Value(nopq.getBinding()).getValue())), Type(Value(v.getType().getArray().at(0)).getValue())) | Id(v.getName());
					ctor /= mem("set"_v);
				}
			}

			ndx++;
		}

		std::map<size_t, ResSet> sets;
		ndx = 0;
		for (auto &s : compiled.getSets()) {
			auto &set_scope = set_scopes.at(ndx).get();
			auto [it, suc] = sets.emplace(std::piecewise_construct, std::forward_as_tuple(s.get().getNdx()), std::forward_as_tuple(s.get().getName(), set_scope, set_scope));
			if (!suc)
				throw std::runtime_error("Can't emplace local set in all sets list");
			it->second.inlineValue.emplace(layouts.at(ndx));
			auto handle_t = "sb::Shader::DescriptorSet::Handle"_t.T(set_scope);
			runtime += handle_t | Id(s.get().getName())("sb::Queue"_t | &N | Id("queue")) | S
			{
				Return | handle_t("m_ref"_v, s.get().getNdx(), "queue"_v)
			};

			ndx++;
		}
		for (auto &rp : compiled.getForeignSets())
			for (auto &s : rp.second) {
				auto &mod_entry = s.getSet().getCompiler().getModuleEntry();
				auto type = m_scope >> Type(mod_entry.getResPath());
				auto [it, suc] = sets.emplace(std::piecewise_construct, std::forward_as_tuple(s.getNdx()), std::forward_as_tuple(s.getSet().getName(), type, type >> "Set"_t >> Type(s.getSet().getName())));
				if (!suc)
					throw std::runtime_error("Can't emplace foreign set in all sets list");
				it->second.foreignNdx = s.getSet().getNdx();
				it->second.value.assign(Vd(mod_entry.getResValue()));
			}

		auto vec_resolver = "sb::rs::Shader::DescriptorSetLayouts"_t;
		auto desc_layout_fwd = sh += vec_resolver | Id("loadDescriptorSetLayouts")("sb::Device"_t | &N | Id("dev")) | Const | Override;
		auto &desc_layout = m_impl_out += vec_resolver | desc_layout_fwd("sb::Device"_t | &N | Id("dev")) | Const | S
		{
			StaticCast(Void, "dev"_v)
		};
		auto desc_layout_res = desc_layout += vec_resolver | Id("_res");

		for (auto &rp : sets) {
			if (rp.second.inlineValue)
				desc_layout += desc_layout_res.M("emplace_back"_v("new sb::Shader::DescriptorSet::Layout::Resolver::Inline"_t("dev"_v, Vd(rp.second.inlineValue->getValue())())));
			else
				desc_layout += desc_layout_res.M("emplace_back"_v("new sb::Shader::DescriptorSet::Layout::Resolver::Foreign"_t.T(rp.second.type)("dev"_v, rp.second.value, rp.second.foreignNdx)));
		}

		desc_layout += Return | desc_layout_res;

		if (!compiled.isModule()) {
			auto render_type = "sb::Shader::Render"_t.T(sh, Type(Value(sets.size()).getValue()));
			auto &render = runtime += render_type | Id("render")("sb::Model::Typed"_t.T(sh>>"Vertex"_t) | &N | Id("model")) | S {};
			auto render_list = B {};
			for (auto &set : sets) {
				auto handle_t = "sb::Shader::DescriptorSet::Handle"_t.T(set.second.set_type);
				auto param = render *= handle_t | &N | Id(set.second.name);
				render_list.add(param);

				ndx++;
			}
			render += Return | render_type(**"m_ref"_v, "model"_v, render_list);
		}

		auto render_pass_t = "std::pair<sb::rs::RenderPass&, size_t>"_t;

		auto render_pass = compiled.getRenderPass();
		auto get_render_pass_fwd = sh += render_pass_t | Id("getRenderPass")(Void) | Const | Override;
		auto &get_render_pass = m_impl_out += render_pass_t | get_render_pass_fwd(Void) | Const | S {};
		if (render_pass) {
			//sh += Using | "RenderPass" = render_pass->getCompiled().getModuleEntry().getResValue;
			get_render_pass += Return | render_pass_t(Vd(render_pass->getCompiled().getModuleEntry().getResValue()), render_pass->getSubpass().getNdx());
		} else
			get_render_pass += "throw"_v;

		auto is_module_fwd = sh += Bool | Id("isModule")(Void) | Const | Override;
		m_impl_out += Bool | is_module_fwd(Void) | Const | S
		{
			Return | compiled.isModule()
		};

		{
			static auto return_type = "sb::Shader::PipelineProps"_t;
			auto get_props_fwd = sh += return_type | Id("getProps")(Void) | Const | Override;
			auto &get_props = m_impl_out += return_type | get_props_fwd(Void) | Const | S
			{
				"sb::Shader::PipelineProps"_t | Id("res")
			};

			{
				static const std::vector<std::string> key {"rasterization", ".", "cull_mode"};
				static const std::string def = "back";
				const std::string *cur = &def;
				auto &cullModeVal = compiled.getProp(key);
				if (cullModeVal.size() > 0) {
					if (cullModeVal.size() != 1)
						throw std::runtime_error("Expected one argument only for rasterization.cull_mod");
					cur = &cullModeVal.at(0);
				}

				static const std::map<std::string, std::string> table {
					{"none", "None"},
					{"front", "Front"},
					{"back", "Back"},
					{"front_and_back", "FrontAndBack"}
				};
				get_props += Vd("res.rasterizationCullMode = sb::Shader::CullMode::" + table.at(*cur));
			}

			get_props += Return | "res"_v;
		}

		auto name = entry.getPath().parent_path().string() + std::string("/.") + entry.getId() + std::string("_stages");
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

	static auto loadOpToValue(sb::Image::LoadOp loadOp)
	{
		static const std::map<sb::Image::LoadOp, std::string> table {
			{sb::Image::LoadOp::DontCare, "DontCare"},
			{sb::Image::LoadOp::Load, "Load"},
			{sb::Image::LoadOp::Clear, "Clear"}
		};

		return "sb::Image::LoadOp"_t >> Vd(table.at(loadOp));
	}

	static auto storeOpToValue(sb::Image::StoreOp storeOp)
	{
		static const std::map<sb::Image::StoreOp, std::string> table {
			{sb::Image::StoreOp::DontCare, "DontCare"},
			{sb::Image::StoreOp::Store, "Store"}
		};

		return "sb::Image::StoreOp"_t >> Vd(table.at(storeOp));
	}

	static auto imageLayoutToValue(sb::Image::Layout layout)
	{
		static const std::map<sb::Image::Layout, std::string> table {
			{sb::Image::Layout::Undefined, "Undefined"},
			{sb::Image::Layout::General, "General"},
			{sb::Image::Layout::ColorAttachmentOptimal, "ColorAttachmentOptimal"},
			{sb::Image::Layout::DepthStencilAttachmentOptimal, "DepthStencilAttachmentOptimal"},
			{sb::Image::Layout::DepthStencilReadOnlyOptimal, "DepthStencilReadOnlyOptimal"},
			{sb::Image::Layout::ShaderReadOnlyOptimal, "ShaderReadOnlyOptimal"},
			{sb::Image::Layout::TransferSrcOptimal, "TransferSrcOptimal"},
			{sb::Image::Layout::TransferDstOptimal, "TransferDstOptimal"},
			{sb::Image::Layout::Preinitialized, "Preinitialized"},
			{sb::Image::Layout::PresentSrc, "PresentSrc"}
		};

		return "sb::Image::Layout"_t >> Vd(table.at(layout));
	}

	static auto attachmentLayoutToBrace(const sb::RenderPass::Compiler::AttachmentLayout &attlay)
	{
		return B {attlay.attachment.getNdx(), imageLayoutToValue(attlay.layout)};
	}

	static auto pipelineStagesToBrace(const std::set<sb::PipelineStage> &stages)
	{
		static const std::map<sb::PipelineStage, std::string> table {
			{sb::PipelineStage::TopOfPipe, "TopOfPipe"},
			{sb::PipelineStage::DrawIndirect, "DrawIndirect"},
			{sb::PipelineStage::VertexInput, "VertexInput"},
			{sb::PipelineStage::VertexShader, "VertexShader"},
			{sb::PipelineStage::TesselationControlShader, "TesselationControlShader"},
			{sb::PipelineStage::TesselationEvaluationShader, "TesselationEvaluationShader"},
			{sb::PipelineStage::GeometryShader, "GeometryShader"},
			{sb::PipelineStage::FragmentShader, "FragmentShader"},
			{sb::PipelineStage::EarlyFragmentTests, "EarlyFragmentTests"},
			{sb::PipelineStage::LateFragmentTests, "LateFragmentTests"},
			{sb::PipelineStage::ColorAttachmentOutput, "ColorAttachmentOutput"},
			{sb::PipelineStage::ComputeShader, "ComputeShader"},
			{sb::PipelineStage::Transfer, "Transfer"},
			{sb::PipelineStage::BottomOfPipe, "BottomOfPipe"}
		};

		if (stages.size() == 0)
			return "sb::PipelineStage::None"_v;
		auto res = ""_v;
		auto first = true;
		for (auto &s : stages) {
			auto cur = "sb::PipelineStage"_t >> Vd(table.at(s));
			if (first) {
				res.assign(cur);
				first = false;
			} else
				res.assign(res | cur);
		}
		return res;
	}

	static auto accessToBrace(const std::set<sb::Access> &access)
	{
		static const std::map<sb::Access, std::string> table {
			{sb::Access::IndirectCommandRead, "IndirectCommandRead"},
			{sb::Access::IndexRead, "IndexRead"},
			{sb::Access::VertexAttributeRead, "VertexAttributeRead"},
			{sb::Access::UniformRead, "UniformRead"},
			{sb::Access::InputAttachmentRead, "InputAttachmentRead"},
			{sb::Access::ShaderRead, "ShaderRead"},
			{sb::Access::ShaderWrite, "ShaderWrite"},
			{sb::Access::ColorAttachmentRead, "ColorAttachmentRead"},
			{sb::Access::ColorAttachmentWrite, "ColorAttachmentWrite"},
			{sb::Access::DepthStencilAttachmentRead, "DepthStencilAttachmentRead"},
			{sb::Access::DepthStencilAttachmentWrite, "DepthStencilAttachmentWrite"},
			{sb::Access::TransferRead, "TransferRead"},
			{sb::Access::TransferWrite, "TransferWrite"},
			{sb::Access::HostRead, "HostRead"},
			{sb::Access::HostWrite, "HostWrite"},
			{sb::Access::MemoryRead, "MemoryRead"},
			{sb::Access::MemoryWrite, "MemoryWrite"}
		};

		if (access.size() == 0)
			return "sb::Access::None"_v;
		auto res = ""_v;
		auto first = true;
		for (auto &s : access) {
			auto cur = "sb::Access"_t >> Vd(table.at(s));
			if (first) {
				res.assign(cur);
				first = false;
			} else
				res.assign(res | cur);
		}
		return res;
	}

	static auto dependencyFlagsToBrace(const std::set<sb::DependencyFlag> &flags)
	{
		static const std::map<sb::DependencyFlag, std::string> table {
			{sb::DependencyFlag::ByRegion, "ByRegion"}
		};

		if (flags.size() == 0)
			return "sb::DependencyFlag::None"_v;
		auto res = ""_v;
		auto first = true;
		for (auto &s : flags) {
			auto cur = "sb::DependencyFlag"_t >> Vd(table.at(s));
			if (first) {
				res.assign(cur);
				first = false;
			} else
				res.assign(res | cur);
		}
		return res;
	}

	Type addRenderPass(Util::CollectionBase &scope, const sb::Resource::Compiler::modules_entry &entry)
	{
		static const Type rp_type("sb::rs::RenderPass");
		sb::RenderPass::Compiler compiled(entry);

		auto &rp = scope += Class | (entry.getId() + std::string("_class")) | C(Public | rp_type) | S {Public};
		auto ctor_fwd = rp += Ctor(Void);
		m_impl_out += ctor_fwd(Void) | S {};
		auto dtor_fwd = rp += Dtor(Void);
		m_impl_out += dtor_fwd(Void) | S {};

		auto attb = B {};
		for (auto &ap : compiled.getAttachments()) {
			auto &a = ap.second.get();
			attb.add(B {
				"sb::Format"_t >> Type(a.getFormat()),
				loadOpToValue(a.getLoadOp()),
				storeOpToValue(a.getStoreOp()),
				imageLayoutToValue(a.getInLayout()),
				imageLayoutToValue(a.getOutLayout())
			});
		}

		auto subb = B {};
		for (auto &sp : compiled.getSubpasses()) {
			auto &s = sp.second.get();
			auto inb = B {};
			for (auto &in : s.getIn())
				inb.add(attachmentLayoutToBrace(in.get()));
			auto outb = B {};
			for (auto &c : s.getOut())
				outb.add(B {attachmentLayoutToBrace(c.attachment), Value(B {c.resolve ? attachmentLayoutToBrace(*c.resolve) : Value(Vd("std::nullopt"))})});
			auto depthv = Value(B {s.getDepthStencil() ? attachmentLayoutToBrace(*s.getDepthStencil()) : Value(Vd("std::nullopt"))});
			auto preb = B {};
			for (auto &p : s.getPreserve())
				preb.add(p.get().getNdx());
			subb.add(B {inb, outb, depthv, preb});
		}

		auto depb = B {};
		for (auto &d : compiled.getDependencies())
			depb.add(B {
				d.getSrcSubpass().getNdx(),
				d.getDstSubpass().getNdx(),
				pipelineStagesToBrace(d.getSrcStages()),
				pipelineStagesToBrace(d.getDstStages()),
				accessToBrace(d.getSrcAccess()),
				accessToBrace(d.getDstAccess()),
				dependencyFlagsToBrace(d.getFlags())
			});

		auto rplayout = "sb::RenderPass::Layout"_t;

		auto layout_fwd = rp += Virtual | rplayout | Id("layout")(Void) | Const | Override;
		m_impl_out += rplayout | layout_fwd(Void) | Const | S
		{
			Return | B {attb, subb, depb}
		};

		rp += Static | "sb::RenderPass::Loaded"_t.T(rp) | Id("loaded")(Void) | S
		{
			"throw"_v
		};

		auto &fb_s = rp += Struct | "Framebuffer" | S {};
		auto &fb_runtime = fb_s +=
		Template(Typename | "Up") ||
		Class | "Runtime" | S
		{
			"sb::Framebuffer"_t | &N | Id("fb")(Void) | S
			{
				Return | StaticCast("Up"_t | &N, *This)
			},
		Public,
			Ctor(Void) | S
			{
			}
		};

		auto &render = fb_runtime +=
		Template() ||
		Void | Id("render")("sb::CommandBuffer"_t | &N | Id("cmd"), Const | "sb::srect2"_t | &N | Id("renderArea")) | S
		{
			"sb::ClearValue"_t[compiled.getAttachments().size()] | Id("clearValues")
		};
		for (auto &a : compiled.getAttachments()) {
			auto &att = a.second.get();
			if (att.getLoadOp() == sb::Image::LoadOp::Clear) {
				static const std::set<std::string> depthFmts {
					"d16_unorm",
					"d32_sfloat",

					"d24un_or_32sf_spl_att",
					"d32sf_or_24un_spl_att",

					"d24un_or_32sf_spl_att_sfb",
					"d32sf_or_24un_spl_att_sfb"
				};
				static const std::set<std::string> stencilFmts {
				};
				static const std::set<std::string> depthStencilFmts {
					"d24un_or_32sf_spl_att_s8_uint",
					"d32sf_or_24un_spl_att_s8_uint"
				};

				auto &fmt = att.getFormat();
				if (depthFmts.find(fmt) != depthFmts.end()) {
					render *= Float | att.getName();
					render += Value("clearValues"_v[a.first].M("depthStencil"_v.M("depth"_v))) = Vd(att.getName());
				} else if (stencilFmts.find(fmt) != stencilFmts.end()) {
					render *= Uint32_t | att.getName();
					render += Value("clearValues"_v[a.first].M("depthStencil"_v.M("stencil"_v))) = Vd(att.getName());
				} else if (depthStencilFmts.find(fmt) != depthStencilFmts.end()) {
					render *= Const | "sb::DepthStencil"_t | &N | Id(att.getName());
					render += Value("clearValues"_v[a.first].M("depthStencil"_v)) = Vd(att.getName());
				} else {
					render *= Const | "sb::Color"_t | &N | att.getName();
					render += Value("clearValues"_v[a.first].M("color"_v)) = Vd(att.getName());
				}
			}
		}

		{
			bool first = true;
			for (auto &s : compiled.getSubpasses()) {
				auto &sub = s.second.get();
				auto type = sub.getName() + std::string("_t");
				render <<= Typename | type;
				render *= Type(type) | & &N | Id(sub.getName());

				if (first) {
					render += "cmd"_v.M("beginRenderPassCmds"_v)("fb"_v(), "renderArea"_v, compiled.getAttachments().size(), "clearValues"_v, "std::forward"_t.T(Type(type))(Id(sub.getName())));
					first = false;
				} else {
					render += "cmd"_v.M("nextSubpassCmds"_v)("std::forward"_t.T(Type(type))(Id(sub.getName())));
				}
			}
		}

		render += "cmd"_v.M("endRenderPass"_v());

		auto &runtime = rp +=
		Template(Typename | "Up") ||
		Class | "Runtime" | S
		{
			Auto | &N | Id("ref")(Void) | S
			{
				Return | **"sb::RenderPass::RefGetter"_t.T("sb::RenderPass::CacheRefHolder"_t)(StaticCast("Up"_t | &N, *This)).M("get"_v())
			},
		Public,
			Ctor(Void) | S
			{
			}
		};
		auto fb_t = runtime += Using | "Framebuffer" = "sb::Framebuffer::Handle"_t.T(rp);
		auto &fb = runtime +=
		Auto | Id("framebuffer")(Const | "sb::svec2"_t | &N | Id("extent"), Size_t | Id("layers")) | S {};
		auto init_images = B {};
		for (auto &a : compiled.getAttachments()) {
			auto &att = a.second.get();
			fb *= "sb::Image"_t | &N | Id(att.getName());
			init_images.add(&Vd(att.getName()));
		}
		fb += "sb::Image"_t | *N[compiled.getAttachments().size()] | Id("images_vla") = init_images;
		fb += Return | fb_t("ref"_v().M("createFramebuffer"_v("extent"_v, "layers"_v, compiled.getAttachments().size(), "images_vla"_v)));

		auto &subpasses = runtime += Struct | "Subpass" | S {};
		for (auto &s : compiled.getSubpasses()) {
			auto &sub = s.second.get();
			subpasses += Struct | sub.getName() | S
			{
				Using | "RenderPass" = rp,
				Static | Inline | Constexpr | Auto | Id("index") = sub.getNdx()
			};
		}

		return rp;
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

	void it_dir(sb::Resource::Compiler::modules_entry &dir, Util::CollectionBase &scope, Util::CollectionFunctionBase &ctor)
	{
		auto dtor_fwd = scope += Dtor(Void) | Override;
		m_impl_out += dtor_fwd(Void) | S{};

		std::map<std::string, std::fs::path> entries;

		for (auto &e : std::fs::directory_iterator(dir.getPath())) {
			auto &path = e.path();
			auto name = path.filename().string();
			if (name.at(0) == '.')
				continue;

			entries[name] = path;
		}

		for (auto &ep : entries)
			dir.addChild(ep.second);

		for (auto &e : dir.getChildren()) {
			if (e.isDirectory()) {
				auto &cl = scope += Class | class_name(e.getId()) | C(Public | "sb::rs::Folder"_t) | S{};
				addgetterstorage(scope, ctor, cl, e.getId(), e.getName());
				cl += Public;
				auto ctor_fwd = cl += Ctor(Void);
				auto &ctor_sub = m_impl_out += ctor_fwd(Void) | S{};
				it_dir(e, cl, ctor_sub);
			} else {
				auto got = getMember(e.getPath());
				if (got) {
					auto type = *got;
					auto t = Type(type);

					if (type == "sb::rs::Shader") {
						try {
							t.assign(addShader(scope, e));
						} catch (const std::exception &excep) {
							throw FileError(type, e.getPath().string(), excep.what());
						}
					} else if (type == "sb::rs::RenderPass") {
						try {
							t.assign(addRenderPass(scope, e));
						} catch (const std::exception &excep) {
							throw FileError(type, e.getPath().string(), excep.what());
						}
					}
					addgetterstorage(scope, ctor, t, e.getId(), e.getName());
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

		auto dir = sb::Resource::Compiler::modules_entry(nullptr, root);
		it_dir(dir, cl, ctor);

		auto var = scope += Extern | cl | Id(fname);
		m_impl_out += cl | var;
	}

public:
	FolderPrinter(Util::CollectionBase &scope, Util::CollectionBase &impl_out, Util::CollectionBase &out, const std::string &root) :
		m_scope(scope),
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
			Pp::Include | "Subtile/Device.hpp",
			Pp::Include | "Subtile/Resource/Folder.hpp",
			Pp::Include | "Subtile/Resource/Model.hpp",
			Pp::Include | "Subtile/Resource/Image.hpp",
			Pp::Include | "Subtile/Resource/Shader.hpp",
			Pp::Include | "Subtile/Resource/RenderPass.hpp"
		};

		Out impl(implpath, true);

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