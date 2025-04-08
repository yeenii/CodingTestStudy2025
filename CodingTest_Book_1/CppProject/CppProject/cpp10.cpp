#include<iostream>
#include<stack>

using namespace std;

int solution(string s) {
    
	
	int count=0;
	char temp;
	int x = (int) s.size();

	for (int i = 0; i < x; i++)//2
	{
		stack<char> st; // *스택을 한번의 검사가 끝날 때 마다 초기화해야 함.

		//올바른 괄호인지 체크
		for (char str : s)
		{
			if (str == '[')
				st.push(str);
			else if (str == ']')
			{

				if (st.top() == '[')
				{
					if (!st.empty())
					{
						st.pop();
					}
					else
						st.push(str);
				}
			}

			if (str == '{')
				st.push(str);
			else if (str == '}')
			{

				if (!st.empty())
				{
					if (st.top() == '{')
					{
						st.pop();
					}
				}else
					st.push(str);
			}

			if (str == '(')
				st.push(str);
			else if (str == ')')
			{

				if (!st.empty())
				{
					if (st.top() == '(')
					{
						st.pop();
					}
						
				}else
					st.push(str);

			}
		}

		if (st.empty())
			count++;


		//s 재정렬
		temp = s[0];
		for (int j = 1; j < x; j++)
		{
			s[j - 1] = s[j];
		}
		s[x - 1] = temp;

	}
	
	return count;

}

int main()
{
	string s = "[](){}";
	int result = solution(s);

	cout << result << endl;
	
	return 0;
}