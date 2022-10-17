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

namespace {
constexpr auto kMaxDepth = 4;
}

Solver::Solver(common::InputStream &input, common::OutputStream &output)
    : input{input}
    , output{output}
    , buffer{0}
{
}

void Solver::solve() noexcept(false)
{
	for(auto case_index{0u}; process_case(case_index); ++case_index) {
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
	for(auto index{0u}; index < number_count; ++index) {
		try {
			numbers.emplace(common::parse_integer(input, 1, upper_bound));
		} catch(...) {
			// Numbers outside of bounds being ignored
		}
	}
}

Solver::Stop Solver::find_greatest_number_impl(const Numbers &numbers,
                                               const Numbers ::const_iterator current_it,
                                               const std::uint8_t depth,
                                               const std::size_t sum,
                                               const uint32_t upper_bound) noexcept(false)
{
	if(kMaxDepth == depth || current_it == numbers.end()) {
		if(sum == upper_bound) {
			greatest_number = upper_bound;
			return Stop::Yes;
		}

		if(sum < upper_bound) {
			greatest_number = std::max(greatest_number, sum);
		}
		return Stop::No;
	}

	for(auto number_it = current_it; number_it != numbers.cend(); ++number_it) {
		const auto new_sum = sum + *number_it;
		if(new_sum == upper_bound) {
			greatest_number = upper_bound;
			return Stop::Yes;
		}
		
		if(new_sum > upper_bound) {
			return Stop::No;
		}

		if(Stop::Yes == find_greatest_number_impl(numbers, number_it, 1 + depth, new_sum, upper_bound)) {
			return Stop::Yes;
		}

		if(Stop::Yes == find_greatest_number_impl(numbers, std::next(number_it), 1 + depth, new_sum, upper_bound)) {
			return Stop::Yes;
		}
	}
	return Stop::No;
}

std::uint32_t Solver::find_greatest_number(Numbers &numbers, const std::uint32_t upper_bound) noexcept(false)
{
	greatest_number = 0;
	const auto equals_upper_bound = find_greatest_number_impl(numbers, numbers.begin(), 0, 0, upper_bound);
	(void)equals_upper_bound;
	return greatest_number;
}

}  // namespace task_two
