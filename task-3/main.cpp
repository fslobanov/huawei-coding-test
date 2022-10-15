/*
 * \author: Lobanov F.S.
 * \date: 10/14/22
 * \time: 12:26 PM
 * \brief: 
 */

//#include <Solver.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>

signed main() noexcept
try {
	std::vector<int> v{2,5,20};
	
	auto found = std::lower_bound(v.rbegin(), v.rend(), 4, std::greater<int>{});
	
	std::cout << "#### " << *found << std::endl;
	
	
	//task_three::Solver{std::cin, std::cout}.solve();
	//return EXIT_SUCCESS;
} catch(const std::exception &exception) {
	//std::cout << "An error occurred: " << exception.what() << std::endl;
	//return EXIT_FAILURE;
}
