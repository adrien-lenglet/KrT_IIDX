#pragma once

#include <set>
#include <vector>
#include <memory>
#include "Subtile/Math.hpp"
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>
#include "util/bin.hpp"

namespace Subtile {

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

			using salign = util::csize_t<sizeof(uint32_t)>;
			using balign = salign;
			using ealign = balign;
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

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;
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

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;
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

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;
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

			using salign = util::csize_t<sizeof(type)>;
			using balign = salign;
			using ealign = balign;
		};

		template <typename S, size_t Size>
		struct Vec;

		template <typename S>
		struct Vec<S, 2> : public glm::vec<2, S, glm::defaultp>
		{
			Vec(void) = default;
			template <typename ...Args>
			Vec(Args &&...args) :
				glm::vec<2, S, glm::defaultp>(std::forward<Args>(args)...)
			{
			}

			using salign = typename S::salign;
			using balign = util::csize_t<salign{} * 2>;
			using ealign = balign;
		};

		template <typename S>
		struct Vec<S, 3> : public glm::vec<3, S, glm::defaultp>
		{
			Vec(void) = default;
			template <typename ...Args>
			Vec(Args &&...args) :
				glm::vec<3, S, glm::defaultp>(std::forward<Args>(args)...)
			{
			}

			using salign = typename S::salign;
			using balign = util::csize_t<salign{} * 4>;
			using ealign = balign;
		};

		template <typename S>
		struct Vec<S, 4> : public glm::vec<4, S, glm::defaultp>
		{
			Vec(void) = default;
			template <typename ...Args>
			Vec(Args &&...args) :
				glm::vec<4, S, glm::defaultp>(std::forward<Args>(args)...)
			{
			}

			using salign = typename S::salign;
			using balign = util::csize_t<salign{} * 4>;
			using ealign = balign;
		};

		struct Std140
		{
			template <typename T>
			struct ArrayPad : public T, private util::pad<util::align_v<sizeof(T), 16> - sizeof(T)>
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

	class DescriptorSet
	{
	public:
		class LayoutBinding
		{
		public:
			size_t binding;
			size_t descriptorCount;
			DescriptorType descriptorType;
			std::set<Stage> stages;
		};

		struct LayoutBindingMapped : public LayoutBinding
		{
			size_t offset;
			size_t size;
		};

		class Layout
		{
		public:
			std::vector<LayoutBindingMapped> bindings_mapped;
			size_t bindings_mapped_size;
			std::vector<LayoutBinding> bindings;
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

	virtual std::unique_ptr<DescriptorSet> material(void) = 0;
	virtual std::unique_ptr<DescriptorSet> object(void) = 0;

	/*
	template <typename ShaderRs>
	using Material = DescriptorSet::Handle<typename Shader::Rs::materialTraits>;
	template <typename ShaderRs>
	using Object = DescriptorSet::Handle<typename Shader::Rs::objectTraits>;
	*/
};

}