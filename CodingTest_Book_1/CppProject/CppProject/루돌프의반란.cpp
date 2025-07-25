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
int stun[P_MAX]; //산타의 기절
int points[P_MAX]; //산타의 포인트

int gameSpace[N_MAX][N_MAX]; //루돌프 위치: -1, 산타위치: 1~p로 표시

//**상우하좌
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
		//1. 입력 및 초기화
		/*
		n : 게임판 크기
		m: 게임 턴 수
		p: 산타의 수
		c: 루돌프의 힘
		d : 산타의 힘
		*/

		cin >> n >> m >> p >> c >> d;

		//게임판 초기화
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				gameSpace[i][j] = 0;
			}
		}
		
		cin >> rudRow >> rudCol; //루돌프 위치 row, col
		gameSpace[rudRow][rudCol] = -1; //루돌프 위치 표시 

		for (int i = 1; i <= p; i++)
		{
			cin >> santaNum;
			cin >> santaPos[santaNum].first >> santaPos[santaNum].second;
			//cout << santaNum << " " << santaPos[santaNum].first << " " << santaPos[santaNum].second << endl;
			gameSpace[santaPos[santaNum].first][santaPos[santaNum].second] = santaNum; //산타의 위치 표시
			santa_live[santaNum] = true;//산타 생존 여부 확인
			stun[i] = 0; //** stun, points 초기화
			points[i] = 0;
		}

		for (int k = 1; k <= m; k++) //m번 턴
		{

			//2. 루돌프 이동
			//살아있는 산타 중 루돌프에 가장 가까운 산타 찾음
			int minDist = INT_MAX;
			int closestIdx = 0; //가장 가까운 산타 번호
			int closestX = -1, closestY = -1; //가장 가까운 산타 위치

			for (int i = 1; i <= p; i++) //산타 순서대로
			{
				//산타가 죽었다면 건너뛰기
				if (!santa_live[i])
					continue;
				
				//산타와 루돌프 간의 거리 구함
				int dist = ((santaPos[i].first - rudRow) * (santaPos[i].first - rudRow)) + ((santaPos[i].second - rudCol) * (santaPos[i].second - rudCol));

				if (dist < minDist) //현재 번호 산타가 거리가 가장 가까울 경우 
				{
					minDist = dist;
					closestIdx = i;
					closestX = santaPos[i].first;
					closestY = santaPos[i].second;
				}
				else if (dist == minDist) //가장 가까운 산타가 2명 이상일 경우, r가장 큰 - c가장 큰
				{
					//r가장 큰 - c가장 큰
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

			//산타 쪽으로 루돌프 이동
			if (closestIdx)
			{
				//루돌프 한칸씩 이동
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

				
				gameSpace[rudRow][rudCol] = 0; //기존 루돌프 위치 삭제
				rudRow += moveX;
				rudCol += moveY;
				gameSpace[rudRow][rudCol] = -1; //루돌프 위치 
				//cout << rudRow << " " << rudCol << endl;

				//루돌프와 산타가 충돌한 경우
				if (rudRow == closestX && rudCol == closestY)
				{
					stun[closestIdx] = k + 1; //산타 기절. k+1까지 못 움직임

					int firstX = closestX + moveX * c; //루돌프가 이동해온 방향 반대로 c 만큼 밀려남
					int firstY = closestY + moveY * c;

					//연쇄 이동 
					int lastX = firstX;
					int lastY = firstY;

					while (inRange(lastX, lastY) && gameSpace[lastX][lastY] > 0) //범위 안에 있고, 산타가 있다면
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
							//한칸씩 미루기 
							gameSpace[lastX][lastY] = idx;
							santaPos[idx].first = lastX;
							santaPos[idx].second = lastY;
						}

						lastX = beforeX;
						lastY = beforeY;
					}

					//연쇄 이동 완료 후, 최종 점수 추가
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

			//3. 산타 이동
			for (int i = 1; i <= p; i++)
			{
				if (!santa_live[i] || stun[i] >= k) //산타가 죽은 경우 //산타가 기절한 경우. 다음 턴까지 못 움직임
					continue;

				//산타와 루돌프 간의 현재 거리 구함
				int minDist = ((santaPos[i].first - rudRow) * (santaPos[i].first - rudRow)) + ((santaPos[i].second - rudCol) * (santaPos[i].second - rudCol));
				int SantaMoveDir = -1; //가장 가까운 산타가 움직인 방향 //안움직였으면 -1

				//산타 상우하좌 움직임
				for (int dir = 0; dir < 4; dir++)
				{
					int nx = santaPos[i].first + dr[dir];
					int ny = santaPos[i].second + dc[dir];

					if (nx > n || nx <1 || ny > n || ny < 1) //범위 밖에 있는 경우 건너뛰기 
						continue;

					if (gameSpace[nx][ny] > 0) //다른 산타가 있는 경우
						continue;

					//산타가 움직인 후의 산타와 루돌프의 거리
					int dist = ((nx - rudRow) * (nx - rudRow)) + ((ny - rudCol) * (ny - rudCol));
					if (minDist > dist)
					{
						minDist = dist;
						SantaMoveDir = dir;
					}
				}

				//산타가 움직였다면
				if (SantaMoveDir != -1)
				{
					int nx = santaPos[i].first + dr[SantaMoveDir];
					int ny = santaPos[i].second + dc[SantaMoveDir];

					//산타의 이동으로 충돌한 경우, 
					if (nx == rudRow && ny == rudCol)
					{
						stun[i] = k + 1; //산타 기절. k+1까지 못 움직임

						//움직인 방향의 반대방향으로 튕김
						int moveX = -dr[SantaMoveDir];
						int moveY = -dc[SantaMoveDir];

						int firstX = nx + moveX * d; //왔던 방향의 반대 방향으로 d만큼 튕겨짐
						int firstY = ny + moveY * d;

						//연쇄 이동 
						int lastX = firstX; 
						int lastY = firstY;

						if (d == 1) //힘이 1인 경우 
						{
							//포인트만 줌
							points[i] += d;
						}
						else {

							//범위 안에 있는데, 다른 산타가 있는 경우
							while (inRange(lastX, lastY) && gameSpace[lastX][lastY] > 0)
							{
								//연쇄로 밀릴 수 있는 마지막 칸 검색
								lastX += moveX;
								lastY += moveY;
							}
							
							//뒤에서 부터 순차적으로 산타들 위치 한칸씩 밀기
							while (!(lastX == firstX && lastY == firstY)) //밀리지 않은 경우가 아니라면
							{
								int beforeX = lastX - moveX; //뒤에서 부터 한칸씩 밀기
								int beforeY = lastY - moveY;

								if (!inRange(beforeX, beforeY))
									break;

								int idx = gameSpace[beforeX][beforeY];

								if (!inRange(lastX, lastY)) 
								{
									//게임판 밖으로 밀리면 죽음
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

							//연쇄 이동 후, 최종 위치와 점수, 생존 여부 반영
							points[i] += d; //힘 d 획득
							gameSpace[santaPos[i].first][santaPos[i].second] = 0; //이전 위치 비우기
							santaPos[i].first = firstX; //연쇄 이동 완료 후, 새로운 위치 업데이트
							santaPos[i].second = firstY;

							//산타가 밀려난 위치가 게임판 안/밖 인지 
							if (inRange(firstX, firstY))
								gameSpace[firstX][firstY] = i; //안이면, 산타 번호 등록
							else
								santa_live[i] = false; //생존 여부 -> 죽음 처리 

						}

					}
					else //충돌하지 않은 경우
					{
						gameSpace[santaPos[i].first][santaPos[i].second] = 0;
						santaPos[i].first = nx; //위치 갱신
						santaPos[i].second = ny;
						gameSpace[nx][ny] = i;

					}
				}
			}

			//생존한 산타들은 점수 +1씩 추가
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}