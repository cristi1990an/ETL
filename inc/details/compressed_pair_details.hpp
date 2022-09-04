#pragma once

#include <type_traits>
#include <functional>
#include <compare>
#include "../type_traits.hpp"

namespace etl
{
	template <typename T1, typename T2>
	class compressed_pair;

namespace details
{
	template<typename T>
	struct first_value_wrapper
	{
		T first_value;

		constexpr T& get_first_value() & noexcept
		{
			return first_value;
		}

		constexpr const T& get_first_value() const& noexcept
		{
			return first_value;
		}

		constexpr T&& get_first_value() && noexcept
		{
			return std::move(first_value);
		}

		constexpr const T&& get_first_value() const&& noexcept
		{
			return std::move(first_value);
		}
	};

	template<typename T>
	struct class_first_value_wrapper : private T
	{
		constexpr T& get_first_value() & noexcept
		{
			return static_cast<T&>(*this);
		}

		constexpr const T& get_first_value() const& noexcept
		{
			return static_cast<const T&>(*this);
		}

		constexpr T&& get_first_value() && noexcept
		{
			return static_cast<T&&>(*this);
		}

		constexpr const T&& get_first_value() const&& noexcept
		{
			return static_cast<const T&&>(*this);
		}
	};

	template<typename T>
	struct second_value_wrapper
	{
		T second_value;

		constexpr T& get_second_value() & noexcept
		{
			return second_value;
		}

		constexpr const T& get_second_value() const& noexcept
		{
			return second_value;
		}

		constexpr T&& get_second_value() && noexcept
		{
			return std::move(second_value);
		}

		constexpr const T&& get_second_value() const&& noexcept
		{
			return std::move(second_value);
		}
	};

	template<typename T>
	struct class_second_value_wrapper : private T
	{
		constexpr T& get_second_value() & noexcept
		{
			return static_cast<T&>(*this);
		}

		constexpr const T& get_second_value() const& noexcept
		{
			return static_cast<const T&>(*this);
		}

		constexpr T&& get_second_value() && noexcept
		{
			return static_cast<T&&>(*this);
		}

		constexpr const T&& get_second_value() const&& noexcept
		{
			return static_cast<const T&&>(*this);
		}
	};

	template<typename T1, typename T2>
	struct deduced_pair
	{
		using type = compressed_pair<
			std::unwrap_ref_decay_t<T1>,
			std::unwrap_ref_decay_t<T2>
		>;
	};

	template<typename T1, typename T2>
	using deduced_pair_t = typename deduced_pair<T1, T2>::type;

	template<typename T1, typename T2>
	struct pair_compare_three_way_result
	{
		using type = std::common_comparison_category_t<
			std::compare_three_way_result_t<T1>,
			std::compare_three_way_result_t<T2>
		>;
	};

	template<typename T1, typename T2>
	using pair_compare_three_way_result_t =
		typename pair_compare_three_way_result<T1, T2>::type;
}
}