#include<iostream>
#include<vector>
#include<stack>

using namespace std;

/*
1. ���� ���� �˻�
   - 0�̻��� ���ڰ� �ִٸ� �� ���� ��� ���ÿ� ����
2. ���� �����̸� pop, count +=2.   
*/

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int num = 0;

    stack<int> st;

    //1. ���� ���� �˻�
    for (int j = 0; j < moves.size(); j++) //8
    {

        for (int i = 0; i < board[0].size(); i++) //5
        {
            if (board[i][moves[j] - 1] > 0) // (1) ���� ���Ұ� 0 �̻��� ��� -> ���� ���� ���� �ִ� ����
            {
                num = i;
                break;
            }
        }

        //���࿡, moves�� ������ ���� ��� ���� 0�� ��� -> ���ÿ� 0�� �� �� ����. continue�� �ǳʶٱ�.
        if (board[num][moves[j] - 1] == 0)
            continue;

        //(2) ������ top�� ������ ���Ұ� ���� ���
        if (!st.empty() && st.top() == board[num][moves[j] - 1])
        {
            st.pop();
            answer += 2;
        } 
        else
        {
            st.push(board[num][moves[j] - 1]);
        }
        
        board[num][moves[j] - 1] = 0; //(3) �ش� ������ ��ġ�� 0ó��
        
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