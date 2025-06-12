#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <cstdio>   // C++ ��Ÿ�Ͽ��� ��õ
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

const int N_MAX = 55;
const int T_MAX = 35;

int n, t;
char charFood[N_MAX][N_MAX];
int foodGrid[N_MAX][N_MAX];
int faithGrid[N_MAX][N_MAX];
int foodCount[N_MAX][N_MAX]; //�⺻ ���� ���� ���� ī��Ʈ 
bool visited[N_MAX][N_MAX];

int dr[4] = {-1,1,0,0};
int dc[4] = { 0,0,-1,1 };

vector<pair<int, pair<int, int>>> group;
vector<pair<int, pair<int, pair<int, int>>>> leaderList;

int countBasicFood(int row, int col)
{
	int cnt = 0;

	if (foodGrid[row][col] & 1) //T(��Ʈ)
		cnt++;

	if (foodGrid[row][col] & 2) //2(����)
		cnt++;

	if (foodGrid[row][col] & 4) //4(����)
		cnt++;

	return cnt;
}
void morningCompute()
{
	//��� �л� �žӽ� 1����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			faithGrid[i][j] += 1;
			//cout << faithGrid[i][j] << " ";
		}
		//cout << endl;
	}

}

int bfsGroup(int foodNum, int row, int col)
{
	queue<pair<int, int>> que;
	int groupCount = 1;

	que.push({row, col});
	visited[row][col] = true;
	group.push_back({ -faithGrid[row][col], {row,col} });


	while (!que.empty())
	{
		int currentRow = que.front().first;
		int currentCol = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextRow = currentRow + dr[i];
			int nextCol = currentCol + dc[i];

			if (nextRow >= n || nextRow < 0 || nextCol >= n || nextCol < 0)
				continue;
			
			if (visited[nextRow][nextCol])
				continue;

			//����� ���� ���� �ź� ������ ���ٸ�
			if (foodGrid[nextRow][nextCol]== foodNum)
			{
				que.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;
				group.push_back({ -faithGrid[nextRow][nextCol], {nextRow,nextCol} });
				groupCount++;
			}
		}
	}
	return groupCount;

}

void lunchCompute()
{
	//(1) ������ �л���� �ź� ������ ���� ��� �׷� ����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = false;
		}

	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visited[i][j])
				continue;

			int count = bfsGroup(foodGrid[i][j], i, j);
			//cout << count << endl;
			sort(group.begin(), group.end());

			int leaderRow = group[0].second.first; //row
			int leaderCol = group[0].second.second; //row

			faithGrid[leaderRow][leaderCol] += count - 1;
			for (int k = 1; k < group.size(); k++)
			{
				int gr = group[k].second.first;
				int gc = group[k].second.second;

				faithGrid[gr][gc] -= 1;

			}
			
			//��ǥ�� - �������İ��� ���� ��, �žӽ�, ��, �� ��
			leaderList.push_back({ foodCount[leaderRow][leaderCol] ,
				{-faithGrid[leaderRow][leaderCol],{leaderRow, leaderCol}}});

			/*for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					cout << faithGrid[i][j] << " ";
				}
				cout << endl;
			}*/

			group.clear(); //�ʱ�ȭ
		}

	} 

	sort(leaderList.begin(), leaderList.end());

	//for (int i = 0; i < leaderList.size(); i++)
	//{
	//	cout << leaderList[i].first<<endl; //�������İ��� ���� ��
	//	cout << leaderList[i].second.first<<endl; //�žӽ� ū ��
	//	cout << leaderList[i].second.second.first << endl; //row ���� ��
	//	cout << leaderList[i].second.second.second << endl; //col ���� �� 
	//}
	
}

void dinnerCompute()
{
	for (auto leader : leaderList)
	{
		int row = leader.second.second.first;
		int col = leader.second.second.second;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	// SWEA ���� �ÿ��� ������ �ּ� ó��!
	freopen("input.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{

		cout << "#" << test_case << " "<<endl;
		
		cin >> n >> t; //nxn, t��
		//cout << n <<" "<< t<<endl;

		for (int i = 0; i < n; i++)
		{
			string foodStr="";
			cin >> foodStr;
			for (int j = 0; j < n; j++)
			{
				charFood[i][j] = foodStr[j];
				//cout << foodGrid[i][j] << " ";
			}
			//cout << endl;
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> faithGrid[i][j];
				//cout << faithGrid[i][j]<<" ";
			}
			//cout << endl;
		}

		//���ڷ� �⺻ ���� ����
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (charFood[i][j] == 'T')
				{
					foodGrid[i][j] = 1;
				}
				else if (charFood[i][j] == 'C')
				{
					foodGrid[i][j] = 2;
				}
				else if (charFood[i][j] == 'M')
				{
					foodGrid[i][j] = 4;
				}

				int cnt = countBasicFood(i, j);
				foodCount[i][j] = cnt;
			}
			
		}

		/*for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << foodCount[i][j]<<" ";
			}
			cout << endl;
		}*/

		 
		//��ħ �ð�
		morningCompute();
		
		//���� �ð�
		lunchCompute();

		//���� �ð�
		dinnerCompute();
	}

	return 0;
}
