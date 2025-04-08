#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int>solution(vector<int>arr)
{
	//solution 함수에서 정수배열 arr을 오름차순으로 정렬하여 반환
	sort(arr.begin(), arr.end()); //시간복잡도가 O(NlogN)인 sort 알고리즘 사용.
	return arr;
}

int main()
{
	vector<int> arr = {6,1 , 7}; // 벡터 초기화

	auto result = solution(arr); // auto를 사용하여 자동 감지

	for (auto it = result.begin(); it != result.end(); it++) // 벡터 정렬된거 출력
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}

// * 문제 포인트 : auto 사용, sort로 자동 정렬, 벡터 출력 방법