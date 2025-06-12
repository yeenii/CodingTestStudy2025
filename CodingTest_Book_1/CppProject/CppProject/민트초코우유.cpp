#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <cstdio>   // C++ 스타일에서 추천
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
int foodCount[N_MAX][N_MAX]; //기본 음식 조합 개수 카운트 
bool visited[N_MAX][N_MAX];

int dr[4] = {-1,1,0,0};
int dc[4] = { 0,0,-1,1 };

vector<pair<int, pair<int, int>>> group;
vector<pair<int, pair<int, pair<int, int>>>> leaderList;

int countBasicFood(int row, int col)
{
	int cnt = 0;

	if (foodGrid[row][col] & 1) //T(민트)
		cnt++;

	if (foodGrid[row][col] & 2) //2(초코)
		cnt++;

	if (foodGrid[row][col] & 4) //4(우유)
		cnt++;

	return cnt;
}
void morningCompute()
{
	//모든 학생 신앙심 1증가
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

			//현재와 인접 셀이 신봉 음식이 같다면
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
	//(1) 인접한 학생들과 신봉 음식이 같은 경우 그룹 형성
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
			
			//대표들 - 조합음식개수 작은 순, 신앙심, 행, 열 순
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

			group.clear(); //초기화
		}

	} 

	sort(leaderList.begin(), leaderList.end());

	//for (int i = 0; i < leaderList.size(); i++)
	//{
	//	cout << leaderList[i].first<<endl; //조합음식개수 작은 순
	//	cout << leaderList[i].second.first<<endl; //신앙심 큰 순
	//	cout << leaderList[i].second.second.first << endl; //row 작은 순
	//	cout << leaderList[i].second.second.second << endl; //col 작은 순 
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

	// SWEA 제출 시에는 무조건 주석 처리!
	freopen("input.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{

		cout << "#" << test_case << " "<<endl;
		
		cin >> n >> t; //nxn, t일
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

		//숫자로 기본 음식 매핑
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

		 
		//아침 시간
		morningCompute();
		
		//점심 시간
		lunchCompute();

		//저녁 시간
		dinnerCompute();
	}

	return 0;
}
