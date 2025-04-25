#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<unordered_set>

using namespace std;

/*너비우선탐색
1. 시작노드 설정 및 시작 노드 푸시
2. 큐가 비어있지 않다면
3. 큐에서 노드 팝
4. 팝한 노드와 인접 노드를 확인하고, 아직 방문하지 않았다면 큐에 푸시하여 방문 처리

*/

unordered_map<int, vector<int>> BreadthGraph;
queue<int> que; 
vector<int> result; //방문 결과
unordered_set<int> visited; //방문 처리

void bfs(int node)
{
	//1.
	que.push(node);
	visited.insert(node);
	result.push_back(node);

	//2.
	while (!que.empty())
	{
		//3.
		int pop_node = que.front(); //방문처리된 노드
		que.pop();
		
		//4.
		for (auto neighbor : BreadthGraph[pop_node])
		{
			if (visited.find(neighbor) == visited.end())
			{
				que.push(neighbor);
				visited.insert(neighbor);
				result.push_back(neighbor);
			}
		}
		

	}

}

vector<int> solution(vector<pair<int, int>> graph, int start)
{
	//1. 
	for (auto node : graph)
	{
		int x = node.first;
		int y = node.second;

		BreadthGraph[x].push_back(y);
	}

	//2. 
	bfs(start);

	return result;
}

int main()
{
	vector<pair<int, int>> graph = { {1,2}, {1, 3},{2,4},{2, 5},{3, 6}, {3, 7},{4,8},{5,8},{6,9},{7, 9} };
	int start=1;

	auto result = solution(graph, start);

	for (auto i : result)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}