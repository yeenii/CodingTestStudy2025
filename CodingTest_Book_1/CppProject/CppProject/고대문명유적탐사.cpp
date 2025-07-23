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
	vector<pair<int, int>> group; //���� ���� ����

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

			if (nextRow < 0 || nextCol < 0 || nextRow >= 5 || nextCol >= 5) //**���� �ȿ� ������ �ǳʶٱ�
				continue;

			if (visited[nextRow][nextCol]) //�湮������ �ǳʶٱ�
				continue;

			if (tempGrid[nextRow][nextCol]==val)
			{
				que.push({nextRow, nextCol});
				visited[nextRow][nextCol] = true;
				group.push_back({ nextRow,nextCol });
			}
		}
	}

	return group;
}

int computeBFS()
{
	//2. BFS�� ���� ȹ��
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			visited[i][j] = false; //�湮 ���� �ʱ�ȭ

		}
	}

	int fragileNum = 0; //90�� ȸ���� �׸����� �� ���� ����
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (visited[i][j])
				continue;

			vector < pair<int, int >> groupCnt = bfs(tempGrid[i][j], i, j); //�Ȱ��� ���� ���� ����

			//���� ȹ�� 3�� �̻��� ��� 
			if (groupCnt.size() >= 3)
			{
				fragileNum += groupCnt.size();

				for (int k = 0; k < groupCnt.size(); k++) //3�� �̻��� ���� ȹ���� ��ǥ
				{
					int row = groupCnt[k].first;
					int col = groupCnt[k].second;
					tempGrid[row][col] = 0; //3�� �̻��� ��� 0���� �ʱ�ȭ
				}
			}
		}
	}

	return fragileNum;
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

	//1. 90�� ȸ��
	for (int i = 0; i < 9; i++)
	{
		int val = grid[index][i].first;

		int r = grid[index][i].second.first - centerRow;
		int c = grid[index][i].second.second - centerCol;
		
		int nr = centerRow + c;
		int nc = centerCol - r;

		tempGrid[nr][nc] = val;

	}
	
	int fragileNum= computeBFS();

	//���� ����
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

	//1. 180�� ȸ��
	for (int i = 0; i < 9; i++)
	{
		int val = grid[index][i].first;

		int r = grid[index][i].second.first - centerRow;
		int c = grid[index][i].second.second - centerCol;

		int nr = centerRow - r;
		int nc = centerCol - c;

		tempGrid[nr][nc] = val;

	}

	int fragileNum = computeBFS();

	//���� ����
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

	//1. 270�� ȸ��
	for (int i = 0; i < 9; i++)
	{
		int val = grid[index][i].first;

		int r = grid[index][i].second.first - centerRow;
		int c = grid[index][i].second.second - centerCol;

		int nr = centerRow - c;
		int nc = centerCol + r;

		tempGrid[nr][nc] = val;

	}

	int fragileNum = computeBFS(); //���� 3�� �̻� ȹ��

	//���� ����
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

void fillZeroSpace()
{
	//���� ���鿡 ���ִ� ���ڷ� ��� ä���
	vector<pair<int, int>> zeroSpace; //0�� �� ���ϱ�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (historySpace[i][j] == 0)
			{
				zeroSpace.push_back({ j, -i });
			}
		}
	}

	sort(zeroSpace.begin(), zeroSpace.end());

	//0�� �� ���鿡 ���ִ� ���ڷ� ä��� 
	for (auto z : zeroSpace)
	{
		int row = -z.second;
		int col = z.first;

		historySpace[row][col] = artifactList.front();
		artifactList.pop();

		if (artifactList.empty())
			break;
	}
	zeroSpace.clear();

}

int computeRepeatFragile(int finalBest)
{
	//���� ���� ȹ��
	while (!artifactList.empty())
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				tempGrid[i][j] = historySpace[i][j];
			}
		}
		int repeatFragileNum = computeBFS();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				historySpace[i][j] = tempGrid[i][j];
			}
		}

		if (repeatFragileNum == 0)
			break;

		if (artifactList.empty())
			break;

		fillZeroSpace();

		finalBest += repeatFragileNum;

	}

	return finalBest;
}

int turnGrid()
{

	rtResults.clear();

	//3x3�׸��� ���ϱ�
	int cnt=0;
	for (int i = 0; i < 9; i++)
	{
		grid[i].clear();
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (centerPoint[i][j] == 1)
			{
				//3x3�׸��� ����
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

	for (int i = 0; i < 9; i++) //9�� ��
	{
		int centerRow = grid[i][4].second.first;
		int centerCol = grid[i][4].second.second;
		//cout << centerRow << centerCol << endl;

		int fragile90 = rotate90(i, centerRow, centerCol,false); //90��
		int fragile180 = rotate180(i, centerRow, centerCol, false); //180��
		int fragile270 = rotate270(i, centerRow, centerCol, false); //270��

		//�켱 ������ ����
		rtResults.push_back({ fragile90, 90, centerCol, centerRow, i}); //** ���� ���� ����!!!!
		rtResults.push_back({ fragile180, 180, centerCol, centerRow, i });
		rtResults.push_back({ fragile270, 270, centerCol, centerRow, i });

	}

	sort(rtResults.begin(), rtResults.end(), [](const rotationResults& a, const rotationResults& b) {
		if (a.size != b.size)
			return a.size > b.size; //��������
		if (a.angle != b.angle)
			return a.angle < b.angle;
		if (a.col != b.col)
			return a.col < b.col;
		if (a.row != b.row)
			return a.row < b.row;
		});


	//���� �ִ� ����
	rotationResults best = rtResults[0];

	int finalBest = 0;
	if (best.angle == 90)
		finalBest= rotate90(best.index, best.row, best.col, true);
	else if(best.angle == 180)
		finalBest = rotate180(best.index, best.row, best.col, true);
	else if (best.angle == 270)
		finalBest = rotate270(best.index, best.row, best.col, true);
	

	return finalBest; //���� ȹ�� �� ����
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

		//ť �ʱ�ȭ
		queue<int> empty;
		artifactList.swap(empty);

		//ť�� ���� ���� ���� ����
		for (int i = 0; i < m; i++)
		{
			int artifact;
			cin >> artifact;
			artifactList.push(artifact);
		}

		//�߽���ǥ
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				centerPoint[i][j] = 1;
			}
		}

		for (int i = 0; i < k; i++) //k�� ��
		{
			//1. �׸��� 90,180,270 ȸ��
			int artifactCount = turnGrid();

			//2. ���� ���� ���ڷ� 0�� �� ä���
			fillZeroSpace();

			//3. ���� ����ȹ��
			int result = computeRepeatFragile(artifactCount);

			if (result == 0)
				break;

			cout << result << " ";
		}

		
		
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}