#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> arr;
vector<int> rankData;

void unionSet(int root1, int root2)
{
	if (root1 != root2)
	{
		if (rankData[root1] > rankData[root2])
			arr[root2] = root1;
		else if (rankData[root1] < rankData[root2])
			arr[root1] = root2;
		else
		{
			arr[root2] = root1;
			rankData[root1]++;
		}
	}
}

int findSet(int x)
{
	//루트노드가 자기자신일 경우
	if (arr[x] == x)
		return x;

	arr[x] = findSet(arr[x]); //아닐 경우, 부모노드 계속 올라가서 루트노드 찾기 //경로압축

	return arr[x];
}

vector<bool> solution(int k, vector<vector<char>> operations)
{
	vector<bool> answer;

	arr.assign(k, 0);
	rankData.assign(k, 0);

	for (int i = 0; i < k; i++)
	{
		arr[i] = i;
	}

	//유니온-파인드 연산
	for (int i = 0; i < operations.size(); i++)
	{
		//유니온 연산 - 랭크 기반 알고리즘
		if (operations[i][0] == 'u')
		{
			int root1 = operations[i][1] - '0';
			int root2 = operations[i][2] - '0';

			unionSet(root1, root2);

		}
		else if (operations[i][0] == 'f') //파인드 연산 - 경로 압축
		{
			int root1 = operations[i][1] - '0';
			int root2 = operations[i][2] - '0';

			int fin_root1 = findSet(root1);
			int fin_root2 = findSet(root2);

			if (fin_root1 == fin_root2)
				answer.push_back(true);
			else
				answer.push_back(false);
		}
	}

	return answer;

}

int main()
{
	//int k = 3;
	int k = 4;
	//vector<vector<char>> operations = { {'u','0','1'}, {'u','1','2'}, {'f','0','2'} };
	vector<vector<char>> operations = { {'u','0','1'},{'u','2','3'}, {'f','0','1'},{'f','0','2'} };
	auto result = solution(k, operations);
		
	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return 0;
}