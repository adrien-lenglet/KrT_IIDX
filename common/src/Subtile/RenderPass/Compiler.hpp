#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <set>
#include <map>
#include "../Resource/Compiler.hpp"
#include "../RenderPass.hpp"
#include "cpp_generator.hpp"
#include "util.hpp"
#include "util/string.hpp"
#include "util/sstream.hpp"

namespace Subtile {

class RenderPass::Compiler
{
	using tstream = rs::Compiler::token_stream;

	const rs::Compiler::modules_entry &m_entry;

	class Attachment
	{
		size_t m_ndx;
		std::string m_format;
		std::string m_name;
		Image::LoadOp m_load_op;
		Image::StoreOp m_store_op;
		Image::Layout m_in_layout;
		Image::Layout m_out_layout;

		bool continue_list(tstream &s, bool force_next)
		{
			auto is_end = s.peek() == "}";
			if (force_next && is_end)
				throw std::runtime_error(std::string("Has ',' and '}' tokens on end of attachment '") + m_name + std::string("' attributes"));
			return force_next || !is_end;
		}

		auto pollLoadOp(const std::string &str)
		{
			std::map<std::string, Image::LoadOp> table {
				{"dont_care", Image::LoadOp::DontCare},
				{"load", Image::LoadOp::Load},
				{"clear", Image::LoadOp::Clear}
			};

			auto got = table.find(str);
			if (got == table.end()) {
				std::stringstream ss;
				ss << "Unkwown load op '" << str << "' for attachment '" << m_name << "'";
				throw std::runtime_error(ss.str());
			}
			return got->second;
		}

		auto pollStoreOp(const std::string &str)
		{
			std::map<std::string, Image::StoreOp> table {
				{"dont_care", Image::StoreOp::DontCare},
				{"store", Image::StoreOp::Store}
			};

			auto got = table.find(str);
			if (got == table.end()) {
				std::stringstream ss;
				ss << "Unkwown store op '" << str << "' for attachment '" << m_name << "'";
				throw std::runtime_error(ss.str());
			}
			return got->second;
		}

		auto pollLayout(const std::string &str)
		{
			std::map<std::string, Image::Layout> table {
				{"undefined", Image::Layout::Undefined},
				{"color_attachment_optimal", Image::Layout::ColorAttachmentOptimal},
				{"depth_stencil_attachment_optimal", Image::Layout::DepthStencilAttachmentOptimal},
				{"depth_stencil_read_only_optimal", Image::Layout::DepthStencilReadOnlyOptimal},
				{"shader_read_only_optimal", Image::Layout::ShaderReadOnlyOptimal},
				{"transfer_src_optimal", Image::Layout::TransferSrcOptimal},
				{"transfer_dst_optimal", Image::Layout::TransferDstOptimal},

				{"preinitialized", Image::Layout::Preinitialized},

				{"present_src", Image::Layout::PresentSrc}
			};

			auto got = table.find(str);
			if (got == table.end()) {
				std::stringstream ss;
				ss << "Unkwown image layout '" << str << "' for attachment '" << m_name << "'";
				throw std::runtime_error(ss.str());
			}
			return got->second;
		}

		void poll_attrs(tstream &s)
		{
			s.expect("{");
			bool force_next = false;
			while (continue_list(s, force_next)) {
				auto &attr = s.poll();

				if (s.peek() == ",") {
					if (attr == "load")
						m_load_op = Image::LoadOp::Load;
					else if (attr == "store")
						m_store_op = Image::StoreOp::Store;
					else {
						std::stringstream ss;
						ss << "Unkwown single attribute type '" << attr << "' for attachment '" << m_name << "': 'load' or 'store' expected";
						throw std::runtime_error(ss.str());
					}
				} else {
					s.expect("=");
					auto &val = s.poll();

					if (attr == "load")
						m_load_op = pollLoadOp(val);
					else if (attr == "store")
						m_store_op = pollStoreOp(val);
					else if (attr == "in_layout")
						m_in_layout = pollLayout(val);
					else if (attr == "out_layout")
						m_out_layout = pollLayout(val);
					else {
						std::stringstream ss;
						ss << "Unkwown attribute type '" << attr << "' for attachment '" << m_name << "': 'load', 'store', 'in_layout' or 'out_layout' expected";
						throw std::runtime_error(ss.str());
					}
				}

				if (s.peek() == ",") {
					force_next = true;
					s.poll();
				} else
					force_next = false;
			}
			s.poll();
		}

