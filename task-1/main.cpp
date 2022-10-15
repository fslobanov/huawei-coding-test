/*
 * \author: Lobanov F.S.
 * \date: 10/14/22
 * \time: 12:26 PM
 * \brief:
 */

#include <Solver.h>

signed main() noexcept
try {
	task_one::Solver{std::cin, std::cout}.solve();
	return EXIT_SUCCESS;
} catch(const std::exception &exception) {
	std::cout << "An error occurred: " << exception.what() << std::endl;
	return EXIT_FAILURE;
}
