#include<iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;
vector<int> rankData;

/*
1. �Ǽ� ��� ���� ���� ���� 
2. ���ĵ� ������� �� ����
3. ����Ŭ�� �������� �ʴ� ��쿡�� �� �����ϰ�, �� �Ǽ� ����� ���� *����Ŭ ����: ���Ͽ�-���ε� �˰���
*/

int find(int x)
{
    if (arr[x] == x)
    {
        return x;
    }

    arr[x] = find(arr[x]);

    return arr[x];
}

bool compare(vector<int> arr1, vector<int> arr2)
{
    return arr1[2] < arr2[2];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;

    sort(costs.begin(), costs.end(), compare);

    arr.assign(n, 0);
    rankData.assign(n, 0);

    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    int totalCost = 0;

    for (vector<int> cost : costs)
    {
        int x = cost[0];
        int y = cost[1];
        int money = cost[2];

        //����Ŭ �Ǻ� -> ���Ͽ� - ���ε� �˰��� 
        //���ε� : ��Ʈ ��尡 ������ Ȯ�� -> ��Ʈ��尡 ������ ����Ŭ��
        int root1 = find(x);
        int root2 = find(y);

        //��Ʈ��尡 ���� ������
        if (root1 != root2)
        {
            //���Ͽ�
            //��Ʈ��� ���� ���� �ͳ��� �����ؼ� �ּ� �ݾ� ����
            if (rankData[root1] > rankData[root2])
                arr[root2] = root1;
            else if (rankData[root1] < rankData[root2])
                arr[root1] = root2;
            else
            {
                arr[root2] = root1;
                rankData[root1]++;
            }

            totalCost += cost[2];
        }
    }

    return answer=totalCost;
}

int main()
{
    int n = 4;
    vector<vector<int>> costs = { {0, 1, 1},{0, 2, 2},{1, 2, 5},{1, 3, 1},{2, 3, 8} };

    int result = solution(n, costs);

    cout << result << endl;

	return 0;
}