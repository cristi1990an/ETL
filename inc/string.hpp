#pragma once

#include <string>
#include <functional>
#include <memory>
#include <optional>

namespace etl
{
	template<
		typename CharT,
		class Traits = std::char_traits<CharT>,
		class Allocator = std::allocator<CharT>
	> class lazy_basic_string : private Allocator
	{
	private:
		using string_equivalent = std::basic_string<CharT, Traits, Allocator>;
		using string_view_equivalent = std::basic_string_view<CharT, Traits>;

	public:
		using traits_type = Traits;
		using value_type = CharT;
		using allocator_type = Allocator;
		using size_type = std::allocator_traits<Allocator>::size_type;
		using difference_type = std::allocator_traits<Allocator>::difference_type;

		explicit constexpr lazy_basic_string(const string_view_equivalent str)
			: size_evaluator_
			{ [str]() -> std::size_t
				{
					return str.size();
				}
			}
			, evaluator_
			{ [str]() -> string_equivalent
				{
					return str;
				}
			}
			
		{

		}

		explicit constexpr lazy_basic_string(const string_equivalent& str)
			: size_evaluator_
			{ [&str]() -> std::size_t
				{
					return str.size();
				}
			}
			, evaluator_
			{ [&str]() -> string_equivalent
				{
					return str;
				}
			}
			
		{

		}

		constexpr lazy_basic_string operator+=(const string_equivalent& str) noexcept
		{
			auto new_size_evaluator_ = [old_size_evaluator_ = std::move(size_evaluator_), &str, this]() mutable
			{
				return str.size() + old_size_evaluator_();
			};
			size_evaluator_ = std::move(new_size_evaluator_);

			auto new_evaluator_ = [old_evaluator_ = std::move(evaluator_), &str, this]()
			{
				string_equivalent result;
				result.reserve(size_evaluator_());
				result += old_evaluator_();
				result += str;

				cached_result_ = result;

				return result;
			};
			evaluator_ = std::move(new_evaluator_);

			cached_result_.reset();

			return *this;
		}

		constexpr string_equivalent evaluate() const
		{
			return cached_result_.value_or(evaluator_());
		}

	private:
		constexpr Allocator& get_allocator() const noexcept
		{
			return static_cast<const Allocator&>(*this);
		}

		std::function<std::size_t()> size_evaluator_;
		std::function<string_equivalent()> evaluator_;
		mutable std::optional<string_equivalent> cached_result_;
	};
}