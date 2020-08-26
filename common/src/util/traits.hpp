#pragma once

#include <tuple>
#include <functional>

namespace util {

template <typename T>
using remove_cvr_t = std::remove_cv_t<std::remove_reference_t<T>>;

struct empty_struct { template <typename ...Args> empty_struct(Args &&...) {} };
template <bool Pred, class T>
using conditional_un_t = std::conditional_t<Pred, T, empty_struct>;

struct empty_t {};
static inline constexpr empty_t empty;

struct identity_converter
{
	template <typename Arg>
	static auto& convert(Arg &&arg)
	{
		return arg;
	}
};

template <template <typename> typename Predicate, typename Converter = identity_converter>
struct elems_to_count_ptr
{
	template <typename ElemsType>
	static size_t count(ElemsType &&elems)
	{
		if constexpr (std::is_same_v<remove_cvr_t<ElemsType>, empty_t>)
			return 0;
		else if constexpr (Predicate<remove_cvr_t<ElemsType>>::value)
			return 1;
		else
			return elems.size();
	}

	template <typename ArrayValueType, typename ElemsType>
	static void fill_array(ArrayValueType *array, ElemsType &&elems)
	{
		if constexpr (Predicate<remove_cvr_t<ElemsType>>::value)
			array[0] = Converter::convert(std::forward<ElemsType>(elems));
		else {
			if constexpr (std::is_same_v<remove_cvr_t<ElemsType>, empty_t>) {
			} else {
				size_t ndx = 0;
				for (auto &el : elems)
					array[ndx++] = Converter::convert(*el);
			}
		}
	}
};

template <typename ValueType>
struct abstract_array
{
	abstract_array(size_t size, ValueType *data) :
		m_size(size),
		m_data(data)
	{
	}

	auto size(void) const
	{
		return m_size;
	}

	auto data(void) const
	{
		return m_data;
	}

private:
	size_t m_size;
	ValueType *m_data;
};

}