#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Ÿ����  bool
bool compare(int a, int b)
{
	return a > b; //a�� b ���� ũ�� 1(true) ��ȯ�ϹǷ�, ū ���ڰ� �տ� �;� �� = ��������
}

vector<int> solution(vector<int> lst)
{
	sort(lst.begin(), lst.end(), compare); // �������� ���� -> 4, 4, 3, 2, 2, 1
	lst.erase(unique(lst.begin(), lst.end()), lst.end()); //erase(unique�� ���ο� ������ ��ġ �ε��� �� 4, ���� ������ ��ġ)�� ����
	return lst;
}


int main()
{
	vector<int> lst = { 4, 2, 2, 1, 3, 4 }; // ���� �ʱ�ȭ

	auto result = solution(lst); // auto�� ����Ͽ� �ڵ� ����

	for (auto it = result.begin(); it != result.end(); it++) // ���� ���ĵȰ� ���
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}