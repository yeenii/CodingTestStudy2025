#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

vector<int> solution(vector<int> numbers)
{
	sort(numbers.begin(), numbers.end());

	vector<int> result;

	for (int i = 0; i < numbers.size(); i++)
	{
		for (int j = i + 1; j < numbers.size(); j++)
		{
			result.push_back(numbers[i] + numbers[j]);
		}

	}

	sort(result.begin(), result.end()); // 중복 제거 전에 반드시 정렬해야 함!!
	result.erase(unique(result.begin(), result.end()), result.end());

	return result;
}

int main()
{
	vector<int> lst = { 2, 1, 3, 4, 1 }; // 벡터 초기화

	auto result = solution(lst); // auto를 사용하여 자동 감지

	for (auto it = result.begin(); it != result.end(); it++) // 벡터 정렬된거 출력
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}