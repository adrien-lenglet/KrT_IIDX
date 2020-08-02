#pragma once

#include <set>
#include <map>
#include <vector>
#include <memory>
#include "Subtile/Math.hpp"
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>
#include "util/bin.hpp"

namespace Subtile {

class ISystem;

class Shader
{
public:
	virtual ~Shader(void) = default;

	enum class Stage {
		TesselationControl,
		TesselationEvaluation,
		Geometry,
		Vertex,
		Fragment
	};

	struct VertexInput
	{
		enum class Format
		{
			Bool,
			Int,
			Uint,
			Float,
			Double,

			Vec2,
			Vec3,
			Vec4,

			Bvec2,
			Bvec3,
			Bvec4,

			Ivec2,
			Ivec3,
			Ivec4,

			Uvec2,
			Uvec3,
			Uvec4,

			Dvec2,
			Dvec3,
			Dvec4
		};

		struct Attribute
		{
			Format format;
			size_t offset;
			size_t location;
		};

		size_t size;
		std::vector<Attribute> attributes;

		class Creator
		{
		public:
			template <typename V>
			Creator(V &&vertex, VertexInput &res) :
				m_base(&vertex),
				m_loc_acc(0),
				m_attributes(res.attributes)
			{
			}

			void addAttr(const void *ptr, Format format)
			{
				m_attributes.emplace_back(Attribute {format, reinterpret_cast<size_t>(ptr) - reinterpret_cast<size_t>(m_base), m_loc_acc});
				if (format == Format::Dvec3 || format == Format::Dvec4)
					m_loc_acc += 2;
				else
					m_loc_acc += 1;
			}

		private:
			void *m_base;
			size_t m_loc_acc;
			std::vector<Attribute> &m_attributes;
		};
	};

	struct Type {

		class Bool : public util::scalar<bool>, private util::pad<sizeof(uint32_t) - sizeof(bool)>
		{
		public:
			Bool(void) = default;
			template <typename ...Args>
			Bool(Args &&...args) :
				util::scalar<bool>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const
			{
				creator.addAttr(this, VertexInput::Format::Bool);
			}

			using salign = util::csize_t<sizeof(uint32_t)>;
			using balign = salign;
			using ealign = balign;

			using to_std = Bool;
		};

		class Int : public util::scalar<int32_t>
		{
		public:
			Int(void) = default;
			template <typename ...Args>
			Int(Args &&...args) :
				util::scalar<int32_t>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const
			{
				creator.addAttr(this, VertexInput::Format::Int);
			}

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;

			using to_std = int32_t;
		};

		class Uint : public util::scalar<uint32_t>
		{
		public:
			Uint(void) = default;
			template <typename ...Args>
			Uint(Args &&...args) :
				util::scalar<uint32_t>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const
			{
				creator.addAttr(this, VertexInput::Format::Uint);
			}

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;

			using to_std = uint32_t;
		};

		class Float : public util::scalar<float>
		{
		public:
			Float(void) = default;
			template <typename ...Args>
			Float(Args &&...args) :
				util::scalar<float>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const
			{
				creator.addAttr(this, VertexInput::Format::Float);
			}

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;

			using to_std = float;
		};

		class Double : public util::scalar<double>
		{
		public:
			Double(void) = default;
			template <typename ...Args>
			Double(Args &&...args) :
				util::scalar<double>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const
			{
				creator.addAttr(this, VertexInput::Format::Double);
			}

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;

			using to_std = double;
		};

		template <typename S, size_t Size>
		struct Vec;

		template <typename S>
		struct Vec<S, 2> : public glm::vec<2, typename S::to_std, glm::defaultp>
		{
			Vec(void) = default;
			template <typename ...Args>
			Vec(Args &&...args) :
				glm::vec<2, typename S::to_std, glm::defaultp>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const;

			using salign = typename S::salign;
			using balign = util::csize_t<salign{} * 2>;
			using ealign = balign;
		};

		template <typename S>
		struct Vec<S, 3> : public glm::vec<3, typename S::to_std, glm::defaultp>
		{
			Vec(void) = default;
			template <typename ...Args>
			Vec(Args &&...args) :
				glm::vec<3, typename S::to_std, glm::defaultp>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const;

			using salign = typename S::salign;
			using balign = util::csize_t<salign{} * 4>;
			using ealign = balign;
		};

