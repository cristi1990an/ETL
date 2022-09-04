#pragma once

#include <type_traits>
#include <concepts>

#include "../compressed_pair.hpp"

namespace etl::static_tests::compressed_pair
{
	struct	long_long	{	long long	x;	long long	y; };
	struct	int_long	{	int			x;	long long	y; };
	struct	long_int	{	long long	x;	int			y; };
	struct	int_int		{	int			x;	int			y; };
	struct	char_long	{	char		x;	long long	y; };
	struct	long_char	{	long long	x;	char		y; };
	struct	int_char	{	int			x;	char		y; };
	struct	char_int	{	char		x;	int			y; };
	struct	char_char	{	char		x;	char		y; };
	struct  empty		{                                  };

	inline constexpr std::size_t long_long_size	= sizeof(long_long);
	inline constexpr std::size_t int_long_size	= sizeof(int_long);
	inline constexpr std::size_t long_int_size	= sizeof(long_int);
	inline constexpr std::size_t int_int_size	= sizeof(int_int);
	inline constexpr std::size_t char_long_size = sizeof(char_long);
	inline constexpr std::size_t long_char_size = sizeof(long_char);
	inline constexpr std::size_t int_char_size	= sizeof(int_char);
	inline constexpr std::size_t char_char_size = sizeof(char_char);
	inline constexpr std::size_t long_size		= sizeof(long long);
	inline constexpr std::size_t int_size		= sizeof(int);
	inline constexpr std::size_t char_size		= sizeof(char);

	using long_long_pair	= etl::compressed_pair<long long, long long>;
	using int_long_pair		= etl::compressed_pair<int, long long>;
	using long_int_pair		= etl::compressed_pair<long long, int>;
	using int_int_pair		= etl::compressed_pair<int, int>;
	using char_long_pair	= etl::compressed_pair<char, long long>;
	using long_char_pair	= etl::compressed_pair<long long, long long>;
	using int_char_pair		= etl::compressed_pair<int, char>;
	using char_char_pair	= etl::compressed_pair<char, char>;
	using long_empty_pair	= etl::compressed_pair<long long, empty>;
	using empty_long_pair	= etl::compressed_pair<empty, long long>;
	using int_empty_pair	= etl::compressed_pair<int, empty>;
	using empty_int_pair	= etl::compressed_pair<empty, int>;
	using char_empty_pair	= etl::compressed_pair<char, empty>;
	using empty_char_pair	= etl::compressed_pair<empty, char>;
	using empty_empty_pair	= etl::compressed_pair<empty, empty>;

	inline constexpr std::size_t long_long_pair_size	= sizeof(long_long_pair);
	inline constexpr std::size_t int_long_pair_size		= sizeof(int_long_pair);
	inline constexpr std::size_t long_int_pair_size		= sizeof(long_int_pair);
	inline constexpr std::size_t int_int_pair_size		= sizeof(int_int_pair);
	inline constexpr std::size_t char_long_pair_size	= sizeof(char_long_pair);
	inline constexpr std::size_t long_char_pair_size	= sizeof(long_char_pair);
	inline constexpr std::size_t int_char_pair_size		= sizeof(int_char_pair);
	inline constexpr std::size_t char_char_pair_size	= sizeof(char_char_pair);
	inline constexpr std::size_t long_empty_pair_size	= sizeof(long_empty_pair);
	inline constexpr std::size_t empty_long_pair_size	= sizeof(empty_long_pair);
	inline constexpr std::size_t int_empty_pair_size	= sizeof(int_empty_pair);
	inline constexpr std::size_t empty_int_pair_size	= sizeof(empty_int_pair);
	inline constexpr std::size_t char_empty_pair_size	= sizeof(char_empty_pair);
	inline constexpr std::size_t empty_char_pair_size	= sizeof(empty_char_pair);
	inline constexpr std::size_t empty_empty_pair_size	= sizeof(empty_empty_pair);

	static_assert(long_long_size	==	long_long_pair_size);
	static_assert(int_long_size		==	int_long_pair_size);
	static_assert(long_int_size		==	long_int_pair_size);
	static_assert(int_int_size		==	int_int_pair_size);
	static_assert(char_long_size	==	char_long_pair_size);
	static_assert(long_char_size	==	long_char_pair_size);
	static_assert(int_char_size		==	int_char_pair_size);
	static_assert(char_char_size	==	char_char_pair_size);
	static_assert(long_size			==	long_empty_pair_size);
	static_assert(long_size			==	empty_long_pair_size);
	static_assert(int_size			==	int_empty_pair_size);
	static_assert(int_size			==	empty_int_pair_size);
	static_assert(char_size			==	char_empty_pair_size);
	static_assert(char_size			==	empty_char_pair_size);
	static_assert(char_size			==  empty_char_pair_size);
	static_assert(1					==  empty_empty_pair_size);

	static_assert(std::is_trivially_default_constructible_v<int_int_pair>);
	static_assert(std::is_trivially_copy_constructible_v<int_int_pair>);
	static_assert(std::is_trivially_move_constructible_v<int_int_pair>);
	static_assert(std::is_trivially_copy_assignable_v<int_int_pair>);
	static_assert(std::is_trivially_move_assignable_v<int_int_pair>);
	static_assert(std::is_trivially_destructible_v<int_int_pair>);

	static_assert(std::is_nothrow_default_constructible_v<int_int_pair>);
	static_assert(std::is_nothrow_copy_constructible_v<int_int_pair>);
	static_assert(std::is_nothrow_move_constructible_v<int_int_pair>);
	static_assert(std::is_nothrow_copy_assignable_v<int_int_pair>);
	static_assert(std::is_nothrow_move_assignable_v<int_int_pair>);
	static_assert(std::is_nothrow_destructible_v<int_int_pair>);


	inline constexpr auto _ = []() -> empty
	{
		[[maybe_unused]] etl::compressed_pair<char, double> pair{};

		static_assert(std::same_as<decltype(pair.first()), char&>);
		static_assert(std::same_as<decltype(pair.second()), double&>);

		static_assert(std::same_as<decltype(std::move(pair).first()), char&&>);
		static_assert(std::same_as<decltype(std::move(pair).second()), double&&>);

		static_assert(std::same_as<decltype(std::as_const(pair).first()), const char&>);
		static_assert(std::same_as<decltype(std::as_const(pair).second()), const double&>);

		static_assert(std::same_as<decltype(std::move(std::as_const(pair)).first()), const char&&>);
		static_assert(std::same_as<decltype(std::move(std::as_const(pair)).second()), const double&&>);

		return {};
	}();
}