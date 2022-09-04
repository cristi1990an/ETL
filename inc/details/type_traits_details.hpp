#pragma once

#include <type_traits>
#include <concepts>

namespace etl::details
{
	template <class T>
	constexpr void implicitly_default_construct(const T&) noexcept { /*helper method*/ };
}