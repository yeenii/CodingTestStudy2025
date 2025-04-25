#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

/*
*���� �켱 Ž�� - ����Լ��� ���� ���
* 1. ���� ����Ʈ ����
* 2. ���� ��� ���� �� ���� ��� �湮 ó��
* 3. ���� ����� �湮 ���θ� Ȯ��. �湮���� �ʾҴٸ� ���
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