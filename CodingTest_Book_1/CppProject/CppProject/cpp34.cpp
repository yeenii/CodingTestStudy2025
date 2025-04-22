#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int solution(vector<int> nums)
{
	int answer = 0;
	unordered_set<int> arr; //중복 자동 제거

	for (int i = 0; i < nums.size(); i++)
	{
		arr.insert(nums[i]);
	}
	

	return min(nums.size() / 2,arr.size());

}

int main()
{
	vector<int> nums = { 3,3,3,2,2,2 };
	int result = solution(nums);
	cout << result << endl;
	return 0;
}