#include<iostream>
#include<vector>
#include<stack>

using namespace std;

/*
1. 인형 집기 검사
   - 0이상인 숫자가 있다면 그 숫자 집어서 스택에 저장
2. 같은 숫자이면 pop, count +=2.   
*/

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int num = 0;

    stack<int> st;

    //1. 인형 집기 검사
    for (int j = 0; j < moves.size(); j++) //8
    {

        for (int i = 0; i < board[0].size(); i++) //5
        {
            if (board[i][moves[j] - 1] > 0) // (1) 현재 원소가 0 이상일 경우 -> 열에 가장 위에 있는 원소
            {
                num = i;
                break;
            }
        }

        //만약에, moves가 지정한 열에 모든 행이 0일 경우 -> 스택에 0이 들어갈 수 있음. continue로 건너뛰기.
        if (board[num][moves[j] - 1] == 0)
            continue;

        //(2) 스택의 top과 지정된 원소가 같을 경우
        if (!st.empty() && st.top() == board[num][moves[j] - 1])
        {
            st.pop();
            answer += 2;
        } 
        else
        {
            st.push(board[num][moves[j] - 1]);
        }
        
        board[num][moves[j] - 1] = 0; //(3) 해당 원소의 위치는 0처리
        
    }
   
    return answer;
}

int main()
{
    vector<vector<int>> board = { {0,0,0,0,0}, {0,0,1,0,3}, {0,2,5,0,1}, {4,2,4,4,2}, {3,5,1,3,1} };
    vector<int> moves = { 1,5,3,5,1,2,1,4 };
    
    int result = solution(board, moves);

    cout << result << endl;

    return 0;
}