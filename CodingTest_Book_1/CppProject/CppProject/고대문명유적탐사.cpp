#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

const int K_MAX = 15;
const int M_MAX = 300;

int M, K;
int historySpace[5][5];
queue<int> que;
vector<pair<int, pair<int, int>>> grid3x3[9];
int centerPoint[9][9];
bool visited[5][5];
int tempGrid[5][5];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0,0,-1,1};

struct rotationResults {
	int score; //내림차순
	int angle; //회전 각도
	int col;
	int row;
	int index;
};

vector<rotationResults> rtResult;

vector<pair<int, int>> bfsConnect(int val, int r, int c)
{
	queue < pair<int,int> > connectQue;
	vector<pair<int, int>> group;

	connectQue.push({r,c});
	visited[r][c] = true;

	group.push_back({ r,c });

	while (!connectQue.empty())
	{
		int currentRow = connectQue.front().first;
		int currentCol = connectQue.front().second;
		connectQue.pop();
		

		for (int i = 0; i < 4; i++) //상하좌우 
		{
			int nextRow = currentRow + dr[i];
			int nextCol = currentCol + dc[i];

			if (nextRow < 0 || nextRow >= 5 || nextCol < 0 || nextCol >= 5)
				continue;

			if (visited[nextRow][nextCol])
				continue;

			if (tempGrid[nextRow][nextCol]==val)
			{
				connectQue.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;
				group.push_back({ nextRow,nextCol });

			}
		}
	}
	return group;
}

int rotate90(int index, int centerRow, int centerCol, bool isApply) //유물된 조각 수 리턴
{
	//1. 3x3 90도 회전 
	//상대 좌표 공식 (r,c ) -> (c, -r)
	
	//tempGrid 초기화 
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			tempGrid[i][j] = historySpace[i][j];
		}
	}

	for (int i = 0; i < 9; i++)
	{
		int val = grid3x3[index][i].first;

		//(1) 상대 좌표 = 현재 위치 - 중심 좌표 
		int r = grid3x3[index][i].second.first - centerRow;
		int c = grid3x3[index][i].second.second - centerCol;

		//(2) 중심좌표에 (c, -r)
		int dr = centerRow + c;
		int dc = centerCol - r; 

		tempGrid[dr][dc] = val; //2. historySpace와 같은 tempGrid에 저장
	}

	
	//3. BFS로 같은 그룹인지 체크 
	//같은 그룹 3개 이상이면 해당 위치 0으로 
	//tempGrid에 저장
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			visited[i][j] = false;
		}
	}


	int fragileNum = 0; //유물된 조각 수 저장
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			if (visited[i][j])
				continue;

			//** vector 로 받음
			vector<pair<int,int>> group = bfsConnect(tempGrid[i][j], i, j);

			if (group.size() >= 3) //조각이 3개 이상일 떄 
			{
				fragileNum += group.size();

				for (int k = 0; k < group.size(); k++)
				{
					int r = group[k].first;
					int c = group[k].second;
					tempGrid[r][c] = 0;
					
				}
				
			}
			

		}
	}
	//cout << fragileNum << endl;

	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << tempGrid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

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


int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << ":"<<endl;

        //5x5 격자 형태 
		//유물 조각 7종류(1-7)
		
		cin >> K >> M; //탐사 반복 횟수 K, 유물 조각 개수 M 

		//유적지에 조각 정보 저장
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cin >> historySpace[i][j];
				//cout << historySpace[i][j] << " ";
			}
			//cout << endl;
		}

		//유적 벽면에 쓰인 숫자
		for (int i = 0; i < M; i++)
		{
			int num = 0;
			cin >> num;
			que.push(num);
		}

		//3x3 격자 선택
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				centerPoint[i][j] = 1;
				//cout << "(" << i << "," << j << ")" << " ";
			}
			//cout << endl;
		}

		//k번 턴

		//[1] 탐사 진행

		// 3x3 격자 내 값 저장
		int count = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (centerPoint[i][j] == 1)
				{
					//cout << "i: " << i << "j: " << j << endl;
					// 3x3 그리드 내에서
					for (int row = i - 1; row <= i + 1; row++)
					{
						for (int col = j - 1; col <= j + 1; col++)
						{
							int val = historySpace[row][col];
							grid3x3[count].push_back({ val, {row, col } });
							//cout << val << " ";
						}
						//cout << endl;
					}
					count++;
					//cout << endl;

					
				}
			}
		}


		//3x3 격자 회전 - 90도, 180도, 270도
		for (int i = 0; i < 9; i++) //5x5 격자 내 3x3 격자 9개 
		{
			int centerRow = grid3x3[i][4].second.first;
			int centerCol = grid3x3[i][4].second.second;

			int r90 = rotate90(i, centerRow, centerCol, false);
			//[2] 유물 1차 획득 : 3개 이상 연결된 경우, 조각이 유물이 되어 사라짐 
			//유물 1차 획득 가치 최대화 - 회전한 각도가 가장 작은 방법 - 중심 좌표 열이 가장 작은 구간 - 헹이 가장 작은 구간
			rtResult.push_back({ r90, 90, centerCol, centerRow,i });
		}
		sort(rtResult.begin(), rtResult.end(), [](const rotationResults& a, const rotationResults& b) {
			if (a.score != b.score)return a.score > b.score;
			if (a.angle != b.angle)return a.angle < b.angle;
			if (a.col != b.col)return a.col < b.col;
			if (a.row != b.row)return a.row < b.row;
			});
		
		cout << rtResult[0].score << endl;
		
		
		
		//[3] 유적 벽면에 있는 숫자 
		// 채우는 순서: 열번호가 작은 순 - 행번호 큰 순 
		//유적 벽면에 써있는 숫자는 다시 사용 x. 남은 숫자부터 순서대로 사용 
		
		//[4] 유물 연쇄 획득 
		//유물 조각이 생겨난 뒤, 조각들 3개 이상 연결될 경우 -> 앞 방식같이 유물이 되어 사라짐 
		// 아직 채울 숫자가 있거나 & 3개 이상 연결되지 않을 때 까지 반복
		
		//[5] 탐사 반복
		// [1]~[4] 까지를 1턴. K 번의 턴 진행 
		// 각 턴 마다 유물의 가치의 총합을 출력 
		// 탐사 진행 과정에서 어떤 방법을 사용해도 유물을 획득할 수 없다면, 모든 탐사 즉시 종료 




	}
	return 0;
}