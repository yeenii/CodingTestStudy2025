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
	int score; //��������
	int angle; //ȸ�� ����
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
		

		for (int i = 0; i < 4; i++) //�����¿� 
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

int rotate90(int index, int centerRow, int centerCol, bool isApply) //������ ���� �� ����
{
	//1. 3x3 90�� ȸ�� 
	//��� ��ǥ ���� (r,c ) -> (c, -r)
	
	//tempGrid �ʱ�ȭ 
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

		//(1) ��� ��ǥ = ���� ��ġ - �߽� ��ǥ 
		int r = grid3x3[index][i].second.first - centerRow;
		int c = grid3x3[index][i].second.second - centerCol;

		//(2) �߽���ǥ�� (c, -r)
		int dr = centerRow + c;
		int dc = centerCol - r; 

		tempGrid[dr][dc] = val; //2. historySpace�� ���� tempGrid�� ����
	}

	
	//3. BFS�� ���� �׷����� üũ 
	//���� �׷� 3�� �̻��̸� �ش� ��ġ 0���� 
	//tempGrid�� ����
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			visited[i][j] = false;
		}
	}


	int fragileNum = 0; //������ ���� �� ����
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			if (visited[i][j])
				continue;

			//** vector �� ����
			vector<pair<int,int>> group = bfsConnect(tempGrid[i][j], i, j);

			if (group.size() >= 3) //������ 3�� �̻��� �� 
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

        //5x5 ���� ���� 
		//���� ���� 7����(1-7)
		
		cin >> K >> M; //Ž�� �ݺ� Ƚ�� K, ���� ���� ���� M 

		//�������� ���� ���� ����
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cin >> historySpace[i][j];
				//cout << historySpace[i][j] << " ";
			}
			//cout << endl;
		}

		//���� ���鿡 ���� ����
		for (int i = 0; i < M; i++)
		{
			int num = 0;
			cin >> num;
			que.push(num);
		}

		//3x3 ���� ����
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				centerPoint[i][j] = 1;
				//cout << "(" << i << "," << j << ")" << " ";
			}
			//cout << endl;
		}

		//k�� ��

		//[1] Ž�� ����

		// 3x3 ���� �� �� ����
		int count = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (centerPoint[i][j] == 1)
				{
					//cout << "i: " << i << "j: " << j << endl;
					// 3x3 �׸��� ������
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


		//3x3 ���� ȸ�� - 90��, 180��, 270��
		for (int i = 0; i < 9; i++) //5x5 ���� �� 3x3 ���� 9�� 
		{
			int centerRow = grid3x3[i][4].second.first;
			int centerCol = grid3x3[i][4].second.second;

			int r90 = rotate90(i, centerRow, centerCol, false);
			//[2] ���� 1�� ȹ�� : 3�� �̻� ����� ���, ������ ������ �Ǿ� ����� 
			//���� 1�� ȹ�� ��ġ �ִ�ȭ - ȸ���� ������ ���� ���� ��� - �߽� ��ǥ ���� ���� ���� ���� - ���� ���� ���� ����
			rtResult.push_back({ r90, 90, centerCol, centerRow,i });
		}
		sort(rtResult.begin(), rtResult.end(), [](const rotationResults& a, const rotationResults& b) {
			if (a.score != b.score)return a.score > b.score;
			if (a.angle != b.angle)return a.angle < b.angle;
			if (a.col != b.col)return a.col < b.col;
			if (a.row != b.row)return a.row < b.row;
			});
		
		cout << rtResult[0].score << endl;
		
		
		
		//[3] ���� ���鿡 �ִ� ���� 
		// ä��� ����: ����ȣ�� ���� �� - ���ȣ ū �� 
		//���� ���鿡 ���ִ� ���ڴ� �ٽ� ��� x. ���� ���ں��� ������� ��� 
		
		//[4] ���� ���� ȹ�� 
		//���� ������ ���ܳ� ��, ������ 3�� �̻� ����� ��� -> �� ��İ��� ������ �Ǿ� ����� 
		// ���� ä�� ���ڰ� �ְų� & 3�� �̻� ������� ���� �� ���� �ݺ�
		
		//[5] Ž�� �ݺ�
		// [1]~[4] ������ 1��. K ���� �� ���� 
		// �� �� ���� ������ ��ġ�� ������ ��� 
		// Ž�� ���� �������� � ����� ����ص� ������ ȹ���� �� ���ٸ�, ��� Ž�� ��� ���� 




	}
	return 0;
}