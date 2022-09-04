#pragma once

#include <memory>
#include <type_traits>
#include <concepts>

namespace etl
{
	template<
		typename T,
		typename Allocator = std::allocator<T>
	> class devector : private Allocator
	{
	private:
		using traits = std::allocator_traits<Allocator>;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = traits::pointer;
		using const_pointer = traits::const_pointer;

		constexpr devector() noexcept(noexcept(Allocator{})) = default;

		explicit constexpr devector(const Allocator& alloc) noexcept
			: Allocator{ alloc }
		{

		}

		explicit constexpr devector(size_type count,
			const Allocator& alloc = Allocator{})
			: Allocator{ alloc }
			, memory_begin_{ allocate(count) }
			, data_begin_{ memory_begin_ }
			, memory_end_{ memory_begin_ + count }
			, data_end_{ memory_end_ }

		{
			try
			{
				std::uninitialized_value_construct_n(data_begin_, count);
			}
			catch (...)
			{
				deallocate();
				throw;
			}
		}

		[[nodiscard]] constexpr pointer data() noexcept
		{
			return data_begin_;
		}

		[[nodiscard]] constexpr const_pointer data() const noexcept
		{
			return data_begin_;
		}

		[[nodiscard]] constexpr size_type size() const noexcept
		{
			return std::distance(data_begin_, data_end_);
		}

		[[nodiscard]] constexpr size_type capacity() const noexcept
		{
			return std::distance(memory_begin_, memory_end_);
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return size() == 0;
		}

	private:
		constexpr Allocator& get_allocator() noexcept
		{
			return static_cast<Allocator&>(*this);
		}

		constexpr pointer allocate(size_type size)
		{
			return traits::allocate(get_allocator(), size);
		}

		constexpr void deallocate()
		{
			traits::deallocate(get_allocator(), memory_begin_, capacity());
		}

		pointer memory_begin_ = nullptr;
		pointer memory_end_ = nullptr;
		pointer data_begin_ = nullptr;
		pointer data_end_ = nullptr;
	};


}