	public:
		Attachment(tstream &s, size_t ndx) :
			m_ndx(ndx),
			m_format(s.poll()),
			m_name(s.poll()),
			m_load_op(Image::LoadOp::DontCare),
			m_store_op(Image::StoreOp::DontCare),
			m_in_layout(Image::Layout::Undefined),
			m_out_layout(Image::Layout::Undefined)
		{
			if (s.peek() == "{")
				poll_attrs(s);
			s.expect(";");
		}

		auto getNdx(void) const { return m_ndx; }
		auto& getFormat(void) const { return m_format; }
		auto& getName(void) const { return m_name; }
		auto getLoadOp(void) const { return m_load_op; }
		auto getStoreOp(void) const { return m_store_op; }
		auto getInLayout(void) const { return m_in_layout; }
		auto getOutLayout(void) const { return m_out_layout; }
	};

	std::map<std::string, Attachment> m_attachments;
	void parseAttachment(tstream &s)
	{
		auto a = Attachment(s, m_attachments.size());
		m_attachments.emplace(std::piecewise_construct, std::forward_as_tuple(a.getName()), std::forward_as_tuple(std::move(a)));
	}

	std::map<size_t, util::ref_wrapper<Attachment>> m_attachments_ordered;

	auto getAttachmentsOrdered(void)
	{
		std::map<size_t, util::ref_wrapper<Attachment>> res;

		for (auto &ap : m_attachments)
			res.emplace(ap.second.getNdx(), ap.second);
		return res;
	}

public:
	auto& findAttachment(const std::string &name)
	{
		auto got = m_attachments.find(name);
		if (got == m_attachments.end()) {
			std::stringstream ss;
			ss << "Unkwown attachment '" << name << "'";
			throw std::runtime_error(ss.str());
		}
		return got->second;
	}

	struct AttachmentLayout
	{
	public:
		AttachmentLayout(Attachment &attachment, Image::Layout layout) :
			attachment(attachment),
			layout(layout)
		{
		}

		Attachment &attachment;
		Image::Layout layout;
	};

private:
	class Subpass
	{
		size_t m_ndx;
		std::string m_name;

		enum class AttachmentUsage
		{
			In,
			Out,
			DepthStencil,
			Resolve
		};

		std::map<util::ref_wrapper<Attachment>, AttachmentLayout> m_attachment_layouts;

		Image::Layout attUsageToLayout(Attachment &attachment, AttachmentUsage usage)
		{
			if (attachment.getFormat().at(0) == 'd') {
				if (usage == AttachmentUsage::In)
					return Image::Layout::DepthStencilReadOnlyOptimal;
				else if (usage == AttachmentUsage::Out) {
					std::stringstream ss;
					ss << "Can't use attachment with depth format '" << attachment.getName() << "' as color attachment for subpass '" << m_name << "'";
					throw std::runtime_error(ss.str());
				} else if (usage == AttachmentUsage::Resolve) {
					std::stringstream ss;
					ss << "Can't use attachment with depth format '" << attachment.getName() << "' as resolve attachment for subpass '" << m_name << "'";
					throw std::runtime_error(ss.str());
				} else if (usage == AttachmentUsage::DepthStencil)
					return Image::Layout::DepthStencilAttachmentOptimal;
			} else {
				if (usage == AttachmentUsage::In)
					return Image::Layout::ShaderReadOnlyOptimal;
				else if (usage == AttachmentUsage::Out)
					return Image::Layout::ColorAttachmentOptimal;
				else if (usage == AttachmentUsage::Resolve)
					return Image::Layout::ColorAttachmentOptimal;
				else if (usage == AttachmentUsage::DepthStencil) {
					std::stringstream ss;
					ss << "Can't use attachment with color format '" << attachment.getName() << "' as depth_stencil attachment for subpass '" << m_name << "'";
					throw std::runtime_error(ss.str());
				}
			}
			throw std::runtime_error("Unkown attachment usage");
		}

