#pragma once

#include <iostream>

namespace util {

template <typename S>
class scalar
{
public:
	using type = S;

	scalar(void) = default;
	scalar(S value) :
		m_value(value)
	{
	}

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

	scalar operator+(int) const
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

	scalar operator*(S other) const
	{
		return m_value * other;
	}
	scalar operator/(S other) const
	{
		return m_value / other;
	}
	scalar operator%(S other) const
	{
		return m_value % other;
	}
	scalar operator+(S other) const
	{
		return m_value + other;
	}
	scalar operator-(S other) const
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

	bool operator<(S other) const
	{
		return m_value < other;
	}
	bool operator<=(S other) const
	{
		return m_value <= other;
	}
	bool operator>(S other) const
	{
		return m_value > other;
	}
	bool operator>=(S other) const
	{
		return m_value >= other;
	}
	bool operator==(S other) const
	{
		return m_value == other;
	}
	bool operator!=(S other) const
	{
		return m_value != other;
	}

	scalar operator&(S other) const
	{
		return m_value & other;
	}
	scalar operator^(S other) const
	{
		return m_value ^ other;
	}
	scalar operator|(S other) const
	{
		return m_value | other;
	}
	scalar operator&&(S other) const
	{
		return m_value && other;
	}
	scalar operator||(S other) const
	{
		return m_value || other;
	}

	auto& operator=(S other) &
	{
		m_value = other;
		return *this;
	}
	auto operator=(S other) &&
	{
		m_value = other;
		return *this;
	}

	auto& operator+=(S other) &
	{
		m_value += other;
		return *this;
	}
	auto operator+=(S other) &&
	{
		m_value += other;
		return *this;
	}

	auto& operator-=(S other) &
	{
		m_value -= other;
		return *this;
	}
	auto operator-=(S other) &&
	{
		m_value -= other;
		return *this;
	}

	auto& operator*=(S other) &
	{
		m_value *= other;
		return *this;
	}
	auto operator*=(S other) &&
	{
		m_value *= other;
		return *this;
	}

	auto& operator/=(S other) &
	{
		m_value /= other;
		return *this;
	}
	auto operator/=(S other) &&
	{
		m_value /= other;
		return *this;
	}

	auto& operator%=(S other) &
	{
		m_value %= other;
		return *this;
	}
	auto operator%=(S other) &&
	{
		m_value %= other;
		return *this;
	}

	auto& operator<<=(S other) &
	{
		m_value <<= other;
		return *this;
	}
	auto operator<<=(S other) &&
	{
		m_value <<= other;
		return *this;
	}

	auto& operator>>=(S other) &
	{
		m_value >>= other;
		return *this;
	}
	auto operator>>=(S other) &&
	{
		m_value >>= other;
		return *this;
	}

	auto& operator&=(S other) &
	{
		m_value &= other;
		return *this;
	}
	auto operator&=(S other) &&
	{
		m_value &= other;
		return *this;
	}

	auto& operator^=(S other) &
	{
		m_value ^= other;
		return *this;
	}
	auto operator^=(S other) &&
	{
		m_value ^= other;
		return *this;
	}

	auto& operator|=(S other) &
	{
		m_value |= other;
		return *this;
	}
	auto operator|=(S other) &&
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
struct constant_cmp
{
private:
	template <typename Cmp, T...>
	struct gen;

	template <typename Cmp, T First>
	struct gen<Cmp, First>
	{
	private:
		static inline constexpr T res = First;

	public:
		using type = std::integral_constant<T, res>;
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

using size_cmp = constant_cmp<size_t>;

template <size_t Size>
class pad
{
	uint8_t data[Size];
};

}