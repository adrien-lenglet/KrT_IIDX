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

	scalar operator*(const scalar &other) const
	{
		return m_value * other.m_value;
	}
	scalar operator/(const scalar &other) const
	{
		return m_value / other.m_value;
	}
	scalar operator%(const scalar &other) const
	{
		return m_value % other.m_value;
	}
	scalar operator+(const scalar &other) const
	{
		return m_value + other.m_value;
	}
	scalar operator-(const scalar &other) const
	{
		return m_value - other.m_value;
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

	bool operator<(const scalar &other) const
	{
		return m_value < other.m_value;
	}
	bool operator<=(const scalar &other) const
	{
		return m_value <= other.m_value;
	}
	bool operator>(const scalar &other) const
	{
		return m_value > other.m_value;
	}
	bool operator>=(const scalar &other) const
	{
		return m_value >= other.m_value;
	}
	bool operator==(const scalar &other) const
	{
		return m_value == other.m_value;
	}
	bool operator!=(const scalar &other) const
	{
		return m_value != other.m_value;
	}

	scalar operator&(const scalar &other) const
	{
		return m_value & other.m_value;
	}
	scalar operator^(const scalar &other) const
	{
		return m_value ^ other.m_value;
	}
	scalar operator|(const scalar &other) const
	{
		return m_value | other.m_value;
	}
	scalar operator&&(const scalar &other) const
	{
		return m_value && other.m_value;
	}
	scalar operator||(const scalar &other) const
	{
		return m_value || other.m_value;
	}

	auto& operator=(const scalar &other) &
	{
		m_value = other.m_value;
		return *this;
	}
	auto operator=(const scalar &other) &&
	{
		m_value = other.m_value;
		return *this;
	}

	auto& operator+=(const scalar &other) &
	{
		m_value += other.m_value;
		return *this;
	}
	auto operator+=(const scalar &other) &&
	{
		m_value += other.m_value;
		return *this;
	}

	auto& operator-=(const scalar &other) &
	{
		m_value -= other.m_value;
		return *this;
	}
	auto operator-=(const scalar &other) &&
	{
		m_value -= other.m_value;
		return *this;
	}

	auto& operator*=(const scalar &other) &
	{
		m_value *= other.m_value;
		return *this;
	}
	auto operator*=(const scalar &other) &&
	{
		m_value *= other.m_value;
		return *this;
	}

	auto& operator/=(const scalar &other) &
	{
		m_value /= other.m_value;
		return *this;
	}
	auto operator/=(const scalar &other) &&
	{
		m_value /= other.m_value;
		return *this;
	}

	auto& operator%=(const scalar &other) &
	{
		m_value %= other.m_value;
		return *this;
	}
	auto operator%=(const scalar &other) &&
	{
		m_value %= other.m_value;
		return *this;
	}

	auto& operator<<=(const scalar &other) &
	{
		m_value <<= other.m_value;
		return *this;
	}
	auto operator<<=(const scalar &other) &&
	{
		m_value <<= other.m_value;
		return *this;
	}

	auto& operator>>=(const scalar &other) &
	{
		m_value >>= other.m_value;
		return *this;
	}
	auto operator>>=(const scalar &other) &&
	{
		m_value >>= other.m_value;
		return *this;
	}

	auto& operator&=(const scalar &other) &
	{
		m_value &= other.m_value;
		return *this;
	}
	auto operator&=(const scalar &other) &&
	{
		m_value &= other.m_value;
		return *this;
	}

	auto& operator^=(const scalar &other) &
	{
		m_value ^= other.m_value;
		return *this;
	}
	auto operator^=(const scalar &other) &&
	{
		m_value ^= other.m_value;
		return *this;
	}

	auto& operator|=(const scalar &other) &
	{
		m_value |= other.m_value;
		return *this;
	}
	auto operator|=(const scalar &other) &&
	{
		m_value |= other.m_value;
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

template <size_t Size>
class pad
{
	uint8_t data[Size];
};

}