		AttachmentLayout& attLayout(Attachment &attachment, AttachmentUsage usage)
		{
			auto got = m_attachment_layouts.find(attachment);
			if (got == m_attachment_layouts.end()) {
				auto [it, suc] = m_attachment_layouts.emplace(std::piecewise_construct, std::forward_as_tuple(attachment), std::forward_as_tuple(attachment, attUsageToLayout(attachment, usage)));
				if (!suc)
					throw std::runtime_error("Can't emplace attachment layout");
				got = it;
			}
			return got->second;
		}

		AttachmentLayout *m_depth_stencil = nullptr;
		std::vector<util::ref_wrapper<AttachmentLayout>> m_in;

		struct Out
		{
			Out(AttachmentLayout &attachment, AttachmentLayout *resolve = nullptr) :
				attachment(attachment),
				resolve(resolve)
			{
			}

			AttachmentLayout &attachment;
			AttachmentLayout *resolve;
		};
		std::vector<Out> m_out;
		std::vector<util::ref_wrapper<Attachment>> m_preserve;

		void check_not_preserved(Attachment &attachment)
		{
			for (auto &p : m_preserve)
				if (&p.get() == &attachment) {
					std::stringstream ss;
					ss << "Illegal usage of preserved attachment '" << attachment.getName() << "' for subpass '" << m_name << "'";
					throw std::runtime_error(ss.str());
				}
		}

	public:
		Subpass(tstream &s, size_t ndx, Compiler &compiler) :
			m_ndx(ndx),
			m_name(s.poll())
		{
			s.expect("{");
			while (s.peek() != "}") {
				auto &qual = s.poll();
				auto &id = s.poll();
				auto &att = compiler.findAttachment(id);

				if (qual == "depth_stencil") {
					if (m_depth_stencil) {
						std::stringstream ss;
						ss << "Depth stencil '" << m_depth_stencil->attachment.getName() << "' already present for subpass '" << m_name << "'";
						throw std::runtime_error(ss.str());
					}
					m_depth_stencil = &attLayout(att, AttachmentUsage::DepthStencil);
					check_not_preserved(m_depth_stencil->attachment);
					s.expect(";");
				} else if (qual == "in") {
					/*for (auto &i : m_in)
						if (i.get().getName() == id) {
							std::stringstream ss;
							ss << "Redefinition of input '" << id << "' for subpass '" << m_name << "'";
							throw std::runtime_error(ss.str());
						}*/
					m_in.emplace_back(attLayout(att, AttachmentUsage::In));
					check_not_preserved(att);
					s.expect(";");
				} else if (qual == "out") {
					/*for (auto &o : m_out)
						if (o.attachment.getName() == id) {
							std::stringstream ss;
							ss << "Redefinition of output '" << id << "' for subpass '" << m_name << "'";
							throw std::runtime_error(ss.str());
						}*/
					m_out.emplace_back(attLayout(att, AttachmentUsage::Out));
					check_not_preserved(att);
					s.expect(";");
				} else if (qual == "preserve") {
					if (m_attachment_layouts.find(att) != m_attachment_layouts.end()) {
						std::stringstream ss;
						ss << "Attachment '" << id << "' is already used in subpass '" << m_name << "' and cannot be preserved";
						throw std::runtime_error(ss.str());	
					}
					for (auto &o : m_preserve)
						if (o.get().getName() == id) {
							std::stringstream ss;
							ss << "Redefinition of preserve '" << id << "' for subpass '" << m_name << "'";
							throw std::runtime_error(ss.str());
						}
					m_preserve.emplace_back(att);
					s.expect(";");
				} else if (qual == "resolve") {
					s.expect(":");
					auto &dst = s.poll();
					bool found = false;
					for (auto &o : m_out)
						if (o.attachment.attachment.getName() == id) {
							auto &att = compiler.findAttachment(dst);
							o.resolve = &attLayout(att, AttachmentUsage::Resolve);
							check_not_preserved(att);
							found = true;
						}
					if (!found) {
						std::stringstream ss;
						ss << "No output '" << id << "found to resolve '" << dst << "' on subpass '" << m_name << "'";
						throw std::runtime_error(ss.str());
					}
					s.expect(";");
				}
			}
			s.poll();
		}

