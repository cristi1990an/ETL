#pragma once

#include <type_traits>
#include <concepts>
#include <utility>
#include <tuple>

#include "type_traits.hpp"
#include "concepts.hpp"
#include "compare.hpp"
#include "details/compressed_pair_details.hpp" 

namespace etl
{
	template <typename T1, typename T2>
	class compressed_pair
		: private std::conditional_t<std::is_class_v<T1>,
			details::class_first_value_wrapper<T1>,
			details::first_value_wrapper<T1>>
		, private std::conditional_t<std::is_class_v<T2>,
			details::class_second_value_wrapper<T2>,
			details::second_value_wrapper<T2>>
	{
	private:
		friend struct details::class_first_value_wrapper<T1>;
		friend struct details::first_value_wrapper<T1>;
		friend struct details::class_second_value_wrapper<T2>;
		friend struct details::second_value_wrapper<T2>;

		using first_wrapper_type = std::conditional_t<std::is_class_v<T1>,
			details::class_first_value_wrapper<T1>,
			details::first_value_wrapper<T1>>;
		using second_wrapper_type = std::conditional_t<std::is_class_v<T2>,
			details::class_second_value_wrapper<T2>,
			details::second_value_wrapper<T2>>;

		static constexpr bool default_constructible_pair =
			std::is_default_constructible_v<T1> &&
			std::is_default_constructible_v<T2>;

		static constexpr bool explicitly_default_constructible_pair =
			!etl::implicitly_default_constructible<T1> ||
			!etl::implicitly_default_constructible<T2>;

		static constexpr bool nothrow_default_constructible_pair =
			std::is_nothrow_default_constructible_v<T1> &&
			std::is_nothrow_default_constructible_v<T2>;

		static constexpr bool copy_constructible_pair =
			std::is_copy_constructible_v<T1> &&
			std::is_copy_constructible_v<T2>;

		static constexpr bool explicitly_copy_constructible_pair =
			!std::is_convertible_v<const T1&, T1> ||
			!std::is_convertible_v<const T2&, T2>;

		static constexpr bool nothrow_copy_constructible_pair =
			std::is_nothrow_copy_constructible_v<T1> &&
			std::is_nothrow_copy_constructible_v<T2>;

		static constexpr bool copy_assignable_pair =
			std::is_copy_assignable_v<T1> &&
			std::is_copy_assignable_v<T2>;

		static constexpr bool nothrow_copy_assignable_pair =
			std::is_nothrow_copy_assignable_v<T1> &&
			std::is_nothrow_copy_assignable_v<T2>;

		static constexpr bool move_constructible_pair =
			std::is_move_constructible_v<T1> &&
			std::is_move_constructible_v<T2>;

		static constexpr bool explicitly_move_constructible_pair =
			!std::is_convertible_v<T1&&, T1> ||
			!std::is_convertible_v<T2&&, T2>;

		static constexpr bool nothrow_move_constructible_pair =
			std::is_nothrow_move_constructible_v<T1> &&
			std::is_nothrow_move_constructible_v<T2>;

		static constexpr bool move_assignable_pair =
			std::is_move_assignable_v<T1> &&
			std::is_move_assignable_v<T2>;

		static constexpr bool nothrow_move_assignable_pair =
			std::is_nothrow_move_assignable_v<T1> &&
			std::is_nothrow_move_assignable_v<T2>;

		template<typename U1, typename U2>
		static constexpr bool constructible_pair_from =
			std::constructible_from<T1, U1> &&
			std::constructible_from<T2, U2>;

		template<typename U1, typename U2>
		static constexpr bool nothrow_constructible_pair_from =
			std::is_nothrow_constructible_v<T1, U1> &&
			std::is_nothrow_constructible_v<T2, U2>;

		template<typename U1, typename U2>
		static constexpr bool explicitly_constructible_pair_from =
			!std::is_convertible_v<U1, T1> ||
			!std::is_convertible_v<U2, T2>;

		static constexpr bool swappable_pair =
			std::is_swappable_v<T1> &&
			std::is_swappable_v<T2>;

		static constexpr bool swappable_const_pair =
			std::is_swappable_v<const T1> &&
			std::is_swappable_v<const T1>;

		static constexpr bool nothrow_swappable_pair =
			std::is_nothrow_swappable_v<T1> &&
			std::is_nothrow_swappable_v<T2>;

		static constexpr bool nothrow_swappable_const_pair =
			std::is_nothrow_swappable_v<const T1> &&
			std::is_nothrow_swappable_v<const T2>;

		static constexpr bool nothrow_destructible_pair =
			std::is_nothrow_destructible_v<T1> &&
			std::is_nothrow_destructible_v<T2>;

	public:
		using first_type = T1;
		using second_type = T2;

		explicit(explicitly_default_constructible_pair)
		compressed_pair()
			noexcept(nothrow_default_constructible_pair)
			requires default_constructible_pair
		= default;

		explicit(explicitly_copy_constructible_pair) constexpr compressed_pair(const T1& x, const T2& y)
			noexcept(nothrow_copy_constructible_pair) requires copy_constructible_pair
			: first_wrapper_type{ x }
			, second_wrapper_type{ y }
		{

		}

		template<typename U1, typename U2>
		explicit(explicitly_constructible_pair_from<U1, U2>) compressed_pair(U1&& x, U2&& y)
			noexcept(nothrow_constructible_pair_from<U1, U2>) requires constructible_pair_from<U1, U2>
			: first_wrapper_type{ std::forward<U1>(x) }
			, second_wrapper_type{ std::forward<U2>(y) }
		{

		}

		template<typename U1, typename U2>
		explicit(explicitly_constructible_pair_from<U1&, U2&>) constexpr compressed_pair(compressed_pair<U1, U2>& p)
			noexcept(nothrow_constructible_pair_from<U1&, U2&>) requires constructible_pair_from<U1&, U2&>
			: first_wrapper_type{ p.first_wrapper_type::first_value }
			, second_wrapper_type{ p.second_wrapper_type::second_value }
		{

		}

		template<typename U1, typename U2>
		explicit(explicitly_constructible_pair_from<const U1&, const U2&>) constexpr compressed_pair(const compressed_pair<U1, U2>& p)
			noexcept(nothrow_constructible_pair_from<const U1&, const U2&>) requires constructible_pair_from<const U1&, const U2&>
			: first_wrapper_type{ p.first_wrapper_type::first_value }
			, second_wrapper_type{ p.second_wrapper_type::second_value }
		{

		}

		template<typename U1, typename U2>
		explicit(explicitly_constructible_pair_from<U1, U2>) constexpr compressed_pair(compressed_pair<U1, U2>&& p)
			noexcept(nothrow_constructible_pair_from<U1, U2>) requires constructible_pair_from<U1, U2>
			: first_wrapper_type{ std::forward<U1>(p.first()) }
			, second_wrapper_type{ std::forward<U2>(p.second()) }
		{

		}

		template<typename U1, typename U2>
		explicit(explicitly_constructible_pair_from<U1, U2>) constexpr compressed_pair(const compressed_pair<U1, U2>&& p)
			noexcept(nothrow_constructible_pair_from<U1, U2>) requires constructible_pair_from<U1, U2>
			: first_wrapper_type{ std::forward<U1>(p.first()) }
			, second_wrapper_type{ std::forward<U2>(p.second()) }
		{

		}

		template<typename ... Args1, typename ... Args2>
		constexpr compressed_pair(
			const std::piecewise_construct_t,
			std::tuple<Args1...> first_args,
			std::tuple<Args2...> second_args) 
			noexcept(nothrow_constructible_pair_from<Args1..., Args2...>) requires constructible_pair_from<Args1..., Args2...>
			: first_wrapper_type { std::make_from_tuple<first_wrapper_type>(first_args) }
			, second_wrapper_type { std::make_from_tuple<second_wrapper_type>(second_args) }
		{

		}

		template<typename Self>
		constexpr decltype(auto) first(this Self&& self) noexcept
		{
			return std::forward<Self>(self).first_wrapper_type::get_first_value();
		}

		template<typename Self>
		constexpr decltype(auto) second(this Self&& self) noexcept
		{
			return std::forward<Self>(self).second_wrapper_type::get_second_value();
		}

		constexpr void swap(compressed_pair& other) noexcept(nothrow_swappable_pair) requires swappable_pair
		{
			std::swap(first(), other.first());
			std::swap(second(), other.second());
		}

		constexpr void swap(const compressed_pair& other) const noexcept(nothrow_swappable_const_pair) requires swappable_const_pair
		{
			std::swap(first(), other.first());
			std::swap(second(), other.second());
		}
	};

