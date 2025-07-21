#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

const int N_MAX=55;
const int M_MAX=310;

using namespace std;

int n, m;
int sr, sc, er, ec;
int warriorPosition[M_MAX][M_MAX];
int medusaHome[N_MAX][N_MAX];
int villageGrid[N_MAX][N_MAX];
int medusaPos[N_MAX][N_MAX];
int medusaSight[N_MAX][N_MAX];

pair<int, int> parkPos;
pair<int, int> homePos;

bool visited[N_MAX][N_MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0,0,-1, 1};

int tempGrid[N_MAX][N_MAX];

bool inRange(int row, int col)
{
	return (row < n && row >= 0 && col < n && col >= 0);
}
void bfsShortRoad(int parkRow, int parkCol) 
{
	queue<pair<int, int>> que;

	//방문 처리 초기화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = false;
		}
	}

	villageGrid[parkRow][parkCol] = 0;
	que.push({ parkRow, parkCol });
	visited[parkRow][parkCol] =true;

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

			if (villageGrid[nextRow][nextCol] == 1e9+10) //도로 X 경우 건너뛰기
				continue;

			
			que.push({ nextRow,nextCol });
			visited[nextRow][nextCol] = true;
			villageGrid[nextRow][nextCol] = villageGrid[currentRow][currentCol] + 1; // 이웃 셀은 현재 셀 +1 값을 가짐
			
		}
	}
}

