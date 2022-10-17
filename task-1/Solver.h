/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 11:16 AM
 * \brief: 
 */

#pragma once

#include <array>

#include <common.h>

namespace task_one {

class Solver final
{
public:
	// Task precondition says than max number of cases is 1 <= T <= 20
	constexpr static auto kCasesMin{1ul};
	constexpr static auto kCasesMax{20ul};
	// Task precondition says than each integer will not exceed 1000 digits
	constexpr static auto kMaxDigits{1'000ul};

public:
	Solver(common::InputStream &input, common::OutputStream &output);
	void solve() noexcept(false);

private:
	// An input buffer for number, just an ordinary string, not an array, to be compatible with
	// standard library stream functions
	using Number = std::string;
	// Due to optimization needs, we need a buffer for summation result. During summation, we fill this buffer
	// from end to begin to preserve summation order, and do not reverse buffer after summation completion.
	// We expect that required space is 1 + max input number size because summation process may overflow.
	// To write sum output we create a view to this buffer to write its contents to stdout
	using SumBuffer = std::array<char, 1 + kMaxDigits>;

private:
	common::InputStream &input;
	common::OutputStream &output;

	Number left;
	Number right;
	SumBuffer sum_buffer;

private:
	/**
 	* @brief Reads number from stream to buffer as plain string
 	* @throw std::exception If reading failed or length preconditions are not met
 	* @warning Does not check number contents
 	*/
	void read_number(Number &number) noexcept(false);

	/**
 	* @brief Sums two numbers and writes summation result from end to begin of summation buffer
 	* @details We use such kind of murky logic to not allocate or reverse output buffer
 	* @return Length of summation buffer actual length, length being counting from end of buffer
 	* @throw std::exception If left or right numbers are invalid
 	*/
	[[nodiscard]] std::size_t sum_numbers() noexcept(false);

	/**
 	* @brief Prints summation result into output
 	* @param case_number Number of case
 	* @param sum_length Actual length of summation string
 	*/
	void print_case(std::size_t case_number, std::size_t sum_length) noexcept;

private:
	/**
 	* @brief Transforms char to it's number representation
 	* @throw std::exception If symbol is out of digits range
 	*/
	[[nodiscard]] static std::uint8_t as_digit(char symbol) noexcept(false);
};

}  // namespace task_one
