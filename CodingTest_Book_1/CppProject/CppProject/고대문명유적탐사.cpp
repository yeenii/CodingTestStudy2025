#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

const int K_MAX = 15;
const int M_MAX = 320;

int k, m;
int historySpace[5][5];
int centerPoint[5][5];
int tempGrid[5][5];
bool visited[5][5];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = { 0, 0, -1, 1 };

queue<int> artifactList;
vector<pair<int, pair<int, int>>>grid[9];

struct rotationResults{
	int size;
	int angle;
	int col;
	int row;
	int index;
};

vector<rotationResults> rtResults;

vector<pair<int, int>> bfs(int val , int row, int col)
{
	queue<pair<int, int>> que;
	vector<pair<int, int>> group; //유적 개수 담음

	que.push({ row, col });
	visited[row][col] = true;
	group.push_back({ row,col });

	while (!que.empty())
	{
		int currentRow = que.front().first;
		int currentCol = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++)
		{
			int nextRow = currentRow + dr[i];
			int nextCol = currentCol + dc[i];

			if (tempGrid[currentRow][currentCol] == tempGrid[nextRow][nextCol])
			{
				que.push({nextRow, nextCol});
				visited[nextRow][nextCol] = true;
				group.push_back({ nextRow,nextCol });
			}
		}

	}

	return group;
}

int rotate90(int index, int centerRow, int centerCol, bool isApply)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tempGrid[i][j] = historySpace[i][j];
		}
	}

	//1. 90도 회전
	for (int i = 0; i < 9; i++)
	{
		int val = grid[index][i].first;

		int r = grid[index][i].second.first - centerRow;
		int c = grid[index][i].second.second - centerCol;
		
		int nr = centerRow + c;
		int nc = centerCol - r;

		tempGrid[nr][nc] = val;

	}

	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << tempGrid[i][j]<<" ";
		}
		cout << endl;
	}*/

	//2. BFS로 유물 획득
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			visited[i][j] = false; //방문 여부 초기화

		}
	}

	int fragileNum = 0; //90도 회전한 그리드의 총 유적 개수
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (visited[i][j])
				continue;

			vector < pair<int, int >> groupCnt = bfs(tempGrid[i][j], i, j); //똑같은 유물 개수 리턴

			//유물 획득 3개 이상인 경우 
			if (groupCnt.size() >= 3)
			{
				fragileNum += groupCnt.size();

				for (int k = 0; k < groupCnt.size(); k++) //3개 이상인 유물 획득의 좌표
				{
					int row = groupCnt[k].first;
					int col = groupCnt[k].second;
					tempGrid[row][col] = 0; //3개 이상인 경우 0으로 초기화
				}
			}
		}
	}

	//적용 여부
	if (isApply)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				historySpace[i][j] = tempGrid[i][j];
			}
		}
	}

	return fragileNum;
}

int rotate180(int index, int centerRow, int centerCol, bool isApply)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tempGrid[i][j] = historySpace[i][j];
		}
	}

	//1. 180도 회전
	for (int i = 0; i < 9; i++)
	{
		int val = grid[index][i].first;

		int r = grid[index][i].second.first - centerRow;
		int c = grid[index][i].second.second - centerCol;

		int nr = centerRow - r;
		int nc = centerCol - c;

		tempGrid[nr][nc] = val;

	}

	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << tempGrid[i][j]<<" ";
		}
		cout << endl;
	}*/

	//2. BFS로 유물 획득
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			visited[i][j] = false; //방문 여부 초기화

		}
	}

	int fragileNum = 0; //90도 회전한 그리드의 총 유적 개수
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (visited[i][j])
				continue;

			vector < pair<int, int >> groupCnt = bfs(tempGrid[i][j], i, j); //똑같은 유물 개수 리턴

			//유물 획득 3개 이상인 경우 
			if (groupCnt.size() >= 3)
			{
				fragileNum += groupCnt.size();

				for (int k = 0; k < groupCnt.size(); k++) //3개 이상인 유물 획득의 좌표
				{
					int row = groupCnt[k].first;
					int col = groupCnt[k].second;
					tempGrid[row][col] = 0; //3개 이상인 경우 0으로 초기화
				}
			}
		}
	}

	//적용 여부
	if (isApply)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				historySpace[i][j] = tempGrid[i][j];
			}
		}
	}

	return fragileNum;
}

