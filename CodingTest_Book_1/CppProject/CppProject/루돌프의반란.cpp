#define _CRT_SECURE_NO_WARNINGS

#include<cstdio>
#include<iostream>
#include<vector>
#include<climits> //**INT_MAX

using namespace std;

const int N_MAX = 55;
const int P_MAX = 35;

int n, m, p, c, d;
int rudRow, rudCol;
pair<int, int> santaPos[P_MAX];
bool santa_live[P_MAX];
int santaNum;
int stun[P_MAX]; //��Ÿ�� ����
int points[P_MAX]; //��Ÿ�� ����Ʈ

int gameSpace[N_MAX][N_MAX]; //�絹�� ��ġ: -1, ��Ÿ��ġ: 1~p�� ǥ��

//**�������
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0 , -1 };

bool inRange(int r, int c)
{
	return r <= n && r >= 1 && c <= n && c >= 1;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	freopen("input.txt", "r", stdin);
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		//1. �Է� �� �ʱ�ȭ
		/*
		n : ������ ũ��
		m: ���� �� ��
		p: ��Ÿ�� ��
		c: �絹���� ��
		d : ��Ÿ�� ��
		*/

		cin >> n >> m >> p >> c >> d;

		//������ �ʱ�ȭ
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				gameSpace[i][j] = 0;
			}
		}
		
		cin >> rudRow >> rudCol; //�絹�� ��ġ row, col
		gameSpace[rudRow][rudCol] = -1; //�絹�� ��ġ ǥ�� 

		for (int i = 1; i <= p; i++)
		{
			cin >> santaNum;
			cin >> santaPos[santaNum].first >> santaPos[santaNum].second;
			//cout << santaNum << " " << santaPos[santaNum].first << " " << santaPos[santaNum].second << endl;
			gameSpace[santaPos[santaNum].first][santaPos[santaNum].second] = santaNum; //��Ÿ�� ��ġ ǥ��
			santa_live[santaNum] = true;//��Ÿ ���� ���� Ȯ��
			stun[i] = 0; //** stun, points �ʱ�ȭ
			points[i] = 0;
		}

		for (int k = 1; k <= m; k++) //m�� ��
		{

			//2. �絹�� �̵�
			//����ִ� ��Ÿ �� �絹���� ���� ����� ��Ÿ ã��
			int minDist = INT_MAX;
			int closestIdx = 0; //���� ����� ��Ÿ ��ȣ
			int closestX = -1, closestY = -1; //���� ����� ��Ÿ ��ġ

			for (int i = 1; i <= p; i++) //��Ÿ �������
			{
				//��Ÿ�� �׾��ٸ� �ǳʶٱ�
				if (!santa_live[i])
					continue;
				
				//��Ÿ�� �絹�� ���� �Ÿ� ����
				int dist = ((santaPos[i].first - rudRow) * (santaPos[i].first - rudRow)) + ((santaPos[i].second - rudCol) * (santaPos[i].second - rudCol));

				if (dist < minDist) //���� ��ȣ ��Ÿ�� �Ÿ��� ���� ����� ��� 
				{
					minDist = dist;
					closestIdx = i;
					closestX = santaPos[i].first;
					closestY = santaPos[i].second;
				}
				else if (dist == minDist) //���� ����� ��Ÿ�� 2�� �̻��� ���, r���� ū - c���� ū
				{
					//r���� ū - c���� ū
					if (santaPos[i].first > closestX || santaPos[i].first == closestX && santaPos[i].second > closestY)
					{
						closestIdx = i;
						closestX = santaPos[i].first;
						closestY = santaPos[i].second;
					}
				}
			}

			//cout << closestIdx << endl;
			//cout << closestX << " " << closestY << endl;

			//��Ÿ ������ �絹�� �̵�
			if (closestIdx)
			{
				//�絹�� ��ĭ�� �̵�
				int moveX = 0;
				int moveY = 0;

				if (closestX > rudRow)
					moveX = 1;
				else if(closestX < rudRow)
					moveX = -1;

				if (closestY > rudCol)
					moveY = 1;
				else if(closestY < rudCol)
					moveY = -1;

				
				gameSpace[rudRow][rudCol] = 0; //���� �絹�� ��ġ ����
				rudRow += moveX;
				rudCol += moveY;
				gameSpace[rudRow][rudCol] = -1; //�絹�� ��ġ 
				//cout << rudRow << " " << rudCol << endl;

				//�絹���� ��Ÿ�� �浹�� ���
				if (rudRow == closestX && rudCol == closestY)
				{
					stun[closestIdx] = k + 1; //��Ÿ ����. k+1���� �� ������

					int firstX = closestX + moveX * c; //�絹���� �̵��ؿ� ���� �ݴ�� c ��ŭ �з���
					int firstY = closestY + moveY * c;

					//���� �̵� 
					int lastX = firstX;
					int lastY = firstY;

					while (inRange(lastX, lastY) && gameSpace[lastX][lastY] > 0) //���� �ȿ� �ְ�, ��Ÿ�� �ִٸ�
					{
						lastX += moveX;
						lastY += moveY;
					}

					while (!(lastX == firstX && lastY == firstY))
					{
						int beforeX = lastX - moveX;
						int beforeY = lastY - moveY;

						if (!inRange(beforeX, beforeY))
							break;

						int idx = gameSpace[beforeX][beforeY];

						if (!inRange(lastX, lastY))
						{
							santa_live[idx] = false;
						}
						else 
						{
							//��ĭ�� �̷�� 
							gameSpace[lastX][lastY] = idx;
							santaPos[idx].first = lastX;
							santaPos[idx].second = lastY;
						}

						lastX = beforeX;
						lastY = beforeY;
					}

					//���� �̵� �Ϸ� ��, ���� ���� �߰�
					points[closestIdx] += c; 
					santaPos[closestIdx].first = firstX;
					santaPos[closestIdx].second = firstY;

					if (inRange(firstX, firstY))
					{
						gameSpace[firstX][firstY] = closestIdx;
					}
					else
					{
						santa_live[closestIdx] = false;
					}

				}
			}
			

			/*for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					cout << gameSpace[i][j] << " ";
				}
				cout << endl;
			}*/

			//3. ��Ÿ �̵�
			for (int i = 1; i <= p; i++)
			{
				if (!santa_live[i] || stun[i] >= k) //��Ÿ�� ���� ��� //��Ÿ�� ������ ���. ���� �ϱ��� �� ������
					continue;

				//��Ÿ�� �絹�� ���� ���� �Ÿ� ����
				int minDist = ((santaPos[i].first - rudRow) * (santaPos[i].first - rudRow)) + ((santaPos[i].second - rudCol) * (santaPos[i].second - rudCol));
				int SantaMoveDir = -1; //���� ����� ��Ÿ�� ������ ���� //�ȿ��������� -1

				//��Ÿ ������� ������
				for (int dir = 0; dir < 4; dir++)
				{
					int nx = santaPos[i].first + dr[dir];
					int ny = santaPos[i].second + dc[dir];

					if (nx > n || nx <1 || ny > n || ny < 1) //���� �ۿ� �ִ� ��� �ǳʶٱ� 
						continue;

					if (gameSpace[nx][ny] > 0) //�ٸ� ��Ÿ�� �ִ� ���
						continue;

					//��Ÿ�� ������ ���� ��Ÿ�� �絹���� �Ÿ�
					int dist = ((nx - rudRow) * (nx - rudRow)) + ((ny - rudCol) * (ny - rudCol));
					if (minDist > dist)
					{
						minDist = dist;
						SantaMoveDir = dir;
					}
				}

				//��Ÿ�� �������ٸ�
				if (SantaMoveDir != -1)
				{
					int nx = santaPos[i].first + dr[SantaMoveDir];
					int ny = santaPos[i].second + dc[SantaMoveDir];

					//��Ÿ�� �̵����� �浹�� ���, 
					if (nx == rudRow && ny == rudCol)
					{
						stun[i] = k + 1; //��Ÿ ����. k+1���� �� ������

						//������ ������ �ݴ�������� ƨ��
						int moveX = -dr[SantaMoveDir];
						int moveY = -dc[SantaMoveDir];

						int firstX = nx + moveX * d; //�Դ� ������ �ݴ� �������� d��ŭ ƨ����
						int firstY = ny + moveY * d;

						//���� �̵� 
						int lastX = firstX; 
						int lastY = firstY;

						if (d == 1) //���� 1�� ��� 
						{
							//����Ʈ�� ��
							points[i] += d;
						}
						else {

							//���� �ȿ� �ִµ�, �ٸ� ��Ÿ�� �ִ� ���
							while (inRange(lastX, lastY) && gameSpace[lastX][lastY] > 0)
							{
								//����� �и� �� �ִ� ������ ĭ �˻�
								lastX += moveX;
								lastY += moveY;
							}
							
							//�ڿ��� ���� ���������� ��Ÿ�� ��ġ ��ĭ�� �б�
							while (!(lastX == firstX && lastY == firstY)) //�и��� ���� ��찡 �ƴ϶��
							{
								int beforeX = lastX - moveX; //�ڿ��� ���� ��ĭ�� �б�
								int beforeY = lastY - moveY;

								if (!inRange(beforeX, beforeY))
									break;

								int idx = gameSpace[beforeX][beforeY];

								if (!inRange(lastX, lastY)) 
								{
									//������ ������ �и��� ����
									santa_live[idx] = false;
								}
								else
								{
									gameSpace[lastX][lastY] = idx;
									santaPos[idx].first = lastX;
									santaPos[idx].second = lastY;
								}

								lastX = beforeX;
								lastY = beforeY;

							}

							//���� �̵� ��, ���� ��ġ�� ����, ���� ���� �ݿ�
							points[i] += d; //�� d ȹ��
							gameSpace[santaPos[i].first][santaPos[i].second] = 0; //���� ��ġ ����
							santaPos[i].first = firstX; //���� �̵� �Ϸ� ��, ���ο� ��ġ ������Ʈ
							santaPos[i].second = firstY;

							//��Ÿ�� �з��� ��ġ�� ������ ��/�� ���� 
							if (inRange(firstX, firstY))
								gameSpace[firstX][firstY] = i; //���̸�, ��Ÿ ��ȣ ���
							else
								santa_live[i] = false; //���� ���� -> ���� ó�� 

						}

					}
					else //�浹���� ���� ���
					{
						gameSpace[santaPos[i].first][santaPos[i].second] = 0;
						santaPos[i].first = nx; //��ġ ����
						santaPos[i].second = ny;
						gameSpace[nx][ny] = i;

					}
				}
			}

			//������ ��Ÿ���� ���� +1�� �߰�
			for (int i = 1; i <= p; i++)
			{
				if (santa_live[i])
					points[i]++;
			}

		}
		
		for (int i = 1; i <= p; i++)
		{
			cout << points[i] << " ";
		}
		cout << endl;

	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}