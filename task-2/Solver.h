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
	using Numbers = std::pmr::set<Number>;

	constexpr static auto kNodeMemory = sizeof(Numbers::node_type) + 32;
	//static_assert(kNodeMemory == 48 );
	using Buffer = std::array<Number, kNumbersLimit * kNodeMemory>;
private:
	common::InputStream &input;
	common::OutputStream &output;

	Buffer buffer;

private:
	[[nodiscard]] bool process_case(std::size_t case_number) noexcept(false);
	void read_numbers(std::size_t number_count, std::size_t upper_bound, Numbers & numbers) noexcept;
	[[nodiscard]] static std::uint32_t find_greatest_number(Numbers & numbers,
	                                                        const uint32_t upper_bound) noexcept(false);
	void print_case(std::size_t case_number, std::size_t max_sum);
};

}  // namespace task_two
