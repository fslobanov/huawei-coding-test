/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 2:18 PM
 * \brief: 
 */
#include <gtest/gtest.h>

#include <Solver.h>

namespace {

using namespace task_three;

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

TEST_F(SolverTest, SouldSolveProvidedExample)
{
	input << "3\n"

	         "5 5 1\n"
	         "0 0 5 5\n"

	         "5 5 2\n"
	         "0 0 3 5\n"
	         "2 0 5 5\n"

	         "30 30 5\n"
	         "0 0 30 10\n"
	         "0 10 30 20\n"
	         "0 20 30 30\n"
	         "0 0 15 30\n"
	         "15 0 30 30";

	const std::string expected =
	    "1\n"
	    "-1\n"
	    "2\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

TEST_F(SolverTest, JustCase)
{
	constexpr static auto kSize = 30;
	constexpr static auto kCount = 30;

	input << "1\n" << std::to_string(kSize) << " " << std::to_string(kSize) << " " << std::to_string(kCount) << "\n";

	for(auto count{0u}; count < kCount; ++count) {
		input << std::to_string(count) << " " << std::to_string(count) << " " << std::to_string(count + 1) << " "
		      << std::to_string(count + 1) << "\n";
	}
	const std::string expected = "-1\n";

	solver.solve();
	ASSERT_EQ(output.str(), expected);
}

}  // namespace
