#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<algorithm>

using namespace std;

int n, m, v;
int v1, v2;
unordered_map<int, vector<int>> graph;
unordered_set<int> visited1;
unordered_set<int> visited2;
vector<int> result1;
vector<int> result2;

void dfs(int node)
{
	//�湮 ó��
	//�̿� �湮�ߴ��� Ȯ��
	//�湮��������, ���

	visited1.insert(node);
	result1.push_back(node);

	for (auto neighbor : graph[node])
	{
		if (visited1.find(neighbor) == visited1.end())
			dfs(neighbor);
	}
}

void bfs(int node)
{
	//ť ���
	//1. ť�� ���� ��� Ǫ���ϸ鼭 �湮ó��
	//2. ť�� ������� �ʴٸ�
	//3. ť�� ��
	//4. ���� ���� �̿� �湮�ϰ�, �̿��� �湮ó���Ǿ����� �ʴٸ� ť�� Ǫ��
	
	queue<int> que;

	que.push(node);
	visited2.insert(node);
	result2.push_back(node);

	while (!que.empty())
	{
		int current = que.front();
		que.pop();

		for (auto neighbor : graph[current])
		{
			if (visited2.find(neighbor) == visited2.end())
			{
				que.push(neighbor);
				visited2.insert(neighbor);
				result2.push_back(neighbor);
			}
		}
	}

	
}

int main(int argc, char** argv)
{
	//int test_case;
	//int T;

	//freopen("input.txt", "r", stdin);
	//cin >> T;

	//for (test_case = 1; test_case <= T; ++test_case)
	//{
		cin >> n >> m >> v;
		//cout << n << m << v<< endl;

		for (int i = 0; i < m; i++)
		{
			cin >> v1 >> v2;
			//cout << v1 << v2 << endl;

			//**����� ���� ó��
			graph[v1].push_back(v2);
			graph[v2].push_back(v1);

		}

		// **�� ����� �̿� ����Ʈ�� ((����))�ؼ� ������ �湮 ����
		for (auto& p : graph) {
			sort(p.second.begin(), p.second.end());
		}

		dfs(v); //���� ���
		bfs(v);

		for (auto i : result1)
		{
			cout << i << " ";
		}
		cout << endl;

		for (auto i : result2)
		{
			cout << i << " ";
		}
		cout << endl;
	//}

	return 0;
}