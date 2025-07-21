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

//상우하좌
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
bool visited[R_MAX+3][C_MAX];

int result;

using namespace std;

bool inRange(int row, int col)
{
	//범위 안에 있으면 true
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

	for (int i = 0; i < R + 3; i++) //**row+3이 아니라 R+3
	{
		for (int j = 0; j < C; j++)
		{
			visited[i][j] = false;
		}
	}

	int rowMax = row; //현재 행이 제일 큰 행
	//1. que에 푸시하며, 방문 처리
	que.push({ row, col });
	visited[row][col] = true;

	//2.큐가 비어있지 않다면
	while (!que.empty())
	{
		//큐를 팝
		int currentRow = que.front().first;
		int currentCol = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextRow = currentRow + dr[i]; //팝한 것에 row, col 계산
			int nextCol = currentCol + dc[i];

			//범위 안에 있지 않거나
			if (!inRange(nextRow, nextCol))
				continue;

			//이미 방문한 경우
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
	if (canDo(row+1, col)) //남
		computeForest(index, row + 1, col, dir);
	else if (canDo(row + 1, col - 1)) //서
		computeForest(index, row + 1, col - 1, (dir + 3) % 4);
	else if(canDo(row+1, col+1)) //동
		computeForest(index, row + 1, col + 1, (dir + 1) % 4);
	else
	{
		if (!inRange(row - 1, col - 1) || !inRange(row - 1, col + 1)) //범위 안에 없으면
		{
			//초기화
			for (int i = 0; i < R + 3; i++) //9
			{
				for (int j = 0; j < C; j++)//5
				{
					forest[i][j] = 0;
					isExit[i][j] = 0;
				}
			}

		}
		else { //범위 안에 있는 경우

			//cout << row << " " << col << endl;
			//범위 안에 정착
			forest[row][col] = index;

			//상하좌우 순 정착
			for (int t = 0; t < 4; t++)
			{
				forest[row+dr[t]][col+dc[t]] = index;
			}

			isExit[row+dr[dir]][col+dc[dir]] = 1; //출구 위치

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

			//정령의 최종 위치 행번호 저장 
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

		//초기화
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

	
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}