/*
1. 해시 테이블 생성: arr 원소를 해시테이블 인덱스로 설정하고, 값은 원소유뮤에 따라 0 또는 1로 처리
2. `target - 원소 == 해시테이블 인덱스` 일 경우 true, 아니면 false
   - 중복 원소 없음
*/

#include<iostream>
#include<vector>

using namespace std;

bool solution(vector<int> arr, int target)
{
	//1. 해시테이블 생성
	vector<int> hash;
	hash.assign(target + 1, 0); //해시테이블 크기 설정 & 0으로 초기화

	for (int i = 0; i <arr.size(); i++)
	{
		//arr 원소가 target보다 작거나 같은 경우에만 해시테이블에 저장. -> 해시테이블 크기보다 더 저장하지 않기 위해서
		if(arr[i]<=target)
			hash[arr[i]] = 1;
		
	}

	//2. 두개의 수 더해서 특정 값 만들어지는지 검사
	for (int i = 0; i < arr.size(); i++)
	{
		int n = target - arr[i];
		
		//중복 원소 여부
		if (arr[i] == n)
			continue;

		//`target-원소 = 해시테이블 인덱스` 일 경우 true
		if (hash[n] == 1)
			return true;
		else
			continue;

	}

	return false; //arr 배열 다 돌아도 없는 경우 false

}

int main()
{
	/*vector<int> arr = { 1,2,3,4,8 };
	int target = 6;*/

	vector<int> arr = { 2, 3, 5, 9 };
	int target = 10;

	bool result= solution(arr, target);

	cout << result << endl;
	return 0;
}