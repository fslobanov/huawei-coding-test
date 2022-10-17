/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 12:24 PM
 * \brief: 
 */

#pragma once

#include <array>
#include <set>
#include <memory_resource>

#include <common.h>

namespace task_two {

class Solver final
{
public:
	Solver(common::InputStream &input, common::OutputStream &output);
	void solve() noexcept(false);

private:
	constexpr static auto kNumbersLimit = 1'000ul;
	constexpr static auto kUpperBoundLimit = 1'000'000'000ul;

	using Number = std::uint32_t;
	using Numbers = std::pmr::set<Number, std::greater<Number>>;

	constexpr static auto kNodeMemory = sizeof(Numbers::node_type) + 32;
	//static_assert(kNodeMemory == 48 );
	using Buffer = std::array<Number, kNumbersLimit * kNodeMemory>;

	enum class [[nodiscard]] Stop : bool
	{
		No,
		Yes
	};

private:
	common::InputStream &input;
	common::OutputStream &output;

	Buffer buffer;
	std::size_t greatest_number;

private:
	[[nodiscard]] bool process_case(std::size_t case_number) noexcept(false);
	void read_numbers(std::size_t number_count, std::size_t upper_bound, Numbers &numbers) noexcept;
	[[nodiscard]] std::uint32_t find_greatest_number(Numbers &numbers, uint32_t upper_bound) noexcept(false);
	
	/**
	 * @brief Recursively search for proper solution
	 * @param numbers
	 * @param current_it
	 * @param depth
	 * @param sum
	 * @param upper_bound
	 * @return
	 */
	Stop find_greatest_number_impl(const Numbers &numbers,
	                               Numbers ::const_iterator current_it,
	                               std::uint8_t depth,
	                               std::size_t sum,
	                               uint32_t upper_bound) noexcept(false);
	/**
	 * @brief Just prints case results to output stream
	 */
	void print_case(std::size_t case_number, std::size_t max_sum);
};

}  // namespace task_two
