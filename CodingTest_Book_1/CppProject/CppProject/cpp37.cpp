#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<unordered_set>

using namespace std;

/*�ʺ�켱Ž��
1. ���۳�� ���� �� ���� ��� Ǫ��
2. ť�� ������� �ʴٸ�
3. ť���� ��� ��
4. ���� ���� ���� ��带 Ȯ���ϰ�, ���� �湮���� �ʾҴٸ� ť�� Ǫ���Ͽ� �湮 ó��

*/

unordered_map<int, vector<int>> BreadthGraph;
queue<int> que; 
vector<int> result; //�湮 ���
unordered_set<int> visited; //�湮 ó��

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
		int pop_node = que.front(); //�湮ó���� ���
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