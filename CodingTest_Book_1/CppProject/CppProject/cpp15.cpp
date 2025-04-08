#include<iostream>
#include<queue>

using namespace std;

int solution(int N, int K)
{
	queue<int> basket;

	//1. 큐에 1~N 만큼 번호 넣기
	for (int i = 0; i < N; i++)
	{
		basket.push(i + 1);
	}

	while (basket.size() > 1) //큐의 크기가 1이상일 때 까지
	{
		for (int j = 0; j < K - 1; j++) //K 번째 사람 찾기 위해, 앞에 push 후 pop
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