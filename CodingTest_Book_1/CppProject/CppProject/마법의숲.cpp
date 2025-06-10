#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm> //max()

using namespace std;

const int R_MAX = 80; //��
const int C_MAX = 80; //��
const int k_MAX = 1005; //������ �� 

int R, C, K;
int c, d;

int forest[R_MAX + 3][C_MAX]; //��. 
int isExit[R_MAX + 3][C_MAX]; // �ⱸ�� ���

//���� 
int dr[4] = { -1,0, 1, 0 };
int dc[4] = { 0, 1, 0 , -1 };

int result;
int visited[R_MAX + 3][C_MAX];

bool inRange(int r, int c)
{
	if (r >= 3 && r < R + 3 && c >= 0 && c < C)
		return true;
	else
		return false;
}

bool canGo(int r, int c)
{
	bool canDo = r + 1 < R + 3; //**
	canDo = canDo && c - 1 >= 0;
	canDo = canDo && c + 1 < C;

	canDo = canDo && (forest[r - 1][c - 1] == 0);
	canDo = canDo && (forest[r - 1][c] == 0);
	canDo = canDo && (forest[r - 1][c + 1] == 0);
	canDo = canDo && (forest[r][c - 1] == 0);
	canDo = canDo && (forest[r][c] == 0);
	canDo = canDo && (forest[r][c + 1] == 0);
	canDo = canDo && (forest[r + 1][c] == 0);

	//cout << canDo << endl;
	return canDo;

}

int bfs(int r, int c)
{
	queue<pair<int, int>> que;
	int maxRow = r; // ���� ���� �ִ� ������ �ʱ�ȭ

	//�湮 ó�� 
	for (int i = 0; i < R + 3; i++)
	{
		for (int j = 0; j < C; j++)
		{
			visited[i][j] = false;
		}
	}

	//1. ť�� Ǫ���ϸ鼭 �湮 ó��
	que.push({ r,c });
	visited[r][c] = true;

	//2. ť�� ������� �ʴٸ�
	while (!que.empty())
	{
		//3. ť�� ��
		int currentRow = que.front().first;
		int currentCol = que.front().second;
		que.pop();

		//4. ���� �Ͱ� ������ �� �� 
		for (int i = 0; i < 4; i++)
		{
			int nextRow = currentRow + dr[i];
			int nextCol = currentCol + dc[i];

			if (!inRange(nextRow, nextCol))
				continue;

			if (visited[nextRow][nextCol])
				continue;

			if (forest[nextRow][nextCol] == forest[currentRow][currentCol] ||
				(isExit[currentRow][currentCol] == 1 && forest[nextRow][nextCol] != 0))
			{
				que.push({ nextRow, nextCol });
				visited[nextRow][nextCol] = true;

				maxRow = max(maxRow, nextRow);

			}


		}

	}

	//5. �����ϴٸ� ť�� Ǫ���ϸ鼭 �湮 ó�� 

	return maxRow;
}

void move(int index, int r, int c, int d)//��, ����
{
	//1. �������� ��ĭ
	if (canGo(r + 1, c))
	{
		move(index, r + 1, c, d);
	}
	else if (canGo(r + 1, c - 1)) //2. ���� �������� ȸ��(�ݽð�)�ϸ鼭 ��ĭ - �Ʒ��� ��ĭ
	{
		move(index, r + 1, c - 1, (d + 3) % 4);
	}
	else if (canGo(r + 1, c + 1)) //3. ���� �������� ȸ��(�ð�)�ϸ鼭 ��ĭ - �Ʒ��� ��ĭ
	{
		move(index, r + 1, c + 1, (d + 1) % 4);
	}
	else //�ִ��� �������� �� ���
	{
		//�� ���� ��� ���
		if (!inRange(r - 1, c - 1) && !inRange(r - 1, c + 1))
		{
			for (int i = 0; i < R + 3; i++)
			{
				for (int j = 0; j < C; j++)
				{
					forest[i][j] = 0;
					isExit[i][j] = 0;
				}
			}
		}
		else //�� ���� ����� �ʾ�, ���� �̵� 
		{

			//���� �� ����
			forest[r][c] = index;
			for (int i = 0; i < 4; i++)
			{
				forest[r + dr[i]][c + dc[i]] = index;
			}

			/*for (int i = 0; i < R + 3; i++)
			{
				for (int j = 0; j < C; j++)
				{
					cout << forest[i][j] << " ";
				}
				cout << endl;

			}
			cout << endl;*/

			//���� �ⱸ 
			isExit[r + dr[d]][c + dc[d]] = 1;

			/*for (int i = 0; i < R + 3; i++)
			{
				for (int j = 0; j < C; j++)
				{
					cout << isExit[i][j] << " ";
				}
				cout << endl;

			}
			cout << endl;*/

			result += bfs(r, c) - 3 + 1; //-3+1 �ؾ��� ������ ���� 6�� ��
			//cout << result << endl;

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

		//cout << "#" << test_case << ": " << endl;

		//[���� �ڵ� �ۼ�]
		/*
		- R�� x C�� (���� �� 1��, ���� �Ʒ� R��)
		- ���� ���ؼ��� ���� �� ����
		- K���� ������ ���� ���� Ž

		[��]
		- ���� ��� ���� (�߾�ĭ ���� 5ĭ)
		- ���� �ⱸ : �� �߾� ���� 4ĭ �� �ϳ�
		- ��� ���⿡���� ž�� ����
		- ���� ���� ������ �ⱸ������

		[�� �̵�]
		- i��°�� ���� Ž���ϴ� ��
		- ���� �� �ۿ��� ����
		- ���� �߾��� ci ���� �ǵ��� �ϴ� ��ġ���� ������
		- �ʱ� ���� �ⱸ : di ���� (0~3. ��(0)-��(1)-��(2)-��(3))

		[�켱����]
		1. �������� ��ĭ
		2. ���� �������� ȸ��(�ݽð�)�ϸ鼭 ��ĭ - �Ʒ��� ��ĭ
		3. ���� �������� ȸ��(�ð�)�ϸ鼭 ��ĭ - �Ʒ��� ��ĭ
		4. �ִ��� �������� �̵�������, ���� �� �Ϻΰ� ���� ��� ��� -> ���Ӱ� �� Ž��

		�ִ��� �������� �̵���, �̵��� �� ���� ���

		[���� �̵�]
		- ������ �� �� �����¿� ���� ĭ���� �̵�
		- ���� ��ġ �ϰ� �ִ� ���� �ⱸ�� �ٸ� �񷽰� �����ϴٸ�,
		  �ⱸ�� ���� �ٸ� ������ �̵�
		- �ִ��� ���� ĭ���� �̵� - ���� �� ��ġ ����
		- ������ ���� ��ġ�� �� ��ȣ ���� ����

		*/

		cin >> R >> C >> K; //���� ũ�� RxC, ������ �� K
		//cout << R << " " << C << " " << K << endl;

		//�� �ʱ�ȭ 
		for (int i = 0; i < R + 3; i++)
		{
			for (int j = 0; j < C; j++)
			{
				forest[i][j] = 0;
				isExit[i][j] = 0;
			}

		}

		for (int i = 1; i <= K; i++) //1~K��
		{
			cin >> c >> d; //��, ����
			//cout << c <<" "<< d <<endl;

			move(i, 1, c - 1, d); //�ε���, ��, ��, ����

		}

		cout << result << endl;

	}
	return 0;
}