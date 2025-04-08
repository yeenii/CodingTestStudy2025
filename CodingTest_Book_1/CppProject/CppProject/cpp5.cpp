/*
1. �� ��� �Ѱ� �ޱ�
2. �� ��� �� ��� ������ ��� ���� �� �ʱ�ȭ - assign() �޼���
3. �� ��� ���ؼ� ������ ��Ŀ� �� �Ѱ��ֱ� - A�� * B�� * A��(B��).
*/

#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) //2���� �迭 : vector<vector<int>> ������
{
	vector<vector<int>> arr3;

	arr3.assign(arr1.size(), vector<int>( arr2[0].size(),0)); // assign(��, vector<int>(��, ä�� ��)): �ʱ�ȭ

	//arr3�� ũ��� 3*2. A�� * B�� * A��(B��)
	for (int i = 0; i < arr1.size();i++)
	{
		for (int j = 0; j < arr2[0].size(); j++)
		{
			for (int k = 0; k < arr1[0].size(); k++)
			{
				//arr3[��][��] = arr3[3][2].
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