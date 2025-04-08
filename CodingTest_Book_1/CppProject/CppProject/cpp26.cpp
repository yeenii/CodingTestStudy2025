#include<iostream>
#include <string>
#include <vector>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>

using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    string uid;
    string BlockId;
    unordered_map<string, int> Signal_list;
    unordered_map<string, unordered_set<string>> dic_uid;

    answer.assign(id_list.size(),0); //*������ ID�� ���� ���, ������ ���� ���� -> �ʱ�ȭ 0 �ʿ�

    //1. ������ �Ű��� ID, ������ �Ű���� Ƚ�� �ؽ����̺� ����
    for (int i = 0; i < report.size(); i++)
    {
        istringstream iss(report[i]);

        iss >> uid >> BlockId;

        //1. ������ �Ű��� ����
        if (!dic_uid[uid].insert(BlockId).second) //�� ������ ������ ���� �Ű��ϸ� �ǳʶٱ�. �ƴϸ� ����
            continue;

        //2. ������ �Ű���� Ƚ��
        Signal_list[BlockId] += 1;

        
    }
    
    //k Ƚ�� �Ѵ� �Ű���� ID
    unordered_set<string> block_list;
    for (auto p : Signal_list)
    {
        if (k <= p.second)
            block_list.insert(p.first);
    }
    
    // ������ ó�� ��� ���� ����
    for (int i = 0; i < id_list.size(); i++) //��������
    {
        for (auto dic : dic_uid[id_list[i]]) //dic_uid�� ������ �Ű��� ID ������ 
        {
            if(block_list.count(dic)) //�Ű���� ID�� ��� *count() Ȱ��
                answer[i] += 1;
        }
    }

    return answer;
}

int main()
{
    vector<string> id_list = { "muzi", "frodo", "apeach", "neo" };
    vector<string> report = { "muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi" };
    int k = 2;

    auto result = solution(id_list,report,k);

    for (auto i = result.begin(); i != result.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

    return 0;
}

