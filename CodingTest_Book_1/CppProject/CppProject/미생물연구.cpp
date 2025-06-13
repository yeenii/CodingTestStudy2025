#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include <stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;

const int N_MAX=20;
const int Q_MAX = 55;

int N, Q;
int r1, c1, r2, c2;
int expGrid[N_MAX][N_MAX]; //���� ��� ���
int newGrid[N_MAX][N_MAX];

bool visited[N_MAX][N_MAX];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int countMicro[Q_MAX];

int microCount[Q_MAX];

int bfsConnectMicro(int row, int col, int idx)
{
	queue<pair<int, int>> que;

	que.push({row, col});
	visited[row][col] = false;

	while (!que.empty())
	{
		int currentRow = que.front().first;
		int currentCol = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextRow = currentRow + dr[i];
			int nextCol = currentCol + dc[i];

			if (nextRow < 0 || nextRow >= N || nextCol < 0 || nextCol >= N)
				continue;

			if (visited[nextRow][nextCol])
				continue;

			if (expGrid[nextRow][nextCol]==0)
				continue;

			if (idx == expGrid[nextRow][nextCol])
			{
				que.push({nextRow,nextCol});
				visited[nextRow][nextCol] = true;
			}
		}
	}

	return idx;
}
void insertMicro(int r1, int c1, int r2, int c2, int index)
{
	//(1) ���ο� �̻��� ����
	for (int i = r1; i < r2; i++)
	{
		for (int j = c1; j < c2; j++)
		{
			expGrid[i][j] = index;
		}
	}

	//visited �ʱ�ȭ
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			visited[i][j]=false;
		}
	}

	for (int i = 1; i <= index; i++)
	{
		countMicro[i] = 0;
	}

	

	//(2) ���� ������ �ִ��� ��
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (expGrid[i][j] == 0)
				continue;

			if (visited[i][j]) //**������ ����
				continue;

			int currentIdx = expGrid[i][j];//**

			bfsConnectMicro(i, j, currentIdx); //**���� �� index�� ���� bfs ����
			//cout << id << endl;
			countMicro[currentIdx]++; //���� ���� ���� 
		}
	}


	//cout << countMicro[1] << endl;
	//cout << countMicro[2] << endl;
	//cout << countMicro[3] << endl;
	
	
	for (int idx = 1; idx <= index; idx++)
	{
		if (countMicro[idx] >= 2)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if(expGrid[i][j]== idx) //**
						expGrid[i][j] = 0;
				}
			}
		}
	}

	/*for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << expGrid[i][j] << " ";
		}
		cout << endl;

	}
	cout << endl;*/
	
}

