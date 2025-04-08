#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(pair<double,int> a, pair<double, int> b)
{
	//������ �������� ���� (�������� ���� ���, ����������ȣ�� ���� ��)
	if (a.first == b.first)
		return a.second < b.second;

	return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages)
{
	vector<int> stage; //�� �������������� Ŭ�������� ���� ����� ��
	vector<pair<double, int>> failure; // �������� �������� ��ȣ ����

	int playersNum = stages.size(); //stages�� ũ��

	stage.assign(N+1, 0); //ũ�Ⱑ 5�� �迭. n-1 ���� 

	sort(stages.begin(), stages.end()); // stages �������� ����. [1, 2, 2, 2, 3, 3, 4, 6]

	for (int i = 1; i <= N; i++) //�������� ����: 1~5
	{
		stage[i] = count(stages.begin(), stages.end(), i); //�� �������� ���� Ŭ���� ���� ���� ����� ��. [1,3, 2,1,0]
		
		//���������� ������ ������ ���� ���, �ش� ���������� �������� 0
		if (playersNum > 0)
		{
			double failRate = (double)stage[i] / playersNum; // ������. double�� ��ȯ. ex) 1/8
			failure.push_back({ failRate,i }); // �� �������� ��ȣ���� ������ ����. ex) {1,1}
			playersNum -= stage[i]; // ����: stages�� ���� -= Ŭ�������� ���� ����� ��
		}
		else
		{
			failure.push_back({ 0, i });
		}

	}
	
	sort(failure.begin(), failure.end(), compare);
	
	vector<int> answer;

	for (auto p : failure)
	{
		answer.push_back(p.second); // �������� ��ȣ��
	}

	return answer;
}

int main()
{
	vector<int> stages = { 2, 1, 2, 6, 2, 4, 3, 3 };
	//vector<int> stages = { 4, 4, 4, 4 };

	auto result = solution(5, stages); // auto�� ����Ͽ� �ڵ� ����

	for (auto it = result.begin(); it != result.end(); it++) // ���� ���ĵȰ� ���
	{
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}