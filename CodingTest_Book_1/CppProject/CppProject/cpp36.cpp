#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

/*
*깊이 우선 탐색 - 재귀함수로 구현 방법
* 1. 인접 리스트 생성
* 2. 시작 노드 설정 및 시작 노드 방문 처리
* 3. 인접 노드의 방문 여부를 확인. 방문하지 않았다면 재귀
*/

unordered_map<char, vector<char>> DepthGraph;
vector<char> result;
unordered_set<char> visited;

void dfs(char node)
{

	visited.insert(node);
	result.push_back(node);

	//3.
	for (auto neighbor : DepthGraph[node])
	{
		if (visited.find(neighbor) == visited.end())
		{
			dfs(neighbor);
		}
	}
}

vector<char>solution(vector<pair<char, char>> graph, char start)
{
	//1.
	for (auto node : graph)
	{
		 char start = node.first;
		 char end = node.second;

		 DepthGraph[start].push_back(end);
	}


	//2. 
	dfs(start);


	return result;
}

int main()
{
	//vector<pair<char, char>> graph = { {'A','B'}, {'B','C'}, {'C','D'}, {'D','E'} };
	vector<pair<char, char>> graph = { {'A','B'}, {'A','C'}, {'B','D'}, {'B','E'},{'C','F'},{'E','F'}};
	char start = 'A';

	auto result = solution(graph, start);

	for (auto i : result)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}