#pragma once

#include <set>
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
			class ArrayPad : public T, private util::pad<util::align_v<sizeof(T), 16> - sizeof(T)>
			{
			public:
				ArrayPad(void) = default;
				template <typename ...Args>
				ArrayPad(Args &&...args) :
					T(std::forward<Args>(args)...)
				{
				}
			};
		};

		template <typename T, size_t Size, class Layout = Std140>
		class Array
		{
		public:
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

		private:
			padded_type m_values[Size];
		};

		template <typename S, size_t C, size_t R, class Layout = Std140>
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
	};

	enum class Sbi {  // shader binary interface
		Vulkan
	};

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

		class Layout
		{
		public:
			Layout(std::initializer_list<LayoutBinding> init) :
				m_bindings(init)
			{
			}

			auto& getBindings(void) const
			{
				return m_bindings;
			}

		private:
			std::vector<LayoutBinding> m_bindings;
		};

		virtual ~DescriptorSet(void) = default;

		virtual void write(size_t offset, size_t range, const void *data) = 0;
		//virtual void bindCombinedImageSampler(RImage &img) = 0;
	};

	virtual std::unique_ptr<DescriptorSet> material(void) = 0;
	virtual std::unique_ptr<DescriptorSet> object(void) = 0;
};

}