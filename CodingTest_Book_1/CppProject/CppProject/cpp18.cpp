/*
1. �ؽ� ���̺� ����: arr ���Ҹ� �ؽ����̺� �ε����� �����ϰ�, ���� �������¿� ���� 0 �Ǵ� 1�� ó��
2. `target - ���� == �ؽ����̺� �ε���` �� ��� true, �ƴϸ� false
   - �ߺ� ���� ����
*/

#include<iostream>
#include<vector>

using namespace std;

bool solution(vector<int> arr, int target)
{
	//1. �ؽ����̺� ����
	vector<int> hash;
	hash.assign(target + 1, 0); //�ؽ����̺� ũ�� ���� & 0���� �ʱ�ȭ

	for (int i = 0; i <arr.size(); i++)
	{
		//arr ���Ұ� target���� �۰ų� ���� ��쿡�� �ؽ����̺� ����. -> �ؽ����̺� ũ�⺸�� �� �������� �ʱ� ���ؼ�
		if(arr[i]<=target)
			hash[arr[i]] = 1;
		
	}

	//2. �ΰ��� �� ���ؼ� Ư�� �� ����������� �˻�
	for (int i = 0; i < arr.size(); i++)
	{
		int n = target - arr[i];
		
		//�ߺ� ���� ����
		if (arr[i] == n)
			continue;

		//`target-���� = �ؽ����̺� �ε���` �� ��� true
		if (hash[n] == 1)
			return true;
		else
			continue;

	}

	return false; //arr �迭 �� ���Ƶ� ���� ��� false

}

int main()
{
	/*vector<int> arr = { 1,2,3,4,8 };
	int target = 6;*/

	vector<int> arr = { 2, 3, 5, 9 };
	int target = 10;

	bool result= solution(arr, target);

	cout << result << endl;
	return 0;
}