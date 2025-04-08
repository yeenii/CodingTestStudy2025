#include <string>
#include <vector>
#include<queue>
#include<iostream>

using namespace std;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    string answer = "";
    queue<string> card1;
    queue<string> card2;

    //1. cards1, cards2 에 대한 큐 생성
    for (int i = 0; i < cards1.size(); i++)
    {
        card1.push(cards1[i]);
    }

    for (int i = 0; i < cards2.size(); i++)
    {
        card2.push(cards2[i]);
    }

    //2. goal 배열 크기만큼 돌아가면서, cards1[0], cards2[0]과 goal[i]가 일치하는지 확인. 일치하면 pop(), 아니면 No
    //3. for문이 다 돌아간 경우 -> Yes
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