#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//타입은  bool
bool compare(int a, int b)
{
	return a > b; //a가 b 보다 크면 1(true) 반환하므로, 큰 숫자가 앞에 와야 됨 = 내림차순
}

vector<int> solution(vector<int> lst)
{
	sort(lst.begin(), lst.end(), compare); // 내림차순 정렬 -> 4, 4, 3, 2, 2, 1
	lst.erase(unique(lst.begin(), lst.end()), lst.end()); //erase(unique로 새로운 마지막 위치 인덱스 값 4, 원래 마지막 위치)를 제거
	return lst;
}


int main()
{
	vector<int> lst = { 4, 2, 2, 1, 3, 4 }; // 벡터 초기화

	auto result = solution(lst); // auto를 사용하여 자동 감지

	for (auto it = result.begin(); it != result.end(); it++) // 벡터 정렬된거 출력
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}