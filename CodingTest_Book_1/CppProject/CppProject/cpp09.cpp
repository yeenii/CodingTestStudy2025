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

	//나머지들만 스택에 저장
	//몫은 다시 나눠지는 수로
	//*몫이 0 보다 작으면 2진수 변환 멈춤*

	while (decimal > 0)
	{
		int  a = decimal % 2;
		st.push(a);
		decimal = decimal / 2;
		cnt++;
	}

	// 스택 값을 string 형태로 저장
	for (int i = 0; i < cnt; i++)
	{
		result += to_string(st.top()); // to_string() 사용해서 int -> string으로 변환
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