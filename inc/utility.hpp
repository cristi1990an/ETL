#pragma once

#include <array>
#include <type_traits>
#include <concepts>
#include <span>

#include "compressed_pair.hpp"

namespace etl
{
	template<typename T, std::size_t Size, typename Predicate>
	constexpr auto array_transform(const std::array<T, Size>& arr, Predicate pred)
		-> std::array<std::invoke_result_t<Predicate, const T&>, Size>
	{
		return [&arr, &pred]<std::size_t ... I>(std::index_sequence<I...>)
			->std::array<std::invoke_result_t<Predicate, const T&>, Size>
		{
			return { std::invoke(pred, arr[I]) ... };
		}(std::make_index_sequence<Size>());
	}

	template<typename T, std::size_t Size, typename Predicate>
		requires (Size != std::dynamic_extent)
	constexpr auto array_transform(const std::span<T, Size>& arr, Predicate pred)
		->std::array<std::invoke_result_t<Predicate, const T&>, Size>
	{
		return [&arr, &pred]<std::size_t ... I>(std::index_sequence<I...>)
			->std::array<std::invoke_result_t<Predicate, const T&>, Size>
		{
			return { std::invoke(pred, arr[I]) ... };
		}(std::make_index_sequence<Size>());
	}
}