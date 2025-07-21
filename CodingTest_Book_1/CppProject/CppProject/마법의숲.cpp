#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

const int R_MAX = 80;
const int C_MAX = 80;

int R, C, K;
int c, d;
int forest[R_MAX+3][C_MAX];
int isExit[R_MAX+3][C_MAX];

//�������
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
bool visited[R_MAX+3][C_MAX];

int result;

using namespace std;

bool inRange(int row, int col)
{
	//���� �ȿ� ������ true
	return (row < R + 3 && row >= 3 && col >= 0 && col < C);
}

bool canDo(int r, int c)
{
	bool canGo = r + 1 < R + 3;
	canGo = canGo && c - 1 >= 0;
	canGo = canGo && c + 1 < C;
	canGo = canGo && (forest[r - 1][c - 1] == 0);
	canGo = canGo && (forest[r - 1][c] == 0);
	canGo = canGo && (forest[r - 1][c + 1] == 0);
	canGo = canGo && (forest[r][c - 1] == 0);
	canGo = canGo && (forest[r][c] == 0);
	canGo = canGo && (forest[r][c+1] == 0);
	canGo = canGo && (forest[r+1][c] == 0);

	return canGo;
}

int bfs(int row, int col)
{
	queue<pair<int, int>> que;

	for (int i = 0; i < R + 3; i++) //**row+3�� �ƴ϶� R+3
	{
		for (int j = 0; j < C; j++)
		{
			visited[i][j] = false;
		}
	}

	int rowMax = row; //���� ���� ���� ū ��
	//1. que�� Ǫ���ϸ�, �湮 ó��
	que.push({ row, col });
	visited[row][col] = true;

	//2.ť�� ������� �ʴٸ�
	while (!que.empty())
	{
		//ť�� ��
		int currentRow = que.front().first;
		int currentCol = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextRow = currentRow + dr[i]; //���� �Ϳ� row, col ���
			int nextCol = currentCol + dc[i];

			//���� �ȿ� ���� �ʰų�
			if (!inRange(nextRow, nextCol))
				continue;

			//�̹� �湮�� ���
			if (visited[nextRow][nextCol])
				continue;

			if ((forest[nextRow][nextCol] == forest[currentRow][currentCol]) || (isExit[currentRow][currentCol] == 1 && forest[nextRow][nextCol] != 0))
			{
				que.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;
				rowMax = max(rowMax, nextRow);
				//cout << nextRow << endl;
			}

		}
		
	}
	//cout << "rowMax: " << rowMax << endl;
	return rowMax;

}

void computeForest(int index, int row, int col, int dir)
{
	if (canDo(row+1, col)) //��
		computeForest(index, row + 1, col, dir);
	else if (canDo(row + 1, col - 1)) //��
		computeForest(index, row + 1, col - 1, (dir + 3) % 4);
	else if(canDo(row+1, col+1)) //��
		computeForest(index, row + 1, col + 1, (dir + 1) % 4);
	else
	{
		if (!inRange(row - 1, col - 1) || !inRange(row - 1, col + 1)) //���� �ȿ� ������
		{
			//�ʱ�ȭ
			for (int i = 0; i < R + 3; i++) //9
			{
				for (int j = 0; j < C; j++)//5
				{
					forest[i][j] = 0;
					isExit[i][j] = 0;
				}
			}

		}
		else { //���� �ȿ� �ִ� ���

			//cout << row << " " << col << endl;
			//���� �ȿ� ����
			forest[row][col] = index;

			//�����¿� �� ����
			for (int t = 0; t < 4; t++)
			{
				forest[row+dr[t]][col+dc[t]] = index;
			}

			isExit[row+dr[dir]][col+dc[dir]] = 1; //�ⱸ ��ġ

			//for (int i = 0; i < R + 3; i++) //9
			//{
			//	for (int j = 0; j < C; j++)//5
			//	{
			//		cout << forest[i][j] << " ";
			//	}
			//	cout << endl;
			//}

			//for (int i = 0; i < R + 3; i++) //9
			//{
			//	for (int j = 0; j < C; j++)//5
			//	{
			//		cout << isExit[i][j] << " ";
			//	}
			//	cout << endl;
			//}

			//������ ���� ��ġ ���ȣ ���� 
			result += bfs(row, col)-3+1;
		
		}
	}

}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> R >> C >> K;
		//cout << R << C << K << endl;

		//�ʱ�ȭ
		for (int i = 0; i < R + 3; i++) //9
		{
			for (int j = 0; j < C; j++)//5
			{
				forest[i][j] = 0;
				isExit[i][j] = 0;
			}
		}

		result = 0;

		for (int i = 1; i <= K; i++) //**
		{
			cin >> c >> d;
			//cout << c << d << endl;

			computeForest(i, 1, c - 1, d); //index, row, col, dir
		}

		cout << result << endl;
	}

	
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}