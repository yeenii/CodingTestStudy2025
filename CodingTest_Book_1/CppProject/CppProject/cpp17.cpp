#include <string>
#include <vector>
#include<queue>
#include<iostream>

using namespace std;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    string answer = "";
    queue<string> card1;
    queue<string> card2;

    //1. cards1, cards2 �� ���� ť ����
    for (int i = 0; i < cards1.size(); i++)
    {
        card1.push(cards1[i]);
    }

    for (int i = 0; i < cards2.size(); i++)
    {
        card2.push(cards2[i]);
    }

    //2. goal �迭 ũ�⸸ŭ ���ư��鼭, cards1[0], cards2[0]�� goal[i]�� ��ġ�ϴ��� Ȯ��. ��ġ�ϸ� pop(), �ƴϸ� No
    //3. for���� �� ���ư� ��� -> Yes
    for (int i = 0; i < goal.size(); i++)
    {
        if (!card1.empty() && goal[i] == card1.front())
            card1.pop();
        else if (!card2.empty() && goal[i] == card2.front())
            card2.pop();
        else
            return answer = "No";
    }


    return answer="Yes";

}

int main()
{
    vector<string> cards1 = { "i", "drink", "water" };
    //vector<string> cards1 = { "i", "water", "drink" };
    vector<string> cards2 = { "want", "to" };
    vector<string> goal = { "i", "want", "to", "drink", "water" };
    
    string result = solution(cards1, cards2, goal);
    
    cout << result << endl;

    return 0;
}