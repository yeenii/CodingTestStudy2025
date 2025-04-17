#include<iostream>
#include<vector>

using namespace std;

vector<int> arr;

//*��� ����, ��ũ��� �˰��� �������� ���� ���

int find(int x)
{
	//�ڱ��ڽ��� ��Ʈ���
	if (arr[x] == x)
	{
		return x;
	}

	return find(arr[x]); //�ڱ��ڽ��� ��Ʈ��尡 �ƴ� ���, �θ���� �̵��ؼ� ��Ʈ��� ã��
}

vector<bool>solution(int k, vector<vector<char>>operations)
{
	vector<bool> result;

	arr.assign(k, 0);

	for (int i = 0; i < k; i++)
	{
		arr[i] = i;
	}

	for (auto op : operations)
	{
		int x = op[1]-'0';
		int y = op[2] - '0';

		if (op[0] == 'u')
		{
			int root_x = find(x);
			int root_y = find(y);

			//���Ͽ� ���� - �ƹ� ������ ��Ʈ���� ����
			if (root_x != root_y)
			{
				arr[root_x] = root_y;
			}

		}
		else if (op[0] == 'f')
		{
			int root_x = find(x);
			int root_y = find(y);

			if (root_x == root_y)
				result.push_back(true);
			else
				result.push_back(false);
		}
	}

	return result;
}

int main()
{
	int k = 3;
	vector<vector<char>> operations = { {'u','0','1'},{'u','1','2'}, {'f','0','2'}}; //result = {true}
	//vector<vector<char>> operations = { {'u','0','1'},{'u','2','3'}, {'f','0','1'},{'f','0','2'}}; // result = {true, false}

	auto result = solution(k, operations);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return 0;
}