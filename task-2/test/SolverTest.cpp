/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 2:18 PM
 * \brief: 
 */

#include <gtest/gtest.h>

#include <Solver.h>

namespace {

using namespace task_two;

class SolverTest : public testing::Test
{
public:
	SolverTest()
	    : solver{input, output}
	{
	}

public:
	void SetUp() override
	{
		input.clear();
		output.clear();
	}

public:
	std::stringstream input;
	std::stringstream output;
	Solver solver;
};

TEST_F(SolverTest, ShouldSolveProvidedExample)
{
	input << "2 10\n"
	         "100\n"
	         "2\n"
	         "0 0";

	const std::string expected = "Case 1: 8\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSolveMultipleCases)
{
	input << "2 10\n"
	         "100\n"
	         "2\n"

	         "2 10\n"
	         "100\n"
	         "2\n"

	         "2 10\n"
	         "100\n"
	         "2\n"

	         "0 0";

	const std::string expected =
	    "Case 1: 8\n\n"
	    "Case 2: 8\n\n"
	    "Case 3: 8\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShoudSolveOverflow)
{
	input << "1 10\n"
	         "100\n"
	         "0 0";

	const std::string expected = "Case 1: 0\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSolve)
{
	input << "3 66\n"
	         "1\n"
	         "15\n"
	         "35\n"
	         "0 0";

	const std::string expected = "Case 1: 66\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSolve1)
{
	input << "3 55\n"
	         "1\n"
	         "10\n"
	         "2\n"
	         "0 0";

	const std::string expected = "Case 1: 40\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSolve2)
{
	input << "3 55\n"
	         "40\n"
	         "5\n"
	         "7\n"
	         "0 0";

	const std::string expected = "Case 1: 55\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, ShouldSolveAnyBoundIfNumbersAvailable)
{
	for(auto value{0u}; value <= 40; ++value) {
		input.clear();
		output.str("");

		const auto value_string = std::to_string(value);

		input << "10"
		      << " " << value_string
		      << "\n"
		         "10\n"
		         "9\n"
		         "8\n"
		         "7\n"
		         "6\n"
		         "5\n"
		         "4\n"
		         "3\n"
		         "2\n"
		         "1\n"
		         "0 0";

		const std::string expected = "Case 1: " + value_string + "\n\n";

		solver.solve();
		ASSERT_EQ(output.str(), expected);
	}
}

TEST_F(SolverTest, ShouldSolveWorstCase)
{
	input << std::to_string(task_two::Solver::kNumbersLimit)
	      << " " << std::to_string(task_two::Solver::kUpperBoundLimit)
	      << "\n";
		
	for(auto number{1u}; number <= Solver::kNumbersLimit; ++ number)
	{
		input << std::to_string(number) << "\n";
	}
	input << "0 0";
	
	const std::string expected = "Case 1: " + std::to_string(4 * Solver::kNumbersLimit) + "\n\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

}  // namespace
