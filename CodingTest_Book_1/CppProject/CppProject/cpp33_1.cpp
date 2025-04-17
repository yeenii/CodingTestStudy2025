#include<iostream>
#include<vector>

using namespace std;

vector<int> arr;
vector<int> rankData;

//*경로 압축, 랭크기반 알고리즘 적용한 결과

int find(int x)
{
	//자기자신이 루트노드
	if (arr[x] == x)
	{
		return x;
	}

	/*
	만약 3-> 2 -> 1 -> 0
	find(3) -> find(2) -> find(1) -> find(0)
	다시 저장하면 find(3)= 0, find(2)=0,find(1)=0, find(0)=0 -> 경로압축
	저장 안하면 find(3) -> find(2) -> find(1) -> find(0)다 돌고 0 반환
	*/
	arr[x] = find(arr[x]); // 다 돌고 루트노드 값 반환.

	return arr[x];
}

vector<bool>solution(int k, vector<vector<char>>operations)
{
	vector<bool> result;

	arr.assign(k, 0);
	rankData.assign(k, 0);

	for (int i = 0; i < k; i++)
	{
		arr[i] = i;
	}

	for (auto op : operations)
	{
		//char -> int
		int x = op[1] - '0';
		int y = op[2] - '0';

		if (op[0] == 'u')
		{
			int root_x = find(x);
			int root_y = find(y);

			//유니온 연산 - 아무 집합의 루트노드로 연결
			if (root_x != root_y)
			{
				if (rankData[root_x] > rankData[root_y])
					arr[root_y] = root_x; //랭크가 큰 x트리에 y트리를 붙임
				else if (rankData[root_x] < rankData[root_y])
					arr[root_x] = root_y; //랭크가 큰 y트리에 x트리를 붙임
				else { //랭크가 동일한 경우
					arr[root_y] = root_x; //x에 y 연결하고 
					rankData[root_x]++; //x의 랭크를 +1함
				}
			}

		}
		else if (op[0] == 'f')
		{
			int root_x = find(x);
			int root_y = find(y);

			if (root_x == root_y)
				result.push_back(true);
			else
				result.push_back(false);
		}
	}

	return result;
}

int main()
{
	int k = 3;
	vector<vector<char>> operations = { {'u','0','1'},{'u','1','2'}, {'f','0','2'} }; //result = {true}
	//vector<vector<char>> operations = { {'u','0','1'},{'u','2','3'}, {'f','0','1'},{'f','0','2'}}; // result = {true, false}

	auto result = solution(k, operations);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return 0;
}