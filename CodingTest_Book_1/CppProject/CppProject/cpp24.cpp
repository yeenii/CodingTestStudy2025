#include<iostream>
#include<sstream>
#include <string>
#include <vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;

    //unordered_map�� ������ �� �� ���� ������ vector�� �����
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
            recordNI[uid] = name; //������ �̸� �ݿ��Ͽ� uid�� �Բ� ����
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

    //���
    for (auto act : actionList) {
        string action = act.first;
        string uid = act.second;
        string nickname = recordNI[uid];

        if (action == "Enter") {
            answer.push_back(nickname + "���� ���Խ��ϴ�.");
        }
        else if (action == "Leave") {
            answer.push_back(nickname + "���� �������ϴ�.");
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