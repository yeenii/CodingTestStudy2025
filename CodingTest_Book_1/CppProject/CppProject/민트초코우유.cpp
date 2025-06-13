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

bool defense[N_MAX][N_MAX]; //������

int countBasicFood(int food)
{
	int cnt = 0;

	if (food & 1) //T(��Ʈ)
		cnt++;

	if (food & 2) //2(����)
		cnt++;

	if (food & 4) //4(����)
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
	//���� ���� ���� ����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int cnt = countBasicFood(foodGrid[i][j]); //**��ǥ�� �ƴ϶� �� ���� ���� �Ѱ��ֱ�
			foodCount[i][j] = cnt;

		}
	}
	
	//(1) ������ �л���� �ź� ������ ���� ��� �׷� ����
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = false;
		}

	}

	group.clear(); //�׷� ���� ���� �ʱ�ȭ
	leaderList.clear(); //��ǥ�� ����Ʈ ���� �ʱ�ȭ**

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (visited[i][j])
				continue;

			int count = bfsGroup(foodGrid[i][j], i, j);
			//cout << count << endl;

			sort(group.begin(), group.end());

			/*for (auto g : group)
			{
				cout << g.first << endl;
			}*/

			int leaderRow = group[0].second.first; //row
			int leaderCol = group[0].second.second; //row
			//int faith = group[0].first; //row
			//cout << faith << endl;
			//cout << leaderRow << " " << leaderCol << endl;

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
			}
			cout << endl;*/

			group.clear(); //�ʱ�ȭ
		}

	} 

	sort(leaderList.begin(), leaderList.end());

	//for (int i = 0; i < leaderList.size(); i++)
	//{
	//	cout << leaderList[i].first<<endl; //�������İ��� ���� ��
	//	cout << leaderList[i].second.first<<endl; //�žӽ� ū ��
	//	cout << leaderList[i].second.second.first << " " << leaderList[i].second.second.second << endl; //col ���� �� 
	//}
	
}

void FinalResult()
{
	int result[8] = {0};

	for (int k = 1; k <= 7; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (foodGrid[i][j] == k)
					result[k] += faithGrid[i][j];
			}
		}

	}
	
	cout << result[7] << " " << result[3] << " " << result[5] << " " << result[6] << " " <<
		result[4] << " " << result[2] << " " << result[1] << endl;
}

void dinnerCompute()
{
	for (auto leader : leaderList) //�켱���� �� ��ǥ ���� 
	{
		int leaderR = leader.second.second.first;
		int leaderC = leader.second.second.second;
		//cout << "leaderR: " << leaderR << " " << "leaderC: " << leaderC << endl;

		if (defense[leaderR][leaderC]) //�����ڰ� �������̸�, �������� ����
			continue;

		int faith = -leader.second.first; //�žӽ�
		//cout << faith << endl;

		int x = faith - 1; // ������
		int dir = faith % 4; //���� ���� 
		//cout << dir << endl;
		faithGrid[leaderR][leaderC] = 1; //�žӽ� 1�� 

		int currentRow = leaderR;
		int currentCol = leaderC;
		while (true)
		{
			//���� �������� ��ĭ�� ���� 
			//������ ����� ���� 
			currentRow += dr[dir];
			currentCol += dc[dir];
			//cout << currentRow << " " << currentCol << endl;

			if (currentRow >= n || currentRow < 0 || currentCol >= n || currentCol < 0) //���� ����� ����
			{
				//cout << "**" << endl;
				break;
			}
				
			if (x <= 0) //�������� 0�̵Ǹ� ����
				break;

			if (foodGrid[leaderR][leaderC] == foodGrid[currentRow][currentCol]) //�ž� ������ ���� ���
			{
				continue;
			}
			else if (foodGrid[leaderR][leaderC] != foodGrid[currentRow][currentCol]) //�ž� ������ �ٸ� ���
			{
				int y = faithGrid[currentRow][currentCol];
				if (x > y) //���� ���� 
				{
					//�����ڿ� ������ ���� ����
					foodGrid[currentRow][currentCol] =foodGrid[leaderR][leaderC];

					//������ ������ y+1 ����
					x -= y + 1;
					//���� ����� �žӽ� +1
					faithGrid[currentRow][currentCol] += 1;

					defense[currentRow][currentCol] = true; //������ 

					//������ 0�̵Ǹ� ���� 
					if (x <= 0)
						break;

				}
				else if (x <= y) // ���� ����
				{
					// ���� ����ڴ� �������� ���ı��� �ź�
					foodGrid[currentRow][currentCol] |= foodGrid[leaderR][leaderC];

					//���Ĵ������ �žӽ��� x ��ŭ ����
					faithGrid[currentRow][currentCol] += x;

					defense[currentRow][currentCol] = true; //��� ���� 

					//�������� �������� 0. ����
					x = 0;
					break;

				}
			}
		}


	}

	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << faithGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << foodGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	//��� ���
	FinalResult();
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
			}
			
		}


		for (int d = 0; d < t; d++)
		{
			//�������հ��� �ʱ�ȭ
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					foodCount[i][j] = 0;
				}
			}
			
			//������ �ʱ�ȭ
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					defense[i][j] = false;
				}
			}

			//��ħ �ð�
			morningCompute();

			//���� �ð�
			lunchCompute();

			//���� �ð�
			dinnerCompute();
		}
		
	}

	return 0;
}
