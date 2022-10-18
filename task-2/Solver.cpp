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
    , upper_bound{0}
    , greatest_number{0}
{
}

void Solver::solve() noexcept(false)
{
	for(auto case_index{0u}; Stop::No == process_case(case_index); ++case_index) {
	}
}

void Solver::print_case(const std::size_t case_number, const std::uint32_t greatest)
{
	output << "Case " << std::to_string(1 + case_number) << ": " << std::to_string(greatest) << "\n" << std::endl;
}

Solver::Stop Solver::process_case(const std::size_t case_number) noexcept(false)
{
	std::pmr::monotonic_buffer_resource memory_resource{buffer.data(), buffer.size()};
	std::pmr::polymorphic_allocator<Number> allocator{&memory_resource};
	Numbers numbers{allocator};

	const auto number_count = common::parse_integer(input, 0, kNumbersLimit);
	upper_bound = common::parse_integer(input, 0, kUpperBoundLimit);

	if(!number_count && !upper_bound) {
		return Stop::Yes;
	}

	read_numbers(number_count, numbers);
	print_case(case_number, find_greatest_number(numbers));
	return Stop::No;
}

void Solver::read_numbers(const std::size_t number_count, Numbers &numbers) noexcept
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
                                               const Numbers ::const_iterator cursor,
                                               const std::uint8_t depth,
                                               const std::uint8_t same_number,
                                               const std::size_t sum) noexcept(false)
{
	// If we reach out of depth or numbers, we should stop our search
	if(kMaxDepth == depth || cursor == numbers.end()) {
		// Perfect, we got GN, but seems this might not happen, because we check it at previous call
		if(sum == upper_bound) {
			greatest_number = upper_bound;
			return Stop::Yes;
		}

		// We got 4 same numbers in a row, and we can stop to find GN, because
		// all consequent sum would be less than current
		if(kMaxDepth == same_number) {
			// If sum is less than bound, we try to update GN if possible
			if(sum < upper_bound) {
				greatest_number = std::max(greatest_number, sum);
				return Stop::Yes;
			}
		}

		// If sum is less than bound, we try to update GN if possible
		if(sum < upper_bound) {
			greatest_number = std::max(greatest_number, sum);
		}
		return Stop::No;
	}

	// Simply iterate over rest numbers
	for(auto number_it = cursor; number_it != numbers.cend(); ++number_it) {
		const auto new_sum = sum + *number_it;

		// If sum is equal, perfect, we found solution
		if(new_sum == upper_bound) {
			greatest_number = upper_bound;
			return Stop::Yes;
		}

		// Sum overflow, giving up
		if(new_sum > upper_bound) {
			return Stop::No;
		}

		// Trying to use this number again
		if(Stop::Yes == find_greatest_number_impl(numbers, number_it, 1 + depth, 1 + same_number, new_sum)) {
			return Stop::Yes;
		}

		// Trying to find missing number to complete upper bound
		// We cannot use closest, because greater GN may exist, consider
		// upper bound is 10, rest is [7,5]. 7 is closest to upper bound, but GN is 2*5
		const Number missing = upper_bound - new_sum;
		const auto missing_found = std::binary_search(number_it, numbers.end(), missing, std::greater<std::uint32_t>{});
		if(missing_found) {
			greatest_number = upper_bound;
			return Stop::Yes;
		}

		// Using next number which is less than current
		if(Stop::Yes == find_greatest_number_impl(numbers, std::next(number_it), 1 + depth, 0, new_sum)) {
			return Stop::Yes;
		}
	}
	return Stop::No;
}

std::uint32_t Solver::find_greatest_number(Numbers &numbers) noexcept(false)
{
	greatest_number = 0;
	const auto equals_upper_bound = find_greatest_number_impl(numbers, numbers.begin(), 0, 0, 0);
	(void)equals_upper_bound;
	return greatest_number;
}

}  // namespace task_two
