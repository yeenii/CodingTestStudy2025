#include<iostream>
#include<sstream>
#include <string>
#include <vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;

    //unordered_map은 순서를 알 수 없기 때문에 vector를 사용함
    unordered_map<string, string> recordNI; // uid, nickname
    vector<pair<string, string>> actionList; // action, uid

    for (int i = 0; i < record.size(); i++)
    {
        istringstream iss(record[i]);
        string actions, uid, name;
        iss >> actions >> uid;

        if (actions == "Enter")
        {
            iss >> name;
            recordNI[uid] = name; //수정된 이름 반영하여 uid와 함께 저장
            actionList.push_back({ actions, uid });
        }
        else if (actions == "Leave")
        {
            actionList.push_back({ actions, uid });
        }
        else if (actions == "Change")
        {
            iss >> name;
            recordNI[uid] = name;
        }
    }

    //출력
    for (auto act : actionList) {
        string action = act.first;
        string uid = act.second;
        string nickname = recordNI[uid];

        if (action == "Enter") {
            answer.push_back(nickname + "님이 들어왔습니다.");
        }
        else if (action == "Leave") {
            answer.push_back(nickname + "님이 나갔습니다.");
        }
    }

    return answer;
}


int main()
{
    vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan" };
    
    auto result = solution(record);
    
    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }

    cout << endl;

    return 0;
}