int sightUp(int medusaRow, int medusaCol, bool isApply)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempGrid[i][j] = 0;
		}
	}
	//(1) 기본 시야각 생성
	for (int i = medusaRow - 1; i >= 0; i--)
	{
		int left = medusaCol - (medusaRow - i);
		int right = medusaCol + (medusaRow - i);

		for (int j = left; j <= right; j++)
		{
			tempGrid[i][j] = 1;
		}
	}

	//(2) 전사 뒤 삭제

	// 중앙 직선 삭제
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!inRange(i, j))
				continue;

			if (tempGrid[i][j]==1 && warriorPosition[i][j] == 1)
			{
				for (int x = i - 1; x >= 0; x--)
				{
					tempGrid[x][j] = 0; //**
				}
			}
		}
	}

	//대각선 삭제 
	for (int i = medusaRow - 1; i >= 0; i--)
	{
		int left = medusaCol - (medusaRow - i);
		int right = medusaCol + (medusaRow - i);

		//왼쪽 부분
		for (int j = left; j < medusaCol; j++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i - 1][j] = 0;
				//대각선 삭제 
				if(j>=0)
					tempGrid[i - 1][j - 1] = 0;
			}

		}

		//오른쪽 부분
		for (int j = medusaCol+1; j <= right; j++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i - 1][j] = 0;
				//대각선 삭제 
				if (j < n)
					tempGrid[i - 1][j + 1] = 0;
			}

		}
	}

	//시야 내 전사 수 계산 
	int cntWarrior = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tempGrid[i][j] == 1 && warriorPosition[i][j]==1)
			{
				cntWarrior++;
			}
		}
	}

	if (isApply)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				medusaSight[i][j] = tempGrid[i][j];
			}
		}
	}
	/*cout << cntWarrior << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << tempGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	return cntWarrior;
}

int sightDown(int medusaRow, int medusaCol, bool isApply)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempGrid[i][j] = 0;
		}
	}
	//(1) 기본 시야각 생성
	for (int i = medusaRow + 1; i < n; i++)
	{
		int left = medusaCol + (medusaRow - i); //+- 체인지
		int right = medusaCol - (medusaRow - i);

		for (int j = left; j <= right; j++)
		{
			tempGrid[i][j] = 1;
		}
	}

	//(2) 전사 뒤 삭제

	// 중앙 직선 삭제
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!inRange(i, j))
				continue;

			if (tempGrid[i][j] == 1 && warriorPosition[i][j] == 1)
			{	
				for (int x = i + 1; x < n; x++) // 전사의 뒤 삭제
				{
					tempGrid[x][j] = 0;
				}
			}
		}
	}

	//대각선 삭제 
	for (int i = medusaRow +1 ; i <n; i++)
	{
		int left = medusaCol + (medusaRow - i);
		int right = medusaCol - (medusaRow - i);

		//왼쪽 부분
		for (int j = left; j < medusaCol; j++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i + 1][j] = 0;
				//대각선 삭제 
				if (j >= 0)
					tempGrid[i + 1][j - 1] = 0;
			}

		}

		//오른쪽 부분
		for (int j = medusaCol + 1; j <= right; j++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i + 1][j] = 0;
				//대각선 삭제 
				if (j < n)
					tempGrid[i + 1][j + 1] = 0;
			}

		}
	}

	//시야 내 전사 수 계산 
	int cntWarrior = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tempGrid[i][j] == 1 && warriorPosition[i][j] == 1)
			{
				cntWarrior++;
			}
		}
	}

	if (isApply)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				medusaSight[i][j] = tempGrid[i][j];
			}
		}
	}
	/*cout << "시야 내 전사 수:" << cntWarrior << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << tempGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	
	return cntWarrior;
}

int sightLeft(int medusaRow, int medusaCol, bool isApply)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempGrid[i][j] = 0;
		}
	}
	//(1) 기본 시야각 생성
	for (int j = medusaCol -1; j >=0; j--)
	{
		int left = medusaRow - (medusaCol - j); //x-(y-i)
		int right = medusaRow + (medusaCol - j);

		for (int i = left; i <= right; i++)
		{
			tempGrid[i][j] = 1;
		}
	}

	

	//(2) 전사 뒤 삭제

	// 중앙 직선 삭제
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!inRange(i, j))
				continue;

			if (tempGrid[i][j] == 1 && warriorPosition[i][j] == 1)
			{
				for (int y = j - 1; y >= 0; y--)
				{
					tempGrid[i][y] = 0; //**
				}
			}
		}
	}

	
	//대각선 삭제 
	for (int j = medusaCol - 1; j >= 0; j--)
	{
		int left = medusaRow - (medusaCol - j); //x-(y-i)
		int right = medusaRow + (medusaCol - j);

		for (int i = left; i < medusaRow; i++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i][j-1] = 0;
				//대각선 삭제 
				if (i >= 0)
					tempGrid[i - 1][j - 1] = 0;
			}

		}

		//오른쪽 부분
		for (int i = medusaRow + 1; i <= right; i++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i][j-1] = 0;
				//대각선 삭제 
				if (i < n)
					tempGrid[i + 1][j - 1] = 0;
			}

		}
	}

	//시야 내 전사 수 계산 
	int cntWarrior = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tempGrid[i][j] == 1 && warriorPosition[i][j] == 1)
			{
				cntWarrior++;
			}
		}
	}
	/*cout << cntWarrior << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << tempGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	if (isApply)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				medusaSight[i][j] = tempGrid[i][j];
			}
		}
	}
	
	return cntWarrior;
}

int sightRight(int medusaRow, int medusaCol, bool isApply)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tempGrid[i][j] = 0;
		}
	}
	//(1) 기본 시야각 생성
	for (int j = medusaCol + 1; j < n; j++)
	{
		int left = medusaRow + (medusaCol - j); 
		int right = medusaRow - (medusaCol - j);

		for (int i = left; i <= right; i++)
		{
			tempGrid[i][j] = 1;
		}
	}

	//(2) 전사 뒤 삭제

	// 중앙 직선 삭제
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!inRange(i, j))
				continue;

			if (tempGrid[i][j] == 1 && warriorPosition[i][j] == 1)
			{
				for (int y = j + 1; y < n; y++)
				{
					tempGrid[i][y] = 0; //**
				}
			}
		}
	}


	//대각선 삭제 
	for (int j = medusaCol + 1; j < n; j++)
	{
		int left = medusaRow + (medusaCol - j);
		int right = medusaRow - (medusaCol - j);

		for (int i = left; i < medusaRow; i++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i][j + 1] = 0;
				//대각선 삭제 
				if (i >= 0)
					tempGrid[i - 1][j + 1] = 0;
			}

		}

		//오른쪽 부분
		for (int i = medusaRow + 1; i <= right; i++)
		{
			if (!inRange(i, j))
				continue;

			if (warriorPosition[i][j] == 1)
			{
				//바로 뒤 삭제
				tempGrid[i][j + 1] = 0;
				//대각선 삭제 
				if (i < n)
					tempGrid[i + 1][j + 1] = 0;
			}

		}
	}

	//시야 내 전사 수 계산 
	int cntWarrior = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tempGrid[i][j] == 1 && warriorPosition[i][j] == 1)
			{
				cntWarrior++;
			}
		}
	}

	if (isApply)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				medusaSight[i][j] = tempGrid[i][j];
			}
		}
	}

	/*cout << cntWarrior << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << tempGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	return cntWarrior;
}

int mhtRoad(int r1, int c1, int r2, int c2)
{
	return abs(r1 - r2) + abs(c1 - c2);
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
		
		cin >> n >> m;
		//cout << n << m << endl;

		cin >> homePos.first >> homePos.second >> parkPos.first >> parkPos.second;
		//cout << sr << sc << er << ec << endl;

		for (int i = 0; i < m; i++)
		{
			int ar, ac;
			cin >> ar >> ac;
			warriorPosition[ar][ac] = 1;
			//cout << ar << " " << ac << " ";
		}
		//cout << endl;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> villageGrid[i][j];
				//cout << villageGrid[i][j] << " ";
			}
			//cout << endl;
		}

		/*for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				
				cout << warriorPosition[i][j] << " ";
			}
			cout << endl;
		}*/

		//1. 메두사 이동
		// 초기화
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (villageGrid[i][j] == 1)
					villageGrid[i][j] = 1e9 + 10;
				else
					villageGrid[i][j] = -1;

			}
			
		}

		//(1) park -> home 최단 경로 구하기 
		// 공원 좌표 넘겨주기 -> 옆으로 갈 때 마다 +1
		//상하좌우 비교 -> 도로 o, 격자 밖 x, 
		bfsShortRoad(parkPos.first, parkPos.second);

		
		int medusaRow = homePos.first;
		int medusaCol = homePos.second;

		while (true)
		{
			if (villageGrid[homePos.first][homePos.second] == -1)
			{
				cout << "-1\n";
				break;
			}

			if (medusaRow == parkPos.first && medusaCol == parkPos.second)
			{
				cout << "0\n" << endl;
				break;
			}

			//메두사 한 칸 이동
			//집에서 부터 한칸 이동 
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					medusaPos[i][j] = 0;
				}

			}

			for (int i = 0; i < 4; i++)
			{
				int nextRow = medusaRow + dr[i];
				int nextCol = medusaCol + dc[i];

				if (!inRange(nextRow, nextCol)) continue;

				if (villageGrid[nextRow][nextCol] < villageGrid[medusaRow][medusaCol])
				{
					medusaRow = nextRow;
					medusaCol = nextCol;
					medusaPos[medusaRow][medusaCol] = 1;
				}

			}
			//cout << medusaRow << medusaCol << endl;
			// 
			//2. 메두사의 시선
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					medusaSight[i][j] = 0;
				}
			}
			int upCount = sightUp(medusaRow, medusaCol, false);
			int downCount = sightDown(medusaRow, medusaCol, false);
			int leftCount = sightLeft(medusaRow, medusaCol, false);
			int rightCount = sightRight(medusaRow, medusaCol, false);

			//전사가 가장 많은 시야 선택 - 상 - 하 - 좌 - 우
			int maxWarriorSight = max({ upCount,downCount, leftCount,rightCount });

			if (maxWarriorSight == upCount)
				maxWarriorSight = sightUp(medusaRow, medusaCol, true);
			else if (maxWarriorSight == downCount)
				maxWarriorSight = sightDown(medusaRow, medusaCol, true);
			else if (maxWarriorSight == leftCount)
				maxWarriorSight = sightLeft(medusaRow, medusaCol, true);
			else if (maxWarriorSight == rightCount)
				maxWarriorSight = sightRight(medusaRow, medusaCol, true);


			//3. 전사들의 이동
			vector<pair<int, int>> canMoveW;
			canMoveW.clear();
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (medusaSight[i][j] != 1 && warriorPosition[i][j] == 1) //움직일 수 있는 전사들
					{
						canMoveW.push_back({ i,j });

					}
				}
			}

			int warriorMove = 0;
			int attackMedusa = 0;
			for (auto w : canMoveW)
			{
				int wRow = w.first;
				int wCol = w.second;

				//현재 전사 위치와 메두사 위치의 맨해튼 거리 구함
				int road = mhtRoad(wRow, wCol, medusaRow, medusaCol);
				//1. 첫번째 이동
				bool canMove = false;
				int currentRow = wRow;
				int currentCol = wCol;
				int anotherRoad = 0;
				for (int i = 0; i < 4; i++)
				{
					int nextRow = currentRow + dr[i];
					int nextCol = currentCol + dc[i];

					if (!inRange(nextRow, nextCol))
						continue;

					if (medusaSight[nextRow][nextCol] == 1)
						continue;

					anotherRoad = mhtRoad(nextRow, nextCol, medusaRow, medusaCol);

					if (anotherRoad < road)
					{
						if (medusaPos[nextRow][nextCol] == 1) //메두사와 전사의 위치가 같다면
						{
							warriorPosition[wRow][wCol] = 0;
							attackMedusa++;
							warriorMove++;
							break;
						}
						currentRow = nextRow;
						currentCol = nextCol;
						warriorMove++;
						canMove = true;
						break;
					}
				}

				int anotherR[4] = { 0, 0, -1, 1 };
				int anotherC[4] = { -1, 1, 0, 0 };

				if (canMove)
				{
					for (int i = 0; i < 4; i++)
					{
						int nextRow = currentRow + anotherR[i];
						int nextCol = currentCol + anotherC[i];

						if (!inRange(nextRow, nextCol))
							continue;

						int otherRoad = mhtRoad(nextRow, nextCol, medusaRow, medusaCol);

						if (otherRoad <= anotherRoad)
						{

							if (medusaPos[nextRow][nextCol] == 1) //메두사와 전사의 위치가 같다면
							{
								warriorPosition[wRow][wCol] = 0;
								attackMedusa++;
								warriorMove++;
								canMove = false;
								break;
							}
						}
						if (!canMove)
							break;
					}
				}
			}
			cout << warriorMove << " " << maxWarriorSight << " " << attackMedusa << endl;
			//attackMedusa = 메두사를 공격한 전사 수
			//warriorMove = 모든 전사가 이동한 거리의 합
			//maxWarriorSight = 돌이된 전사 수
		}
		
	}
	return 0;
}