		template <typename S>
		struct Vec<S, 4> : public glm::vec<4, typename S::to_std, glm::defaultp>
		{
			Vec(void) = default;
			template <typename ...Args>
			Vec(Args &&...args) :
				glm::vec<4, typename S::to_std, glm::defaultp>(std::forward<Args>(args)...)
			{
			}

			void createVertexInput(VertexInput::Creator &creator) const;

			using salign = typename S::salign;
			using balign = util::csize_t<salign{} * 4>;
			using ealign = balign;
		};

		struct Std140
		{
			template <typename T>
			struct ArrayPad : public T, private util::pad<util::align_v<sizeof(T), util::align_v<T::ealign::value, 16>> - sizeof(T)>
			{
				ArrayPad(void) = default;
				template <typename ...Args>
				ArrayPad(Args &&...args) :
					T(std::forward<Args>(args)...)
				{
				}
			};

			template <typename T>
			using align = typename T::ealign;
		};

		struct Std430
		{
			template <typename T>
			struct ArrayPad : public T, private util::pad<util::align_v<sizeof(T), T::balign::value> - sizeof(T)>
			{
				ArrayPad(void) = default;
				template <typename ...Args>
				ArrayPad(Args &&...args) :
					T(std::forward<Args>(args)...)
				{
				}
			};

			template <typename T>
			using align = typename T::balign;
		};

		template <typename T, size_t Size, class Layout>
		struct Array
		{
			Array(void) = default;

			auto& operator[](size_t ndx)
			{
				return m_values[ndx];
			}
			auto& operator[](size_t ndx) const
			{
				return m_values[ndx];
			}

			inline constexpr auto size(void) const
			{
				return Size;
			}

			class iterator
			{
			public:
				iterator(Array &array, size_t ndx = 0) :
					m_array(array),
					m_ndx(ndx)
				{
				}

				auto& operator++(void)
				{
					++m_ndx;
					return *this;
				}
				auto& operator--(void)
				{
					--m_ndx;
					return *this;
				}
				auto operator++(int)
				{
					auto res = *this;
					m_ndx++;
					return res;
				}
				auto operator--(int)
				{
					auto res = *this;
					m_ndx--;
					return res;
				}

				auto operator+(size_t off) { return iterator(m_array, m_ndx + off); }
				auto operator-(size_t off) { return iterator(m_array, m_ndx - off); }
				bool operator==(const iterator &other) { return m_ndx == other.m_ndx; }
				bool operator!=(const iterator &other) { return m_ndx != other.m_ndx; }
				auto& operator*(void) { return m_array[m_ndx]; }
				auto operator->(void) { return &m_array[m_ndx]; }

			private:
				Array &m_array;
				size_t m_ndx;
			};

			auto begin(void) { return iterator(*this); }
			auto end(void) { return iterator(*this, Size); }

			class const_iterator
			{
			public:
				const_iterator(const Array &array, size_t ndx = 0) :
					m_array(array),
					m_ndx(ndx)
				{
				}

				auto& operator++(void)
				{
					++m_ndx;
					return *this;
				}
				auto& operator--(void)
				{
					--m_ndx;
					return *this;
				}
				auto operator++(int)
				{
					auto res = *this;
					m_ndx++;
					return res;
				}
				auto operator--(int)
				{
					auto res = *this;
					m_ndx--;
					return res;
				}

				auto operator+(size_t off) { return const_iterator(m_array, m_ndx + off); }
				auto operator-(size_t off) { return const_iterator(m_array, m_ndx - off); }
				bool operator==(const const_iterator &other) { return m_ndx == other.m_ndx; }
				bool operator!=(const const_iterator &other) { return m_ndx != other.m_ndx; }
				auto& operator*(void) { return m_array[m_ndx]; }
				auto operator->(void) { return &m_array[m_ndx]; }

			private:
				const Array &m_array;
				size_t m_ndx;
			};

			auto begin(void) const { return const_iterator(*this); }
			auto end(void) const { return const_iterator(*this, Size); }
			auto cbegin(void) const { return begin(); }
			auto cend(void) const { return end(); }

			using salign = typename T::salign;
			using balign = typename T::balign;
			using ealign = util::csize_t<util::align_v<T::ealign::value, 16>>;

			using padded_type = typename Layout::template ArrayPad<T>;

			void createVertexInput(VertexInput::Creator &creator) const
			{
				for (auto &e : *this)
					e.createVertexInput(creator);
			}

		private:
			padded_type m_values[Size];
		};

