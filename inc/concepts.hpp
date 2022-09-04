#pragma once

#include <type_traits>
#include <concepts>

#include "type_traits.hpp"

namespace etl
{
	template<typename T>
	concept implicitly_default_constructible = is_implicitly_default_constructible_v<T>;
}