	template<typename T1, typename T2>
	struct ::std::tuple_size<compressed_pair<T1, T2>>
		: std::integral_constant<std::size_t, 2> {};

	template<std::size_t I, typename T>
	struct std::tuple_element;

	template<std::size_t I, typename T1, typename T2>
	struct ::std::tuple_element<I, compressed_pair<T1, T2>>
	{
		static_assert(I < 2, "Can't index compressed_tuple's elements outside [0, 1]");
	};

	template<typename T1, typename T2>
	struct ::std::tuple_element<0, etl::compressed_pair<T1, T2>>
	{
		using type = T1;
	};

	template<typename T1, typename T2>
	struct ::std::tuple_element<1, etl::compressed_pair<T1, T2>>
	{
		using type = T2;
	};

	template<typename T1, typename T2>
	constexpr auto make_pair(T1&& t, T2&& u)
	noexcept(
		std::is_nothrow_constructible_v<
			std::unwrap_ref_decay<T1>, T1> &&
		std::is_nothrow_constructible_v<
			std::unwrap_ref_decay<T2>, T2>
	) -> details::deduced_pair_t<T1, T2>
	{
		return {
			std::forward<T1>(t), std::forward<T2>(u)
		};
	}

	template<typename T1, typename T2>
	constexpr auto operator <=> (
		const compressed_pair<T1, T2>& lhs,
		const compressed_pair<T1, T2>& rhs
		)
	noexcept(
		noexcept(std::compare_three_way::operator()(std::declval<T1>(), std::declval<T1>())) &&
		noexcept(std::compare_three_way::operator()(std::declval<T2>(), std::declval<T2>()))
	) -> etl::details::pair_compare_three_way_result_t<T1, T2>
	{
		const auto first_comp_result = std::compare_three_way{}(lhs.first(), rhs.first());

		return first_comp_result
			? first_comp_result
			: std::compare_three_way{}(lhs.second(), rhs.second());
	}

