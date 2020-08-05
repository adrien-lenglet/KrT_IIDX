#pragma once

#include <iostream>

namespace util {

template <typename S>
class scalar
{
public:
	using type = S;

	scalar(void) = default;
	explicit scalar(S value) :
		m_value(value)
	{
	}
	scalar(const scalar&) = default;

	S value(void) const
	{
		return m_value;
	}

	operator S(void) const
	{
		return m_value;
	}

	auto& operator++(void) &
	{
		++m_value;
		return *this;
	}
	scalar operator++(void) &&
	{
		++m_value;
		return *this;
	}
	auto operator++(int)
	{
		auto res = *this;
		m_value++;
		return res;
	}

	auto& operator--(void) &
	{
		--m_value;
		return *this;
	}
	scalar operator--(void) &&
	{
		--m_value;
		return *this;
	}
	auto operator--(int)
	{
		auto res = *this;
		m_value--;
		return res;
	}

	scalar operator+(void) const
	{
		return +m_value;
	}
	scalar operator-(void) const
	{
		return -m_value;
	}
	scalar operator!(void) const
	{
		return !m_value;
	}
	scalar operator~(void) const
	{
		return ~m_value;
	}

	scalar operator*(scalar other) const
	{
		return m_value * other;
	}
	scalar operator/(scalar other) const
	{
		return m_value / other;
	}
	scalar operator%(scalar other) const
	{
		return m_value % other;
	}
	scalar operator+(scalar other) const
	{
		return m_value + other;
	}
	scalar operator-(scalar other) const
	{
		return m_value - other;
	}

	template <typename T>
	scalar operator<<(T &&other) const
	{
		return m_value << other;
	}
	template <typename T>
	scalar operator>>(T &&other) const
	{
		return m_value >> other;
	}

	bool operator<(scalar other) const
	{
		return m_value < other;
	}
	bool operator<=(scalar other) const
	{
		return m_value <= other;
	}
	bool operator>(scalar other) const
	{
		return m_value > other;
	}
	bool operator>=(scalar other) const
	{
		return m_value >= other;
	}
	bool operator==(scalar other) const
	{
		return m_value == other;
	}
	bool operator!=(scalar other) const
	{
		return m_value != other;
	}

	scalar operator&(scalar other) const
	{
		return m_value & other;
	}
	scalar operator^(scalar other) const
	{
		return m_value ^ other;
	}
	scalar operator|(scalar other) const
	{
		return m_value | other;
	}
	scalar operator&&(scalar other) const
	{
		return m_value && other;
	}
	scalar operator||(scalar other) const
	{
		return m_value || other;
	}

	auto& operator=(scalar other) &
	{
		m_value = other;
		return *this;
	}
	auto operator=(scalar other) &&
	{
		m_value = other;
		return *this;
	}

	auto& operator+=(scalar other) &
	{
		m_value += other;
		return *this;
	}
	auto operator+=(scalar other) &&
	{
		m_value += other;
		return *this;
	}

	auto& operator-=(scalar other) &
	{
		m_value -= other;
		return *this;
	}
	auto operator-=(scalar other) &&
	{
		m_value -= other;
		return *this;
	}

	auto& operator*=(scalar other) &
	{
		m_value *= other;
		return *this;
	}
	auto operator*=(scalar other) &&
	{
		m_value *= other;
		return *this;
	}

	auto& operator/=(scalar other) &
	{
		m_value /= other;
		return *this;
	}
	auto operator/=(scalar other) &&
	{
		m_value /= other;
		return *this;
	}

	auto& operator%=(scalar other) &
	{
		m_value %= other;
		return *this;
	}
	auto operator%=(scalar other) &&
	{
		m_value %= other;
		return *this;
	}

	auto& operator<<=(scalar other) &
	{
		m_value <<= other;
		return *this;
	}
	auto operator<<=(scalar other) &&
	{
		m_value <<= other;
		return *this;
	}

	auto& operator>>=(scalar other) &
	{
		m_value >>= other;
		return *this;
	}
	auto operator>>=(scalar other) &&
	{
		m_value >>= other;
		return *this;
	}

	auto& operator&=(scalar other) &
	{
		m_value &= other;
		return *this;
	}
	auto operator&=(scalar other) &&
	{
		m_value &= other;
		return *this;
	}

	auto& operator^=(scalar other) &
	{
		m_value ^= other;
		return *this;
	}
	auto operator^=(scalar other) &&
	{
		m_value ^= other;
		return *this;
	}

	auto& operator|=(scalar other) &
	{
		m_value |= other;
		return *this;
	}
	auto operator|=(scalar other) &&
	{
		m_value |= other;
		return *this;
	}

private:
	S m_value;
};

template <typename S>
std::ostream& operator<<(std::ostream &o, const scalar<S> &s)
{
	o << s.value();
	return o;
}

template <typename T>
struct constant
{
	template <T value>
	using value_t = std::integral_constant<T, value>;

private:
	template <typename Cmp, T...>
	struct gen;

	template <typename Cmp, T First>
	struct gen<Cmp, First>
	{
	private:
		static inline constexpr T res = First;

	public:
		using type = value_t<res>;
		static inline constexpr T value = type{};
	};

	template <typename Cmp, T First, T Second, T ...Rest>
	struct gen<Cmp, First, Second, Rest...>
	{
	private:
		static inline constexpr T res = Cmp()(First, Second) ? First : Second;

	public:
		using type = typename gen<Cmp, res, Rest...>::type;
		static inline constexpr T value = type{};
	};

public:
	template <T ...Args>
	using min = gen<std::less<>, Args...>;
	template <T ...Args>
	using min_t = typename min<Args...>::type;
	template <T ...Args>
	static inline constexpr T min_v = min_t<Args...>{};

	template <T ...Args>
	using max = gen<std::greater<>, Args...>;
	template <T ...Args>
	using max_t = typename max<Args...>::type;
	template <T ...Args>
	static inline constexpr T max_v = max_t<Args...>{};
};
using csize = constant<size_t>;
template <size_t value>
using csize_t = constant<size_t>::value_t<value>;

template <size_t Size>
class pad
{
	uint8_t data[Size];
};

template <size_t Offset, size_t Alignment>
struct align
{
	using type = std::conditional_t<Offset % Alignment == 0, csize_t<Offset>, csize_t<Offset - Offset % Alignment + Alignment>>;
	static inline constexpr size_t value = type{};
};

template <size_t ...Args>
using align_t = typename align<Args...>::type;
template <size_t ...Args>
static inline constexpr size_t align_v = align_t<Args...>{};

static inline constexpr size_t align_dyn(size_t offset, size_t alignment)
{
	if (offset % alignment == 0)
		return offset;
	else
		return offset - offset % alignment + alignment;
}

}