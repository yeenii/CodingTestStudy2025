/*

1 2 3 4 5 6 7 8
 1/2 4  5/6  7
   4       7
       ?
    
*/

#include<iostream>

using namespace std;

int solution(int n, int a, int b)
{
    int answer = 0;

    while (a != b)
    {
        a = (a + 1) / 2;
        b = (b + 1) / 2;

        answer++;
    }

    return answer;
}

int main()
{
    int n = 8;
    int a = 4;
    int b = 7;

    int result = solution(n, a, b);

    cout << result << endl;

	return 0;
}