		template <typename S, size_t C, size_t R, class Layout>
		class Mat : public Array<Vec<S, R>, C, Layout>
		{
			using col_type = Array<Vec<S, R>, C, Layout>;

		public:
			using glm_type = glm::mat<C, R, S, glm::defaultp>;

			Mat(void) = default;
			template <typename GlmS, glm::qualifier Q>
			Mat(const glm::mat<C, R, GlmS, Q> &glmmat)
			{
				for (size_t i = 0; i < C; i++)
					for (size_t j = 0; j < R; j++)
						(*this)[i][j] = glmmat[i][j];
			}

			using salign = typename S::salign;
			using balign = typename col_type::balign;
			using ealign = balign;
		};

	private:
		struct FirstStructMember
		{
			using salign = util::csize_t<1>;
			using balign = util::csize_t<1>;
			using ealign = util::csize_t<1>;
			using offset = util::csize_t<0>;
			using size = util::csize_t<0>;
			using offset_end = util::csize_t<0>;
		};

	public:
		template <typename T, typename Layout, typename PrevType = FirstStructMember>
		struct StructMember : private util::pad<util::align_v<PrevType::offset_end::value, Layout::template align<T>::value> - PrevType::offset_end::value>, public T
		{
			StructMember(void) = default;
			template <typename ...Args>
			StructMember(Args &&...args) :
				T(std::forward<Args>(args)...)
			{
			}

			using salign = typename T::salign;
			using balign = typename T::balign;
			using ealign = typename T::ealign;
			using offset = util::align<PrevType::offset_end::value, Layout::template align<T>::value>;
			using size = util::csize_t<sizeof(T)>;
			using type = T;
			using offset_end = util::csize_t<offset::value + sizeof(T)>;
		};

		template <typename Collection, typename ...Members>
		struct Struct : public Collection
		{
			Struct(void) = default;
			template <typename ...Args>
			Struct(Args &&...args) :
				Collection(std::forward<Args>(args)...)
			{
			}

		private:
			template <typename T>
			struct salign_getter : public T::salign {};
			template <typename T>
			struct balign_getter : public T::balign {};
			template <typename T>
			struct ealign_getter : public T::ealign {};

			template <template <typename T> typename Getter, typename ...Rest>
			struct get_align;

			template <template <typename T> typename Getter>
			struct get_align<Getter>
			{
			public:
				using type = util::csize_t<0>;
				static inline constexpr size_t value = type{};
			};

			template <template <typename T> typename Getter, size_t First>
			struct get_align<Getter, std::integral_constant<size_t, First>>
			{
			public:
				using type = util::csize_t<First>;
				static inline constexpr size_t value = type{};
			};

			template <template <typename T> typename Getter, typename First>
			struct get_align<Getter, First>
			{
			public:
				using type = Getter<First>;
				static inline constexpr size_t value = type{};
			};

			template <template <typename T> typename Getter, size_t First, typename Second, typename ...Rest>
			struct get_align<Getter, std::integral_constant<size_t, First>, Second, Rest...>
			{
			private:
				using Sval = Getter<Second>;
				static inline constexpr size_t res = util::csize::max_v<First, Sval::value>;

			public:
				using type = typename get_align<Getter, util::csize_t<res>, Rest...>::type;
				static inline constexpr size_t value = type{};
			};

			template <template <typename T> typename Getter, typename First, typename Second, typename ...Rest>
			struct get_align<Getter, First, Second, Rest...>
			{
			private:
				using Fval = Getter<First>;
				using Sval = Getter<Second>;
				static inline constexpr size_t res = util::csize::max_v<Fval::value, Sval::value>;

			public:
				using type = typename get_align<Getter, util::csize_t<res>, Rest...>::type;
				static inline constexpr size_t value = type{};
			};

			template <template <typename T> typename Getter, typename ...Rest>
			using get_align_t = typename get_align<Getter, Rest...>::type;

		public:
			using salign = get_align_t<salign_getter, Members...>;
			using balign = get_align_t<balign_getter, Members...>;
			using ealign = util::align_t<get_align_t<ealign_getter, Members...>{}, 16>;
		};
	};

	enum class Sbi {  // shader binary interface
		Vulkan
	};

	static const std::set<Sbi>& getSbi(void);

	class Compiler;

	enum class DescriptorType
	{
		UniformBuffer,
		CombinedImageSampler
	};

	static bool descriptorTypeIsMapped(DescriptorType type);

