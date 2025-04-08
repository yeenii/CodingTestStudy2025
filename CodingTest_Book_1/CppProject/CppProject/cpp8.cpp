#include<iostream>
#include<stack>

using namespace std;

/*
1. 만약에 '(' 가 있는경우, 스택에 push
2. 만약에 ')'가 있는 경우, 현재 스택의 top 위치에 있는 값을 pop

3. string s에 있는 값을 다 스택에 저장했을 때, 모두 상쇄된 경우 -> true 반환, 아닌 경우 -> false 반환.

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
			if (!strStack.empty()) //스택이 비어있지 않을 경우 
				strStack.pop();
			else
				return false; //스택이 비어있을 경우
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