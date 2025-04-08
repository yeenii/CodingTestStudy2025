#include<iostream>
#include<queue>

using namespace std;

int solution(int N, int K)
{
	queue<int> basket;

	//1. ť�� 1~N ��ŭ ��ȣ �ֱ�
	for (int i = 0; i < N; i++)
	{
		basket.push(i + 1);
	}

	while (basket.size() > 1) //ť�� ũ�Ⱑ 1�̻��� �� ����
	{
		for (int j = 0; j < K - 1; j++) //K ��° ��� ã�� ����, �տ� push �� pop
		{
			basket.push(basket.front());
			basket.pop();
		}

		basket.pop();
	}
	

	return basket.front();
}

int main()
{
	int N = 5;
	int K = 2;

	int result = solution(N, K);

	cout << result << endl;

	return 0;
}