void moveMicro(int index)
{
	//���ο� ��� ��� �ʱ�ȭ
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			newGrid[i][j] = 0;
		}
	}

	//�켱����
	vector<pair<int, int>> microArray;

	//** �� �̻��� ���� ���� ���� ���� �ʱ�ȭ
	for (int i = 1; i <= index; i++)
	{
		microCount[i] = 0;
	}

	for (int idx = 1; idx <= index; idx++)
	{
		int count = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (expGrid[i][j] == idx)
					count++;
			}
		}
		if (count == 0)
			continue;
		microArray.push_back({-count,idx}); //���� ��� ���� ũ�� - ���� ���Ե� ����
		microCount[idx] = count;
		//cout << microCount[idx] << endl;
	}
	sort(microArray.begin(), microArray.end());
	
	/*for (auto micro : microArray)
	{
		cout << micro.first << " " << micro.second << endl;
	}*/
	

	for (auto micro : microArray) //�켱���� ��� �̻������� �ű��
	{
		int idx = micro.second; //���� �̻��� ���� id 
		//cout << "idx: " << idx << endl;

		pair<int, int> maxPoint = { std::numeric_limits<int>::min(),std::numeric_limits<int>::min() };
		pair<int, int> minPoint = { std::numeric_limits<int>::max(),std::numeric_limits<int>::max() };

		//��� �ڽ� ���ϴ�, ���� ��ǥ ���ϱ� 
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (idx == expGrid[i][j])
				{
					minPoint.first = min(minPoint.first, i);
					minPoint.second = min(minPoint.second, j);
					maxPoint.first = max(maxPoint.first, i);
					maxPoint.second = max(maxPoint.second, j);
				}
				
			}
		}

		//cout << "minRow: " << minPoint.first << "minCol: " << minPoint.second << endl;
		//cout << "maxRow: " << maxPoint.first << "maxCol: " << maxPoint.second << endl;
		//cout << RowCount << " " << ColCount << endl;

		int RowCount = maxPoint.first - minPoint.first +1; //���ڽ� ��
		int ColCount = maxPoint.second - minPoint.second + 1; //���ڽ� ��
		
		//**
		for (int i = 0; i <= N-RowCount; i++)
		{
			bool canPlaceRow = false;
			for (int j = 0; j <= N-ColCount; j++)
			{
				bool canPlaceCol = true;
				for (int row = 0; row < RowCount; row++)
				{
					for (int col = 0; col < ColCount; col++)
					{
						//���� �̻��� ������ �ƴ� ��� �ǳʶٱ�
						int oriRow = minPoint.first + row;
						int oriCol = minPoint.second + col;
						//cout << oriRow << " " << oriCol << endl;

						if (expGrid[oriRow][oriCol] != idx)
							continue;

						if (newGrid[i + row][j + col] != 0) //���ο� �׸��忡 ������ ���� ������ ����ִ��� üũ
						{
							canPlaceCol = false;
							break;
						}

					}
					if (!canPlaceCol)
						break;
				}
				
				if (canPlaceCol)
				{
					//���ο� ��� ��⿡ �ű��
					for (int row = 0; row < RowCount; row++)
					{
						for (int col = 0; col < ColCount; col++)
						{
							//���� �̻��� ������ �ƴ� ��� �ǳʶٱ�
							int oriRow = minPoint.first + row;
							int oriCol = minPoint.second + col;
							//cout << oriRow << " " << oriCol << endl;

							if (expGrid[oriRow][oriCol] != idx)
								continue;

							//�� ��� ��⿡ ����
							newGrid[i + row][j + col] = idx;


						}
					}
					canPlaceRow = true;
					break;
				}
			}
			if (canPlaceRow)
				break;
		}

		/*for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << newGrid[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;*/

	}
		
	//expGrid ������Ʈ
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			expGrid[i][j] = newGrid[i][j];
		}
	}

}

void adjacentMicro(int index)
{
	bool isAdjacent[Q_MAX][Q_MAX] = {false}; //������ ���� A, B ��� �迭

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int nextRow = i + dr[k];
				int nextCol = j + dc[k];

				if (expGrid[i][j] != expGrid[nextRow][nextCol])
				{
					//���� A, B�� �ε��� ����
					int diffA = expGrid[i][j];
					int diffB = expGrid[nextRow][nextCol];

					isAdjacent[diffA][diffB] = true;
					isAdjacent[diffB][diffA] = true;

				}
			}
			
		}
	}

	int result=0;
	for (int i = 1; i <= index; i++)
	{
		for (int j = i + 1; j <= index; j++)
		{
			if(isAdjacent[i][j]) //**
				result += (microCount[i] * microCount[j]);
		}
	}
	cout << result << endl;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << ": " << endl;
		
		cin >> N >> Q; //NXN ���� ũ��, Q���� ���� 
		//cout << N << Q << endl;

		//expGrid �ʱ�ȭ
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				expGrid[i][j] = 0;
			}
		}

		for (int i = 1; i <= Q; i++)
		{
			//r1, c1, r2, c2 
			cin >> r1 >> c1 >> r2 >> c2; 
			//cout << r1 << " " << c1 << " " << r2 << " " << c2 << endl;


			insertMicro(r1, c1, r2, c2, i);

			moveMicro(i);

			adjacentMicro(i);
		}

	}

	return 0;
}