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

	sort(result.begin(), result.end()); // �ߺ� ���� ���� �ݵ�� �����ؾ� ��!!
	result.erase(unique(result.begin(), result.end()), result.end());

	return result;
}

int main()
{
	vector<int> lst = { 2, 1, 3, 4, 1 }; // ���� �ʱ�ȭ

	auto result = solution(lst); // auto�� ����Ͽ� �ڵ� ����

	for (auto it = result.begin(); it != result.end(); it++) // ���� ���ĵȰ� ���
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}