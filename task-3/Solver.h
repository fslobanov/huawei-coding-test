/*
 * \author: Lobanov F.S.
 * \date: 10/15/22
 * \time: 3:14 PM
 * \brief: 
 */

#pragma once

#include <common.h>

namespace task_three {

class Solver final
{
public:
	Solver(common::InputStream &input, common::OutputStream &output);
	void solve() noexcept(false);
	
private:
	common::InputStream &input;
	common::OutputStream &output;
};

}  // namespace task_three