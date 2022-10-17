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
	constexpr static auto kMaxDepth = 4u;

	using Number = std::uint32_t;
	// We need input numbers to be sorted and unique, so we insert them into set with no dynamic allocations
	using Numbers = std::pmr::set<Number, std::greater<Number>>;
	constexpr static auto kNodeMemory = sizeof(Numbers::node_type) + 32;
	// Buffer should be big enough to fit node data and std::set pointers
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
	std::uint32_t upper_bound;
	std::size_t greatest_number;

private:
	/**
	 * @brief Processes each cases one by one
	 */
	Stop process_case(std::size_t case_number) noexcept(false);

	/**
	 * @brief Reads numbers from stream into provided container
	 * @details Drops numbers greater which are out of bounds
	 */
	void read_numbers(std::size_t number_count, Numbers &numbers) noexcept;

	/**
	 * @brief Driver for recursive implementation
	 * @return GN
	 */
	[[nodiscard]] std::uint32_t find_greatest_number(Numbers &numbers) noexcept(false);

	/**
	 * @brief Recursively searches for proper solution
	 * @return Indicator that found GN which is equal to upper_bound
	 */
	Stop find_greatest_number_impl(const Numbers &numbers,
	                               Numbers ::const_iterator cursor,
	                               std::uint8_t depth,
	                               std::size_t sum) noexcept(false);
	/**
	 * @brief Just prints case results to output stream
	 */
	void print_case(std::size_t case_number, std::uint32_t greatest);
};

}  // namespace task_two
