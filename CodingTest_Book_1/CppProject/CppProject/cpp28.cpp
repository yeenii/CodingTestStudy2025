/* ���� 28: ����Ž��Ʈ�� - ������ȸ, ������ȸ, ������ȸ 

1. ����, ����, ������ ���� �Լ� ����
2. ��� �迭�� �ε��� ��ȣ 0 �Ѱ���
3. ���� �ε��� ��ȣ ���� ��� �迭 ũ�Ⱑ ũ�ٸ�
4. ����, ������ �� ��ȸ�ϵ��� �ε��� ��� & ��� �Լ� Ȱ��
5. ����� string���� ����

6. �� �ڿ� " " ������ ����
7. result �迭�� ����, ����, ���� ��ȸ ����� ���� �� ���

*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


string postCompute(vector<int> nodes, int idx)
{
	if (idx < nodes.size())
	{
		string ret = postCompute(nodes, idx * 2 + 1);
		ret += postCompute(nodes, idx * 2 + 2);
		ret += to_string(nodes[idx]) + " ";

		return ret;
	}

	return "";
}

string midCompute(vector<int> nodes, int idx)
{
	if (idx < nodes.size())
	{
		string ret = midCompute(nodes, idx * 2 + 1);
		ret +=  to_string(nodes[idx]) + " ";
		ret += midCompute(nodes, idx * 2 + 2);

		return ret;
	}

	return "";
}

string preCompute(vector<int> nodes, int idx)
{
	if (idx < nodes.size())
	{
		string ret = to_string(nodes[idx]) + " ";
		ret += preCompute(nodes, idx * 2 + 1);
		ret += preCompute(nodes, idx * 2 + 2);

		return ret;
	}

	return "";
}


vector<string> solution(vector<int> nodes)
{
	vector<string> result;
	
	string pre = preCompute(nodes, 0); //0���� �ε��� ����
	string mid = midCompute(nodes, 0);
	string post = postCompute(nodes, 0);

	//�Ǹ����� " " ����
	pre.pop_back();
	mid.pop_back();
	post.pop_back();

	//result �迭�� ��� ����
	result.push_back(pre);
	result.push_back(mid);
	result.push_back(post);


	return result;
}

int main()
{
	vector<int> nodes = {1, 2, 3, 4, 5, 6, 7};

	auto result = solution(nodes);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << endl;
	}


	return 0;
}