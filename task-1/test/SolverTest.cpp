/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 2:18 PM
 * \brief: 
 */

#include <gtest/gtest.h>

#include <Solver.h>

namespace {

using namespace task_one;
class SolverTest : public testing::Test
{};

TEST_F(SolverTest, ProvidedExample)
{
	std::stringstream input, output;

	input << "2\n"
	         "1 2\n"
	         "112233445566778899 998877665544332211";
	const std::string expected =
	    "Case 1:\n"
	    "1 + 2 = 3\n"
	    "\n"
	    "Case 2:\n"
	    "112233445566778899 + 998877665544332211 = 1111111111111111110\n\n";

	Solver{input, output}.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSumMaxLength)
{
	std::stringstream input, output;

	std::string left(Solver::kMaxDigits, '1');
	std::string right(Solver::kMaxDigits, '2');
	std::string sum(Solver::kMaxDigits, '3');

	input << "1\n" << left << " " << right;
	const std::string expected = "Case 1:\n" + left + " + " + right + " = " + sum + "\n\n";
	
	Solver{input, output}.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldHandleCarry)
{
	std::stringstream input, output;
	
	std::string left{'1'};
	std::string right(Solver::kMaxDigits, '9');
	std::string sum = std::string{'1'} + std::string(Solver::kMaxDigits, '0');

	input << "1\n" << left << " " << right;
	const std::string expected = "Case 1:\n" + left + " + " + right + " = " + sum + "\n\n";
	
	Solver{input, output}.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSumMaxNumbers)
{
	std::stringstream input, output;
	
	std::string left(Solver::kMaxDigits, '9');
	std::string right(Solver::kMaxDigits, '9');
	std::string sum = std::string{'1'} + std::string(Solver::kMaxDigits - 1, '9') + '8';
	
	input << "1\n" << left << " " << right;
	const std::string expected = "Case 1:\n" + left + " + " + right + " = " + sum + "\n\n";
	
	Solver{input, output}.solve();
	ASSERT_EQ(output.str(), expected);
}

}  // namespace
