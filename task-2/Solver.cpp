/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 12:24 PM
 * \brief: 
 */

#include <Solver.h>

#include <cassert>
#include <algorithm>

namespace task_two {

Solver::Solver(common::InputStream &input, common::OutputStream &output)
    : input{input}
    , output{output}
    , buffer{0}
{
}

void Solver::solve() noexcept(false)
{
	for(auto case_index{0}; process_case(case_index); ++case_index) {
	}
}

void Solver::print_case(const std::size_t case_number, const std::size_t max_sum)
{
	output << "Case " << std::to_string(1 + case_number) << ": " << std::to_string(max_sum) << "\n" << std::endl;
}

bool Solver::process_case(const std::size_t case_number) noexcept(false)
{
	std::pmr::monotonic_buffer_resource memory_resource{buffer.data(), buffer.size()};
	std::pmr::polymorphic_allocator<Number> allocator{&memory_resource};
	Numbers numbers{allocator};

	const auto number_count = common::parse_integer(input, 0, kNumbersLimit);
	const auto upper_bound = common::parse_integer(input, 0, kUpperBoundLimit);

	if(!number_count && !upper_bound) {
		return false;
	}

	read_numbers(number_count, upper_bound, numbers);
	print_case(case_number, find_greatest_number(numbers, upper_bound));
	return true;
}

void Solver::read_numbers(const std::size_t number_count, const std::size_t upper_bound, Numbers &numbers) noexcept
{
	for(auto index = 0UL; index < number_count; ++index) {
		try {
			numbers.emplace(common::parse_integer(input, 1, upper_bound));
		} catch(...) {
			// Numbers outside of bounds being ignored
		}
	}
}

std::uint32_t Solver::find_greatest_number(Solver::Numbers &numbers, const std::uint32_t upper_bound) noexcept(false)
{
	if(numbers.empty()) {
		return 0;
	}

	auto iterator = numbers.rbegin();
	if(*iterator == upper_bound) {
		return upper_bound;
	}

	std::size_t remaining{upper_bound};
	std::size_t greatest_number{0};
	std::size_t component_count{4};

	while(component_count != 0) {
		const auto value = *iterator;
		const auto quotient = remaining / value;
		const auto remainder = remaining % value;

		const auto count = std::min(quotient, component_count);
		greatest_number += (count * value);
		if(greatest_number == upper_bound) {
			return upper_bound;
		}

		component_count -= count;
		iterator = std::lower_bound(iterator, numbers.rend(), remainder, std::greater<>{});
	}

	return greatest_number;
}

}  // namespace task_two
