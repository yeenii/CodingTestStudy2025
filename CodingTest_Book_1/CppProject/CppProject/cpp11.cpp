#include<iostream>
#include<stack>

using namespace std;

int solution(string s)
{
	stack<char> basket;

	for (char c : s)
	{
		if (basket.empty())
		{
			basket.push(c);
		}
		else {
			if (basket.top() != c)
				basket.push(c);
			else
				basket.pop();
		}
	}

	if (basket.empty())
		return 1;
	else
		return 0;
}

int main()
{
	string s = "cdcd";
	//string s = "baabaa";
	cout << solution(s) << endl;
	return 0;
}