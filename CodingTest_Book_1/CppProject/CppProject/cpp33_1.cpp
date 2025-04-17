#include<iostream>
#include<vector>

using namespace std;

vector<int> arr;
vector<int> rankData;

//*��� ����, ��ũ��� �˰��� ������ ���

int find(int x)
{
	//�ڱ��ڽ��� ��Ʈ���
	if (arr[x] == x)
	{
		return x;
	}

	/*
	���� 3-> 2 -> 1 -> 0
	find(3) -> find(2) -> find(1) -> find(0)
	�ٽ� �����ϸ� find(3)= 0, find(2)=0,find(1)=0, find(0)=0 -> ��ξ���
	���� ���ϸ� find(3) -> find(2) -> find(1) -> find(0)�� ���� 0 ��ȯ
	*/
	arr[x] = find(arr[x]); // �� ���� ��Ʈ��� �� ��ȯ.

	return arr[x];
}

vector<bool>solution(int k, vector<vector<char>>operations)
{
	vector<bool> result;

	arr.assign(k, 0);
	rankData.assign(k, 0);

	for (int i = 0; i < k; i++)
	{
		arr[i] = i;
	}

	for (auto op : operations)
	{
		//char -> int
		int x = op[1] - '0';
		int y = op[2] - '0';

		if (op[0] == 'u')
		{
			int root_x = find(x);
			int root_y = find(y);

			//���Ͽ� ���� - �ƹ� ������ ��Ʈ���� ����
			if (root_x != root_y)
			{
				if (rankData[root_x] > rankData[root_y])
					arr[root_y] = root_x; //��ũ�� ū xƮ���� yƮ���� ����
				else if (rankData[root_x] < rankData[root_y])
					arr[root_x] = root_y; //��ũ�� ū yƮ���� xƮ���� ����
				else { //��ũ�� ������ ���
					arr[root_y] = root_x; //x�� y �����ϰ� 
					rankData[root_x]++; //x�� ��ũ�� +1��
				}
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
	vector<vector<char>> operations = { {'u','0','1'},{'u','1','2'}, {'f','0','2'} }; //result = {true}
	//vector<vector<char>> operations = { {'u','0','1'},{'u','2','3'}, {'f','0','1'},{'f','0','2'}}; // result = {true, false}

	auto result = solution(k, operations);

	for (auto i = result.begin(); i != result.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return 0;
}