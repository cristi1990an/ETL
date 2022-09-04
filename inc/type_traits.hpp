#pragma once

#include "details/type_traits_details.hpp"

namespace etl
{
	template <class T, class = void>
	struct is_implicitly_default_constructible : std::false_type {};

	template <class T>
	struct is_implicitly_default_constructible<T, std::void_t<decltype(details::implicitly_default_construct<T>({}))>>
		: std::true_type {};

	template<typename T>
	static constexpr bool is_implicitly_default_constructible_v = is_implicitly_default_constructible<T>::value;

	template<typename T>
	concept bool_convertible = std::convertible_to<T, bool>;

	template <class T>
	concept boolean_testable = bool_convertible<T> &&
		requires(T&& t) 
	{
			{ !static_cast<T&&>(t) } -> bool_convertible;
	};
}