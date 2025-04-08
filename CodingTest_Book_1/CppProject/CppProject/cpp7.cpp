/*
1. dirs �Ѱܹ���
2. dirs�� x, y ��ǥ ���� �����̴��� ������ �迭 ����
3. ������ ��ġ ������Ʈ
4. ��ǥ ����� �ʾҴ��� üũ
5. �ߺ� ������� üũ - unordered_set<pair<int,int>, pair<int,int>> ���
6. ���� ��ġ�� ������Ʈ
7. �ߺ� ��θ� ������ ���� ��� ���� ��ȯ 
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

    set<pair<pair<int, int>, pair<int, int>>> visited; //pair<> �߰� ����!!

    int x = 5, y = 5;
    int nx, ny;

    for (char dir : dirs)
    {
        int n = toDir(dir); //������ ���
        nx = x + dx[n]; //x��ǥ �̵�
        ny = y + dy[n]; //y��ǥ �̵�

        //��ǥ ���� ���� �ִ��� üũ
        if (nx < 0 || ny < 0 || nx >10 || ny >10)
            continue; //�������� �ʰ� �Ѿ

        //�ߺ� ��� üũ
        pair<int, int> from = { x, y };
        pair<int, int> to = { nx, ny };

        visited.insert({ from, to }); // �߰�ȣ ���� ����!!
        visited.insert({to, from});

        // ���� ��ġ ������Ʈ
        x = nx;
        y = ny;
    }
    

    // ���� ���� = �ߺ� ��� / 2
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