	class DescriptorSet
	{
	public:
		class Layout
		{
		public:
			class DescriptionBinding
			{
			public:
				size_t binding;
				size_t descriptorCount;	// buffer size when descriptorType is UniformBuffer
				DescriptorType descriptorType;
				std::set<Stage> stages;

				bool isMapped(void) const;
			};
			using Description = std::vector<DescriptionBinding>;

			virtual ~Layout(void) = default;

			class Inline;

			class Resolver
			{
			public:
				virtual ~Resolver(void) = default;

				virtual const Layout& resolve(void) const = 0;

				class Inline;
			};
		};

		virtual ~DescriptorSet(void) = default;

		virtual void write(size_t offset, size_t range, const void *data) = 0;
		//virtual void bindCombinedImageSampler(RImage &img) = 0;

		template <typename Traits>
		class Handle : public Traits::Mapped
		{
			using Mapped = typename Traits::Mapped;

		public:
			Handle(std::unique_ptr<DescriptorSet> &&desc_set) :
				m_set(std::move(desc_set))
			{
			}

			void upload(void)
			{
				m_set->write(0, sizeof(Mapped), &static_cast<Mapped&>(*this));
			}

		private:
			std::unique_ptr<DescriptorSet> m_set;
		};
	};

	//virtual std::unique_ptr<DescriptorSet> material(void) = 0;
	//virtual std::unique_ptr<DescriptorSet> object(void) = 0;

	class Model
	{
	public:
		virtual ~Model(void) = default;
	};

	virtual std::unique_ptr<Model> model(size_t count, size_t stride, const void *data) = 0;
	virtual std::unique_ptr<DescriptorSet> set(size_t ndx) = 0;

	/*
	template <typename ShaderRs>
	using Material = DescriptorSet::Handle<typename Shader::Rs::materialTraits>;
	template <typename ShaderRs>
	using Object = DescriptorSet::Handle<typename Shader::Rs::objectTraits>;
	*/
};

}

#include "Resource/File.hpp"
#include "Resource/Target.hpp"

namespace Subtile {
namespace Resource {

class Shader : public File
{
public:
	Shader(const std::set<sb::Shader::Stage> &stages);
	~Shader(void) override;

	virtual sb::Shader::VertexInput vertexInput(void) const = 0;
	using DescriptorSetLayouts = std::vector<std::unique_ptr<sb::Shader::DescriptorSet::Layout::Resolver>>;
	virtual DescriptorSetLayouts loadDescriptorSetLayouts(ISystem &sys) const = 0;

	class Stage
	{
		static const std::string& getStageName(sb::Shader::Stage stage);

	public:
		Stage(Folder &folder, sb::Shader::Stage stage);

		class Source : public File
		{
		public:
			static std::string getFileName(sb::Shader::Stage stage, sb::Shader::Sbi sbi);

			Source(sb::Shader::Stage stage, sb::Shader::Sbi sbi);

			decltype(auto) getPath(void) const
			{
				return File::getPath();
			}

		protected:
			static const std::string& getSbiName(sb::Shader::Sbi sbi);
		};

		class VkSource : public Source
		{
		public:
			VkSource(Folder &folder, sb::Shader::Stage stage, sb::Shader::Sbi sbi);

			class Compiled : public Target
			{
			public:
				Compiled(Source &src);

			protected:
				void build(std::ostream &o) const override;

			private:
				Source &m_src;
			};

			const Compiled& getCompiled(void) const;

		private:
			Compiled &m_compiled;

			static std::string getCompiledName(sb::Shader::Stage stage, sb::Shader::Sbi sbi);
		};

		const VkSource& getVk(void) const;

	private:
		VkSource &m_vk;
	};

	const std::map<sb::Shader::Stage, Stage>& getStages(void) const;

private:
	Folder &m_stages_folder;
	const std::map<sb::Shader::Stage, Stage> m_stages;

	std::map<sb::Shader::Stage, Stage> createStages(const std::set<sb::Shader::Stage> &stages);
};

}
}

#include "Subtile/ISystem.hpp"

namespace Subtile
{

class Shader::DescriptorSet::Layout::Resolver::Inline : public Shader::DescriptorSet::Layout::Resolver
{
public:
	Inline(ISystem &sys, const Layout::Description &desc);
	~Inline(void) override;

	const Layout& resolve(void) const override;

private:
	std::unique_ptr<Layout> m_layout;
};

}