	template<std::size_t I, class T1, class T2 >
	constexpr std::tuple_element_t<I, etl::compressed_pair<T1, T2>>&
		get(etl::compressed_pair<T1, T2>& p) noexcept
	{
		static_assert(I < 2, "Can't index compressed_tuple's elements outside [0, 1]");
		if constexpr (I == 0)
		{
			return p.first();
		}
		else if constexpr (I == 1)
		{
			return p.second();
		}
	}

	template< std::size_t I, class T1, class T2 >
	constexpr const std::tuple_element_t<I, etl::compressed_pair<T1, T2>>&
		get(const etl::compressed_pair<T1, T2>& p) noexcept
	{
		static_assert(I < 2, "Can't index compressed_tuple's elements outside [0, 1]");
		if constexpr (I == 0)
		{
			return p.first();
		}
		else if constexpr (I == 1)
		{
			return p.second();
		}
	}

	template< std::size_t I, class T1, class T2 >
	constexpr std::tuple_element_t<I, etl::compressed_pair<T1, T2>>&&
		get(etl::compressed_pair<T1, T2>&& p) noexcept
	{
		static_assert(I < 2, "Can't index compressed_tuple's elements outside [0, 1]");
		if constexpr (I == 0)
		{
			return std::move(p).first();
		}
		else if constexpr (I == 1)
		{
			return std::move(p).second();
		}
	}

	template< std::size_t I, class T1, class T2 >
	constexpr const std::tuple_element_t<I, etl::compressed_pair<T1, T2>>&&
		get(const etl::compressed_pair<T1, T2>&& p) noexcept
	{
		static_assert(I < 2, "Can't index compressed_tuple's elements outside [0, 1]");
		if constexpr (I == 0)
		{
			return std::move(p).first();
		}
		else if constexpr (I == 1)
		{
			return std::move(p).second();
		}
	}

	template <class T, class U>
	constexpr T& get(etl::compressed_pair<T, U>& p) noexcept
	{
		return p.first();
	}

	template <class T, class U>
	constexpr const T& get(const etl::compressed_pair<T, U>& p) noexcept
	{
		return p.first();
	}

	template <class T, class U>
	constexpr T&& get(etl::compressed_pair<T, U>&& p) noexcept
	{
		return std::move(p).first();
	}

	template <class T, class U>
	constexpr const T&& get(const etl::compressed_pair<T, U>&& p) noexcept
	{
		return std::move(p).first();
	}

	template <class T, class U>
	constexpr T& get(etl::compressed_pair<U, T>& p) noexcept
	{
		return p.second();
	}

	template <class T, class U>
	constexpr const T& get(const etl::compressed_pair<U, T>& p) noexcept
	{
		return p.second();
	}

	template <class T, class U>
	constexpr T&& get(etl::compressed_pair<U, T>&& p) noexcept
	{
		return std::move(p).second();
	}

	template <class T, class U>
	constexpr const T&& get(const etl::compressed_pair<U, T>&& p) noexcept
	{
		return std::move(p).second();
	}

	template<class T1, class T2>
	constexpr void swap(etl::compressed_pair<T1, T2>& p1, etl::compressed_pair<T1, T2>& p2)
		noexcept(std::is_nothrow_swappable_v<T1> && std::is_nothrow_swappable_v<T2>)
		requires(std::swappable<T1> && std::swappable<T2>)
	{
		p1.swap(p2);
	}

	template<class T1, class T2>
	constexpr void swap(const etl::compressed_pair<T1, T2>& p1, const etl::compressed_pair<T1, T2>& p2)
		noexcept(std::is_nothrow_swappable_v<const T1>&& std::is_nothrow_swappable_v<const T2>)
		requires(std::swappable<const T1>&& std::swappable<const T2>)
	{
		p1.swap(p2);
	}
}