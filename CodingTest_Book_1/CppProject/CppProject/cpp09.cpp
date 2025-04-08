#include<iostream>
#include<stack>
#include<vector>
#include<string>

using namespace std;

string solution(int decimal)
{
	stack<int> st;
	int cnt=0;
	string result;

	//�������鸸 ���ÿ� ����
	//���� �ٽ� �������� ����
	//*���� 0 ���� ������ 2���� ��ȯ ����*

	while (decimal > 0)
	{
		int  a = decimal % 2;
		st.push(a);
		decimal = decimal / 2;
		cnt++;
	}

	// ���� ���� string ���·� ����
	for (int i = 0; i < cnt; i++)
	{
		result += to_string(st.top()); // to_string() ����ؼ� int -> string���� ��ȯ
		st.pop();
		
	}
	
	return result;
}

int main()
{
	int decimal = 12345;

	string result = solution(decimal);

	cout <<  result << endl;


	return 0;
}