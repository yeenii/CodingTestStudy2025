/*
1. dirs 넘겨받음
2. dirs의 x, y 좌표 어디로 움직이는지 저장한 배열 정의
3. 움직인 위치 업데이트
4. 좌표 벗어나지 않았는지 체크
5. 중복 경로인지 체크 - unordered_set<pair<int,int>, pair<int,int>> 사용
6. 현재 위치를 업데이트
7. 중복 경로를 제외한 최종 경로 길이 반환 
*/

#include<iostream>
#include<set>
#include<vector>
#include <string>

using namespace std;

int toDir(char dir)
{
    if (dir == 'U')
        return 0;
    else if (dir == 'D')
        return 1;
    else if (dir == 'R')
        return 2;
    else if (dir == 'L')
        return 3;
    else
        return -1;
}

int solution(string dirs) {
    int answer = 0;

    vector<int> dx = { 0, 0, 1, -1 };
    vector<int> dy = { 1, -1, 0, 0 };

    set<pair<pair<int, int>, pair<int, int>>> visited; //pair<> 추가 주의!!

    int x = 5, y = 5;
    int nx, ny;

    for (char dir : dirs)
    {
        int n = toDir(dir); //움직일 경로
        nx = x + dx[n]; //x좌표 이동
        ny = y + dy[n]; //y좌표 이동

        //좌표 범위 내에 있는지 체크
        if (nx < 0 || ny < 0 || nx >10 || ny >10)
            continue; //동작하지 않고 넘어감

        //중복 경로 체크
        pair<int, int> from = { x, y };
        pair<int, int> to = { nx, ny };

        visited.insert({ from, to }); // 중괄호 포함 주의!!
        visited.insert({to, from});

        // 현재 위치 업데이트
        x = nx;
        y = ny;
    }
    

    // 최종 길이 = 중복 경로 / 2
    answer = (int) visited.size() / 2;

    return answer;
}

int main()
{
    string dirs = "LULLLLLLU";

    int result = solution(dirs);
 
    cout << result << endl;

	return 0;
}