		auto getNdx(void) const { return m_ndx; }
		auto& getName(void) const { return m_name; }
		auto& getIn(void) const { return m_in; }
		auto& getOut(void) const { return m_out; }
		auto& getDepthStencil(void) const { return m_depth_stencil; }
		auto& getPreserve(void) const { return m_preserve; }
	};

	std::map<std::string, Subpass> m_subpasses;
	void parseSubpass(tstream &s)
	{
		auto a = Subpass(s, m_subpasses.size(), *this);
		m_subpasses.emplace(std::piecewise_construct, std::forward_as_tuple(a.getName()), std::forward_as_tuple(std::move(a)));
	}
	std::map<size_t, util::ref_wrapper<Subpass>> m_subpasses_ordered;

	auto getSubpassesOrdered(void)
	{
		std::map<size_t, util::ref_wrapper<Subpass>> res;

		for (auto &sp : m_subpasses)
			res.emplace(sp.second.getNdx(), sp.second);
		return res;
	}

public:
	auto& getSubpass(const std::string &id)
	{
		auto got = m_subpasses.find(id);
		if (got == m_subpasses.end()) {
			std::stringstream ss;
			ss << "Can't find subpass '" << id << "'";
			throw std::runtime_error(ss.str());
		}
		return got->second;
	}

private:
	class Dependency
	{
		Subpass &m_src_subpass;
		Subpass &m_dst_subpass;
		std::set<PipelineStage> m_src_stages;
		std::set<PipelineStage> m_dst_stages;
		std::set<Access> m_src_access;
		std::set<Access> m_dst_access;

		static auto& getPipelineTable(void)
		{
			static const std::map<std::string, PipelineStage> table {
				{"top_of_pipe", PipelineStage::TopOfPipe},
				{"draw_indirect", PipelineStage::DrawIndirect},
				{"vertex_input", PipelineStage::VertexInput},
				{"vertex_shader", PipelineStage::VertexShader},
				{"tesselation_control_shader", PipelineStage::TesselationControlShader},
				{"tesselation_evaluation_shader", PipelineStage::TesselationEvaluationShader},
				{"geometry_shader", PipelineStage::GeometryShader},
				{"fragment_shader", PipelineStage::FragmentShader},
				{"early_fragment_tests", PipelineStage::EarlyFragmentTests},
				{"late_fragment_tests", PipelineStage::LateFragmentTests},
				{"color_attachment_output", PipelineStage::ColorAttachmentOutput},
				{"compute_shader", PipelineStage::ComputeShader},
				{"transfer", PipelineStage::Transfer},
				{"bottom_of_pipe", PipelineStage::BottomOfPipe}
			};

			return table;
		}

		static auto& getAccessTable(void)
		{
			static const std::map<std::string, Access> table {
				{"indirect_command_read", Access::IndirectCommandRead},
				{"index_read", Access::IndexRead},
				{"vertex_attribute_read", Access::VertexAttributeRead},
				{"uniform_read", Access::UniformRead},
				{"input_attachment_read", Access::InputAttachmentRead},
				{"shader_read", Access::ShaderRead},
				{"shader_write", Access::ShaderWrite},
				{"color_attachment_read", Access::ColorAttachmentRead},
				{"color_attachment_write", Access::ColorAttachmentWrite},
				{"depth_stencil_attachment_read", Access::DepthStencilAttachmentRead},
				{"depth_stencil_attachment_write", Access::DepthStencilAttachmentWrite},
				{"transfer_read", Access::TransferRead},
				{"transfer_write", Access::TransferWrite},
				{"host_read", Access::HostRead},
				{"host_write", Access::HostWrite},
				{"memory_read", Access::MemoryRead},
				{"memory_write", Access::MemoryWrite}
			};

			return table;
		}

