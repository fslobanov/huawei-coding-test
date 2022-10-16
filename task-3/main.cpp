/*
 * \author: Lobanov F.S.
 * \date: 10/14/22
 * \time: 12:26 PM
 * \brief: 
 */

#include <Solver.h>

/*#include <bits/stdc++.h>
using namespace std;
void permutationUtil(vector<int> &nums, const int depth, const int nums_size, vector<vector<int>> &answer){
	if(depth == nums_size){
		answer.push_back(nums);
	}
	for(int index = depth; index < nums_size; index++){
		std::cout << "d-" << depth << " i-" << index << " s-" << nums_size << std::endl;
		
		swap(nums[depth], nums[index]);
		permutationUtil(nums, depth +1, nums_size, answer);
		swap(nums[depth], nums[index]);
	}
}
vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> answer;
	int numsSize = nums.size();
	permutationUtil(nums, 0, numsSize, answer);
	return answer;
}
int main(){
	vector<int> nums({1, 2, 3});
	vector<vector<int>> answer = permute(nums);
	for(const auto&perm : answer){
		for(auto item : perm)
			cout<< item <<" ";
		cout<<"\t";
	}
}*/

auto main() noexcept -> signed
try {
	task_three::Solver{std::cin, std::cout}.solve();
	return EXIT_SUCCESS;
} catch(const std::exception &exception) {
	std::cout << "An error occurred: " << exception.what() << std::endl;
	return EXIT_FAILURE;
}