int rotate270(int index, int centerRow, int centerCol, bool isApply)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tempGrid[i][j] = historySpace[i][j];
		}
	}

	//1. 270도 회전
	for (int i = 0; i < 9; i++)
	{
		int val = grid[index][i].first;

		int r = grid[index][i].second.first - centerRow;
		int c = grid[index][i].second.second - centerCol;

		int nr = centerRow - c;
		int nc = centerCol + r;

		tempGrid[nr][nc] = val;

	}

	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << tempGrid[i][j]<<" ";
		}
		cout << endl;
	}*/

	//2. BFS로 유물 획득
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			visited[i][j] = false; //방문 여부 초기화

		}
	}

	int fragileNum = 0; //90도 회전한 그리드의 총 유적 개수
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (visited[i][j])
				continue;

			vector < pair<int, int >> groupCnt = bfs(tempGrid[i][j], i, j); //똑같은 유물 개수 리턴

			//유물 획득 3개 이상인 경우 
			if (groupCnt.size() >= 3)
			{
				fragileNum += groupCnt.size();

				for (int k = 0; k < groupCnt.size(); k++) //3개 이상인 유물 획득의 좌표
				{
					int row = groupCnt[k].first;
					int col = groupCnt[k].second;
					tempGrid[row][col] = 0; //3개 이상인 경우 0으로 초기화
				}
			}
		}
	}

	//적용 여부
	if (isApply)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				historySpace[i][j] = tempGrid[i][j];
			}
		}
	}

	return fragileNum;
}

void turnGrid()
{

	//중심좌표
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			centerPoint[i][j] = 1;
		}
	}

	//3x3그리드 구하기
	int cnt=0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (centerPoint[i][j] == 1)
			{
				//3x3그리드 저장
				for (int row = i - 1; row <= i + 1; row++)
				{
					for (int col = j - 1; col <= j + 1; col++)
					{
						int val = historySpace[row][col];

						grid[cnt].push_back({ val,{row,col}});
					}
				}
				cnt++;
			}
		}
	}

	for (int i = 0; i < 9; i++) //9번 턴
	{
		int centerRow = grid[i][4].second.first;
		int centerCol = grid[i][4].second.second;
		cout << centerRow << centerCol << endl;

		int fragile90 = rotate90(i, centerRow, centerCol,false); //90도
		int fragile180 = rotate180(i, centerRow, centerCol, false); //180도
		int fragile270 = rotate270(i, centerRow, centerCol, false); //270도

		//우선 순위별 정렬
		rtResults.push_back({ fragile90, 90, centerRow, centerCol, i});
		rtResults.push_back({ fragile180, 180, centerRow, centerCol, i });
		rtResults.push_back({ fragile270, 270, centerRow, centerCol, i });

		sort(rtResults.begin(), rtResults.end(), [](const rotationResults& a, const rotationResults& b) {
			if (a.size != b.size)
				return a.size > b.size;
			if (a.angle != b.angle)
				return a.angle < b.angle;
			if (a.col != b.col)
				return a.col < b.col;
			if (a.row != b.row)
				return a.row < b.row;
			});

		if (rtResults[0].size == 0)
			continue;

		//유물 최대 구함
		rotationResults best = rtResults[0];

		int finalBest = 0;
		if (best.angle == 90)
			finalBest= rotate90(i, centerRow, centerCol, true);
		else if(best.angle == 180)
			finalBest = rotate180(i, centerRow, centerCol, true);
		else if (best.angle == 270)
			finalBest = rotate270(i, centerRow, centerCol, true);
	}
	

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << historySpace[i][j]<<" ";
		}
		cout << endl;
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
		cin >> k >> m;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cin >> historySpace[i][j];
				centerPoint[i][j] = 0;
			}
		}

		for (int i = 0; i < m; i++)
		{
			int artifact;
			cin >> artifact;
			artifactList.push(artifact);
		}

		turnGrid();
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}