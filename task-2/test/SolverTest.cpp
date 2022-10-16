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

TEST_F(SolverTest, ProvidedExample) {}
}  // namespace
