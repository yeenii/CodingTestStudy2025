#include<iostream>
#include<stack>

using namespace std;

/*
1. ���࿡ '(' �� �ִ°��, ���ÿ� push
2. ���࿡ ')'�� �ִ� ���, ���� ������ top ��ġ�� �ִ� ���� pop

3. string s�� �ִ� ���� �� ���ÿ� �������� ��, ��� ���� ��� -> true ��ȯ, �ƴ� ��� -> false ��ȯ.

*/
bool solution(string s)
{
	stack<char> strStack;

	for (char str : s)
	{
		if(str == '(')
			strStack.push(str);
		else if (str == ')')
		{
			if (!strStack.empty()) //������ ������� ���� ��� 
				strStack.pop();
			else
				return false; //������ ������� ���
		} 
			
	}

	if (strStack.empty())
		return true; //1
	else
		return false; //0
}

int main()
{
	//string s = "(())()";
	string s = "((())()";
	bool result = solution(s);
	cout << result << endl;
	return 0;
}