		template <typename MaskType>
		auto pollMask(tstream &s, const std::map<std::string, MaskType> &table, const std::string &value_name)
		{
			std::set<MaskType> res;

			if (s.peek() == ",")
				s.poll();
			else
				return res;
			bool has_value = false;
			while (!(s.peek() == "]" || s.peek() == ",")) {
				auto &got = s.poll();
				if (has_value) {
					if (got != "|") {
						std::stringstream ss;
						ss << "Expected | but got '" << got << "' in dependency member " << value_name;
						throw std::runtime_error(ss.str());
					}
					has_value = false;
					continue;
				}
				if (got == "0")
					has_value = true;
				else {
					auto found = table.find(got);
					if (found == table.end()) {
						std::stringstream ss;
						ss << "Unkown mask '" << got << "' in dependency member " << value_name;
						throw std::runtime_error(ss.str());
					}
					if (res.find(found->second) != res.end()) {
						std::stringstream ss;
						ss << "Duplicate of mask '" << got << "' in dependency member " << value_name;
						throw std::runtime_error(ss.str());
					}
					res.emplace(found->second);
					has_value = true;
				}
			}
			if (!has_value) {
				std::stringstream ss;
				ss << "Expected expression near '" << s.peek() << "' in dependency member " << value_name;
				throw std::runtime_error(ss.str());
			}
			return res;
		}

	public:
		Dependency(tstream &s, Compiler &compiler) :
			m_src_subpass((s.expect("["), compiler.getSubpass(s.poll()))),
			m_dst_subpass((s.expect(","), compiler.getSubpass(s.poll()))),
			m_src_stages(pollMask(s, getPipelineTable(), "srcStageMask (PipelineStage)")),
			m_dst_stages(pollMask(s, getPipelineTable(), "dstStageMask (PipelineStage)")),
			m_src_access(pollMask(s, getAccessTable(), "srcAccessMask (Access)")),
			m_dst_access(pollMask(s, getAccessTable(), "dstAccessMask (Access)"))
		{
			s.expect("]");
		}

		auto& getSrcSubpass(void) const { return m_src_subpass; }
		auto& getDstSubpass(void) const { return m_dst_subpass; }
		auto& getSrcStages(void) const { return m_src_stages; }
		auto& getDstStages(void) const { return m_dst_stages; }
		auto& getSrcAccess(void) const { return m_src_access; }
		auto& getDstAccess(void) const { return m_dst_access; }
	};
	std::vector<Dependency> m_dependencies;
	void parseDependency(tstream &s)
	{
		m_dependencies.emplace_back(s, *this);
	}

	void parse(tstream &s)
	{
		while (!s.is_end()) {
			auto [f, sec] = s.peek2();
			if (sec == "{")
				parseSubpass(s);
			else if (f == "[")
				parseDependency(s);
			else
				parseAttachment(s);
		}
	}

public:
	auto& getModuleEntry(void) const
	{
		return m_entry;
	}

	Compiler(const rs::Compiler::modules_entry &entry) :
		m_entry(entry)
	{
		auto stream = tstream::tokenize(rs::Compiler::read(entry.getPath().string()));
		parse(stream);
		m_attachments_ordered = getAttachmentsOrdered();
		m_subpasses_ordered = getSubpassesOrdered();
	}

	auto& getAttachments(void) const { return m_attachments_ordered; }
	auto& getSubpasses(void) const { return m_subpasses_ordered; }
	auto& getDependencies(void) const { return m_dependencies; }
};

}