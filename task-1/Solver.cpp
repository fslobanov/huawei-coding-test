/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 11:16 AM
 * \brief: 
 */

#include <Solver.h>

#include <cassert>
#include <utility>

namespace task_one {

Solver::Solver(common::InputStream &input, common::OutputStream &output)
    : input{input}
    , output{output}
    , sum_buffer{0}
{
	// We do not want to allocate string each time we are reading case, so input and output
	// buffers being allocated just once and being passed to functions by reference
	left.reserve(kMaxDigits);
	right.reserve(kMaxDigits);
}

void Solver::solve() noexcept(false)
{
	const auto number_of_cases = common::parse_integer(input, kCasesMin, kCasesMax);
	for(auto case_number = 0UL; case_number < number_of_cases; ++case_number) {
		read_number(left);
		read_number(right);
		print_case(case_number, sum_numbers());
	}
}

void Solver::read_number(Number &number) noexcept(false)
{
	// Not really need to clear buffers, we use only written bytes
	number.clear();
	input >> number;

	if(input.fail()) {
		throw std::invalid_argument("failed to read left number");
	}

	if(number.empty() || number.size() > kMaxDigits) {
		throw std::invalid_argument("invalid left num length");
	}

	// String data correctness check being omitted and will be performed on summation
}

std::uint8_t Solver::as_digit(char symbol) noexcept(false)
{
	if(symbol < '0' || symbol > '9') {
		throw std::invalid_argument("illegal symbol '" + std::string{symbol} + "'");
	}

	return symbol - '0';
}

std::size_t Solver::sum_numbers() noexcept(false)
{
	// Not really need to reset this buffer, we use only written bytes
	sum_buffer.fill(0);

	auto left_it = left.rbegin();
	auto right_it = right.rbegin();

	std::size_t sum_length{0};
	std::uint8_t carry{0};

	while(!(left.rend() == left_it && right.rend() == right_it)) {
		auto sum = std::exchange(carry, 0);

		if(left.rend() != left_it) {
			sum += as_digit(*left_it);
			++left_it;
		}

		if(right.rend() != right_it) {
			sum += as_digit(*right_it);
			++right_it;
		}

		if(sum >= 10) {
			carry = 1;
			sum -= 10;
		}

		sum_buffer[sum_buffer.size() - sum_length - 1] = static_cast<char>(sum + '0');
		++sum_length;

		assert(sum_length < sum_buffer.size());
	}

	if(carry) {
		sum_buffer[sum_buffer.size() - sum_length - 1] = static_cast<char>(carry + '0');
		++sum_length;
	}

	return sum_length;
}

void Solver::print_case(std::size_t case_number, std::size_t sum_length) noexcept
{
	const auto sum_view = std::string_view{sum_buffer.begin() + (sum_buffer.size() - sum_length), sum_length};
	output << "Case " << std::to_string(1 + case_number) << ":\n";
	output << left << " + " << right << " = " << sum_view << "\n" << std::endl;
}

}  // namespace task_one
