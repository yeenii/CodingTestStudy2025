#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int>solution(vector<int>arr)
{
	//solution �Լ����� �����迭 arr�� ������������ �����Ͽ� ��ȯ
	sort(arr.begin(), arr.end()); //�ð����⵵�� O(NlogN)�� sort �˰��� ���.
	return arr;
}

int main()
{
	vector<int> arr = {6,1 , 7}; // ���� �ʱ�ȭ

	auto result = solution(arr); // auto�� ����Ͽ� �ڵ� ����

	for (auto it = result.begin(); it != result.end(); it++) // ���� ���ĵȰ� ���
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}

// * ���� ����Ʈ : auto ���, sort�� �ڵ� ����, ���� ��� ���