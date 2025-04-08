/*
1. 두 행렬 넘겨 받기
2. 두 행렬 곱 결과 저장할 행렬 정의 및 초기화 - assign() 메서드
3. 두 행렬 곱해서 저장할 행렬에 값 넘겨주기 - A행 * B열 * A열(B행).
*/

#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) //2차원 배열 : vector<vector<int>> 변수명
{
	vector<vector<int>> arr3;

	arr3.assign(arr1.size(), vector<int>( arr2[0].size(),0)); // assign(행, vector<int>(열, 채울 값)): 초기화

	//arr3의 크기는 3*2. A행 * B열 * A열(B행)
	for (int i = 0; i < arr1.size();i++)
	{
		for (int j = 0; j < arr2[0].size(); j++)
		{
			for (int k = 0; k < arr1[0].size(); k++)
			{
				//arr3[행][열] = arr3[3][2].
				arr3[i][j] += arr1[i][k] * arr2[k][j];  // ex) arr3[0][0] = (arr1[0][0] * arr2[0][0]) + ( arr1[0][1] * arr2[1][0]) ....
			}
		}
	}

	return arr3;
}


int main()
{
	vector<vector<int>> arr1 = { {1,4}, {3,2},{4,1} }; //3*2
	vector<vector<int>> arr2 = { {3,3}, {3,3} }; //2*2

	//vector<vector<int>> arr1 = { {2,3,2}, {4,2,4},{3,1,4} }; //3*3
	//vector<vector<int>> arr2 = { {5,4,3}, {2,4,1}, {3,1,1} }; //2*2

	auto result = solution(arr1, arr2);

	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < result[0].size(); j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}