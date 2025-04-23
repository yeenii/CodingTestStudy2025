#include<iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;
vector<int> rankData;

/*
1. 건설 비용 오름 차순 정렬 
2. 정렬된 순서대로 섬 연결
3. 사이클을 형성하지 않는 경우에만 섬 연결하고, 총 건설 비용을 구함 *사이클 여부: 유니온-파인드 알고르짐
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

        //사이클 판별 -> 유니온 - 파인드 알고리즘 
        //파인드 : 루트 노드가 같은지 확인 -> 루트노드가 같으면 사이클임
        int root1 = find(x);
        int root2 = find(y);

        //루트노드가 같지 않으면
        if (root1 != root2)
        {
            //유니온
            //루트노드 같지 않은 것끼리 집합해서 최소 금액 구함
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